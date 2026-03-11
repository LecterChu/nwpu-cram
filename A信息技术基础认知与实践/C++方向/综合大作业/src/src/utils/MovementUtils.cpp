// Game - NWPU C++ sp25
// Created on 2025/5/21
// by konakona418 (https://github.com/konakona418)

#include "MovementUtils.hpp"

#include "systems/SceneControl.hpp"

namespace game {
    void game::MovementUtils::Builder::build(const entt::entity& entity) const {
        auto& registry = game::getRegistry();

        if (!registry.any_of<CHasLayout>(entity)) {
            // getLogger().logDebug("Entity does not have layout components, adding them");
            attachLayoutComponents(entity);
        }

        registry.get<CLayout>(entity).setAnchor(m_anchor);
        registry.get<CLayout>(entity).setLayoutType(m_layoutType);
        registry.get<CLocalTransform>(entity).setSize(m_size);
        registry.get<CLocalTransform>(entity).setPosition(m_localPos);
        registry.get<CLocalTransform>(entity).setScale(m_scale);
        registry.get<CGlobalTransform>(entity).setPosition(m_globalPos);
    }

    entt::entity game::MovementUtils::attachLayoutComponents(entt::entity entity) {
        auto& registry = game::getRegistry();

        if (registry.any_of<CHasLayout>(entity)) {
            throw std::runtime_error("Entity already has layout components");
        }

        registry.emplace<CHasLayout>(entity);
        registry.emplace<CLayout>(entity);
        registry.emplace<CGlobalTransform>(entity);
        registry.emplace<CLocalTransform>(entity);
        return entity;
    }

    bool MovementUtils::Flip::isHorizontallyFlipped(const sf::Vector2f& scaleVec) {
        return scaleVec.x < 0;
    }

    bool MovementUtils::Flip::isVerticallyFlipped(const sf::Vector2f& scaleVec) {
        return scaleVec.y < 0;
    }

    void MovementUtils::markAsDirty(entt::entity entity) {
        if (SceneTreeUtils::isDirty(entity)) {
            return;
        }
        SceneTreeUtils::markAsDirty(entity);
    }

    void MovementUtils::markAsClean(entt::entity entity) {
        if (!SceneTreeUtils::isDirty(entity)) {
            return;
        }
        SceneTreeUtils::markAsClean(entity);
    }

    void MovementUtils::setPosition(entt::entity entity, sf::Vector2f position) {
        auto& registry = getRegistry();
        registry.patch<CLocalTransform>(entity, [position](CLocalTransform& localTransform) {
            localTransform.setPosition(position);
        });
        markAsDirty(entity);
    }

    void MovementUtils::setSize(entt::entity entity, sf::Vector2f size) {
        auto& registry = getRegistry();
        registry.patch<CLocalTransform>(entity, [size](CLocalTransform& localTransform) {
            localTransform.setSize(size);
        });
        markAsDirty(entity);
    }

    void MovementUtils::setScale(entt::entity entity, sf::Vector2f scale) {
        auto& registry = getRegistry();
        registry.patch<CLocalTransform>(entity, [scale](CLocalTransform& localTransform) {
            localTransform.setScale(scale);
        });
        markAsDirty(entity);
    }

    void MovementUtils::setAnchor(entt::entity entity, CLayout::Anchor anchor) {
        auto& registry = getRegistry();
        registry.patch<CLayout>(entity, [anchor](CLayout& layout) {
            layout.setAnchor(anchor);
        });
    }

    void MovementUtils::setLayoutType(entt::entity entity, CLayout::LayoutType layoutType) {
        auto& registry = getRegistry();
        registry.patch<CLayout>(entity, [layoutType](CLayout& layout) {
            layout.setLayoutType(layoutType);
        });
        markAsDirty(entity);
    }

    void MovementUtils::move(entt::entity entity, sf::Vector2f offset) {
        auto& registry = getRegistry();
        registry.patch<CLocalTransform>(entity, [offset](CLocalTransform& localTransform) {
            localTransform.move(offset);
        });
        markAsDirty(entity);
    }

    void MovementUtils::flip(entt::entity entity, sf::Vector2f flip) {
        auto& registry = getRegistry();
        registry.patch<CLocalTransform>(entity, [flip](CLocalTransform& localTransform) {
            auto scale = localTransform.getScale();
            localTransform.setScale({std::fabsf(scale.x) * flip.x, std::fabsf(scale.y) * flip.y});
        });
        markAsDirty(entity);
    }

    void MovementUtils::flipHorizontal(entt::entity entity, bool flip) {
        if (flip) {
            MovementUtils::flip(entity, Flip::Horizontal);
        }
        else {
            MovementUtils::flip(entity, Flip::None);
        }
    }

    void MovementUtils::flipVertical(entt::entity entity, bool flip) {
        if (flip) {
            MovementUtils::flip(entity, Flip::Vertical);
        }
        else {
            MovementUtils::flip(entity, Flip::None);
        }
    }

    bool MovementUtils::isOutOfMapBounds(entt::entity entity, sf::Vector2f minBound, sf::Vector2f maxBound, sf::Vector2f offset) {
        if (minBound.x > maxBound.x || minBound.y > maxBound.y) {
            throw std::runtime_error("Min bound is greater than max bound");
        }
        if (offset.x > maxBound.x || offset.y > maxBound.y || offset.x < minBound.x || offset.y < minBound.y) {
            return true;
        }
        return false;
    }
} // game
