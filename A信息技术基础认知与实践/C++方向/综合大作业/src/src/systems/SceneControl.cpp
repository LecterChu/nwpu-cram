// Game - NWPU C++ sp25
// Created on 2025/5/16
// by konakona418 (https://github.com/konakona418)

#include "SceneControl.hpp"

#include "Common.hpp"
#include "Logger.hpp"
#include "components/SceneTree.hpp"
#include "components/Layout.hpp"

entt::entity game::SceneTreeUtils::attachSceneTreeComponents(entt::entity entity) {
    auto& registry = game::getRegistry();

    if (registry.any_of<CNode>(entity)) {
        throw std::runtime_error("Entity already has CNode component.");
    }

    registry.emplace<CNode>(entity);
    registry.emplace<CParent>(entity);
    registry.emplace<CChild>(entity);

    markAsDirty(entity);

    return entity;
}

entt::entity game::SceneTreeUtils::detachSceneTreeComponents(entt::entity entity) {
    auto& registry = game::getRegistry();

    if (registry.any_of<CSceneElementNeedsUpdate>(entity)) {
        markAsCleanRecurse(entity);
    }

    auto parent = registry.get<CParent>(entity);
    if (parent.getParent() != entt::null) {
        detachChild(parent.getParent(), entity);
    }

    if (registry.get<CChild>(entity).hasChildren()) {
        for (const auto child : registry.get<CChild>(entity).getChildren()) {
            detachParent(child, entity);
        }
    }

    registry.remove<CNode>(entity);
    registry.remove<CParent>(entity);
    registry.remove<CChild>(entity);

    return entity;
}

entt::entity game::SceneTreeUtils::attachChild(const entt::entity parent, const entt::entity child) {
    auto& registry = game::getRegistry();

    if (!registry.any_of<CChild>(parent)) {
        throw std::runtime_error("Parent entity does not have CChild component.");
    }
    if (!registry.any_of<CParent>(child)) {
        throw std::runtime_error("Child entity does not have CParent component.");
    }

    registry.get<CChild>(parent).addChild(child);

    if (registry.get<CParent>(child).getParent() != entt::null) {
        detachParent(child, registry.get<CParent>(child).getParent());
    }
    registry.get<CParent>(child).setParent(parent);

    markAsDirty(child);

    return child;
}

entt::entity game::SceneTreeUtils::detachChild(const entt::entity parent, const entt::entity child) {
    auto& registry = game::getRegistry();

    if (!registry.any_of<CChild>(parent)) {
        throw std::runtime_error("Parent entity does not have CChild component.");
    }
    if (!registry.any_of<CParent>(child)) {
        throw std::runtime_error("Child entity does not have CParent component.");
    }

    registry.get<CChild>(parent).removeChild(child);
    registry.get<CParent>(child).setParent(entt::null);

    markAsDirty(child);

    return child;
}

entt::entity game::SceneTreeUtils::attachParent(entt::entity child, entt::entity parent) {
    auto& registry = game::getRegistry();

    if (!registry.any_of<CChild>(parent)) {
        throw std::runtime_error("Parent entity does not have CChild component.");
    }
    if (!registry.any_of<CParent>(child)) {
        throw std::runtime_error("Child entity does not have CParent component.");
    }

    if (registry.get<CParent>(child).getParent() != entt::null) {
        detachParent(child, registry.get<CParent>(child).getParent());
    }
    attachChild(parent, child);

    markAsDirty(child);

    return child;
}

entt::entity game::SceneTreeUtils::detachParent(entt::entity child, entt::entity parent) {
    auto& registry = game::getRegistry();

    if (!registry.any_of<CChild>(parent)) {
        throw std::runtime_error("Parent entity does not have CChild component.");
    }
    if (!registry.any_of<CParent>(child)) {
        throw std::runtime_error("Child entity does not have CParent component.");
    }

    detachChild(parent, child);

    return child;
}

entt::entity game::SceneTreeUtils::markAsDirty(entt::entity entity) {
    auto& registry = game::getRegistry();

    if (registry.any_of<CSceneElementNeedsUpdate>(entity)) {
        // already dirty
        return entity;
    }

    registry.emplace<CSceneElementNeedsUpdate>(entity);

    for (const auto child : registry.get<CChild>(entity).getChildren()) {
        markAsDirty(child);
    }
    // this will recursively mark all children as dirty

    return entity;
}

entt::entity game::SceneTreeUtils::markAsClean(entt::entity entity) {
    auto& registry = game::getRegistry();

    if (!registry.any_of<CSceneElementNeedsUpdate>(entity)) {
        // already clean
        return entity;
    }

    registry.remove<CSceneElementNeedsUpdate>(entity);
    // in the meantime, we shouldn't mark children as clean even if its parent is clean
    return entity;
}

entt::entity game::SceneTreeUtils::markAsCleanRecurse(entt::entity entity) {
    auto& registry = game::getRegistry();
    if (registry.any_of<CSceneElementNeedsUpdate>(entity)) {
        // only mark as clean if it's dirty
        markAsClean(entity);
    }

    for (const auto child : registry.get<CChild>(entity).getChildren()) {
        markAsCleanRecurse(child);
    }

    return entity;
}

bool game::SceneTreeUtils::isDirty(entt::entity entity) {
    auto& registry = game::getRegistry();
    return registry.any_of<CSceneElementNeedsUpdate>(entity);
}

void game::SceneTreeUtils::unmount(entt::entity entity) {
    auto& registry = game::getRegistry();

    if (!registry.valid(entity)) {
        getLogger().logWarn("Entity has been invalidated forehand.");
        return;
    }

    if (!registry.any_of<CNode>(entity)) {
        throw std::runtime_error("Entity does not have CNode component.");
    }

    // life cycle!!
    // the problem is, unmounting a child will cause all the components to be destroyed
    // and if we use inline iteration, as we hold a **reference** to the children list,
    // it will cause the iterator to be invalidated!
    const auto children = registry.get<CChild>(entity).getChildren();
    for (const auto child : children) {
        unmount(child);
    }

    if (registry.any_of<CNode>(entity)) {
        detachSceneTreeComponents(entity);
    }
    registry.destroy(entity);

    /*getLogger().logDebug("invoked SceneTreeUtils::unmount() on entity "
        + std::to_string(static_cast<entt::id_type>(entity)));*/
}

void game::SScenePositionUpdateSystem::update() {
    auto& registry = game::getRegistry();

    // this is to prevent potential infinite loop
    // at least we can make it easy to debug
    constexpr size_t maxIterationLimit = 512;
    size_t iterationCount = 0;

    while (registry.view<CSceneElementNeedsUpdate>().size() > 0) {
        if (++iterationCount > maxIterationLimit) {
            getLogger().logError(
                Logger::concatLineFile(
                    "SceneGlobalPositionSystem::update() iteration count exceeded maxIterationLimit",
                    __LINE__, __FILE_NAME__));

            for (const auto dirty : registry.view<CSceneElementNeedsUpdate>()) {
                markEntityAsClean(dirty);
            }
            return;
        }

        auto dirtyView = registry.view<CNode, CParent, CChild, CSceneElementNeedsUpdate>();
        for (const auto dirty : dirtyView) {
            bool canUpdateNow = false;

            if (!registry.valid(dirty)) {
                getLogger().logError(
                    Logger::concatLineFile(
                        "SceneGlobalPositionSystem::update() invalid entity",
                        __LINE__, __FILE_NAME__));
            }

            auto parent = dirtyView.get<CParent>(dirty);

            if (parent.getParent() == entt::null) {
                canUpdateNow = true;
            } else {
                if (!dirtyView.contains(parent.getParent())) {
                    // so here the parent is not in the view,
                    // which means that the parent is not dirty.
                    canUpdateNow = true;
                }
            }

            if (canUpdateNow) {
                // todo: process transform.
                calculateLayout(dirty);
                markEntityAsClean(dirty);
            }
        }
    }

    if (registry.view<CSceneElementNeedsUpdate>().size() > 0) {
        getLogger().logError(
            Logger::concatLineFile(
                "SceneGlobalPositionSystem::update() dirty entities still exist",
                __LINE__, __FILE_NAME__));

        for (const auto dirty : registry.view<CSceneElementNeedsUpdate>()) {
            markEntityAsClean(dirty);
        }
    }
}

void game::SScenePositionUpdateSystem::markEntityAsDirty(const entt::entity entity) {
    SceneTreeUtils::markAsDirty(entity);
}

void game::SScenePositionUpdateSystem::markEntityAsClean(entt::entity entity) {
    SceneTreeUtils::markAsClean(entity);
}

void game::SScenePositionUpdateSystem::calculateLayout(entt::entity entity) {
    auto& registry = game::getRegistry();

    if (!registry.any_of<CLayout>(entity)) {
        throw std::runtime_error("Entity does not have CLayout component.");
    }

    auto layout = registry.get<CLayout>(entity);
    auto parent = registry.get<CParent>(entity);

    auto localTransform = registry.get<CLocalTransform>(entity);

    // we use anchor to calculate the origin offset
    auto anchorOffset = layout.getAnchor().getAnchorVec();
    auto calculatedOrigin = sf::Vector2f { anchorOffset.x * localTransform.getSize().x, anchorOffset.y * localTransform.getSize().y };
    registry.get<CGlobalTransform>(entity).setOrigin(calculatedOrigin);

    auto absoluteScale = localTransform.getScale();

    if (layout.getLayoutType() == CLayout::LayoutType::Absolute ||
        parent.getParent() == entt::null) {
        registry.get<CGlobalTransform>(entity).setPosition(
            localTransform.getPosition()
            /*+ sf::Vector2f  { anchorOffset.x * localTransform.getSize().x, anchorOffset.y * localTransform.getSize().y }*/);
        registry.get<CGlobalTransform>(entity).setSize(localTransform.getSize());
        registry.get<CGlobalTransform>(entity).setScale(absoluteScale);
        return;
    }

    auto parentGlobalTransform = registry.get<CGlobalTransform>(parent.getParent());

    auto relativeOffset = localTransform.getPosition() /*+
        sf::Vector2f { anchorOffset.x * localTransform.getSize().x, anchorOffset.y * localTransform.getSize().y }*/;

    registry.get<CGlobalTransform>(entity).setPosition(
        parentGlobalTransform.getPosition() + relativeOffset);
    registry.get<CGlobalTransform>(entity).setSize(localTransform.getSize());

    auto parentScale = parentGlobalTransform.getScale();
    auto relativeScale = sf::Vector2f { absoluteScale.x * parentScale.x, absoluteScale.y * parentScale.y};
    registry.get<CGlobalTransform>(entity).setScale(relativeScale);
}

void game::SSceneUnmountSystem::update() {
    auto& registry = game::getRegistry();

    for (const auto entity : registry.view<CUnmount>()) {
        unmount(entity);
    }
}

void game::SSceneUnmountSystem::unmount(entt::entity entity) {
    SceneTreeUtils::unmount(entity);
}

void game::UnmountUtils::queueUnmount(entt::entity entity) {
    auto& registry = game::getRegistry();
    if (registry.any_of<CUnmount>(entity)) {
        return;
    }
    registry.emplace<CUnmount>(entity);
}

bool game::UnmountUtils::isUnmountingQueued(entt::entity entity) {
    return game::getRegistry().any_of<CUnmount>(entity);
}
