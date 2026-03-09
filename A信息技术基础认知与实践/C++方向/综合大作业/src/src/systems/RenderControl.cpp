// Game - NWPU C++ sp25
// Created on 2025/5/16
// by konakona418 (https://github.com/konakona418)

#include "RenderControl.hpp"

#include "Common.hpp"
#include "components/Layout.hpp"
#include "components/Render.hpp"
#include "components/SceneTree.hpp"

void game::SRenderSystem::update(sf::RenderTarget& target, size_t targetId, sf::Time deltaTime) {
    auto& registry = game::getRegistry();

    registry.sort<CRenderLayerComponent>(
        [](const auto& lhs, const auto& rhs) {
            if (lhs.getLayer() == rhs.getLayer()) {
                return lhs.getOrder() < rhs.getOrder();
            }
            return lhs.getLayer() < rhs.getLayer();
    });

    auto commonView = registry.view<CGlobalTransform, CRenderComponent, CRenderLayerComponent, CRenderTargetComponent>();
    // make sure that the ordering is applied.
    // see also: https://github.com/skypjack/entt/issues/752
    commonView.use<CRenderLayerComponent>();

    for (auto entity : commonView) {
        size_t renderTargetId = commonView.get<CRenderTargetComponent>(entity).getTargetId();
        if (!checkRenderTargetMask(renderTargetId, targetId)) {
            continue;
        }

        auto globalTransform = commonView.get<CGlobalTransform>(entity);
        if (registry.any_of<CSpriteRenderComponent>(entity)) {
            registry.get<CSpriteRenderComponent>(entity).update(target, globalTransform);
            continue;
        }
        if (registry.any_of<CAnimatedSpriteRenderComponent>(entity)) {
            registry.get<CAnimatedSpriteRenderComponent>(entity).update(target, deltaTime, globalTransform);
            continue;
        }
        if (registry.any_of<CTextRenderComponent>(entity)) {
            registry.get<CTextRenderComponent>(entity).update(target, globalTransform);
            continue;
        }
        if (registry.any_of<CShapeRenderComponent>(entity)) {
            registry.get<CShapeRenderComponent>(entity).update(target, globalTransform);
            continue;
        }
        // todo: implement other render systems
    }
}

bool game::RenderUtils::isVisible(entt::entity entity) {
    auto& registry = game::getRegistry();
    return registry.any_of<CRenderComponent>(entity);
}

void game::RenderUtils::markAsInvisible(entt::entity entity) {
    auto& registry = game::getRegistry();
    if (!registry.any_of<CNode>(entity)) {
        getLogger().logWarn("Entity does not have CNode, markAsInvisibleNotRecurse() will be used instead.");
        markAsInvisibleNotRecurse(entity);
        return;
    }

    for (auto child : registry.get<CChild>(entity).getChildren()) {
        markAsInvisible(child);
    }
    markAsInvisibleNotRecurse(entity);
}

void game::RenderUtils::markAsVisible(entt::entity entity) {
    auto& registry = game::getRegistry();
    if (!registry.any_of<CNode>(entity)) {
        getLogger().logWarn("Entity does not have CNode, markAsVisibleNotRecurse() will be used instead.");
        markAsVisibleNotRecurse(entity);
        return;
    }

    for (auto child : registry.get<CChild>(entity).getChildren()) {
        markAsVisible(child);
    }
    markAsVisibleNotRecurse(entity);
}

void game::RenderUtils::markAsInvisibleNotRecurse(entt::entity entity) {
    auto& registry = game::getRegistry();

    if (registry.any_of<CRenderComponent>(entity)) {
        registry.remove<CRenderComponent>(entity);
    }
}

void game::RenderUtils::markAsVisibleNotRecurse(entt::entity entity) {
    auto& registry = game::getRegistry();

    if (!registry.any_of<CRenderComponent>(entity)) {
        registry.emplace<CRenderComponent>(entity);
    }
}

bool game::SRenderSystem::checkRenderTargetMask(size_t targetId, size_t mask) {
    return !!(targetId & mask);
}
