// Game - NWPU C++ sp25
// Created on 2025/5/20
// by konakona418 (https://github.com/konakona418)

#include "CollisionControl.hpp"

#include "Common.hpp"
#include "Game.hpp"
#include "components/Collision.hpp"
#include "components/Layout.hpp"

namespace game {
    void SCollisionSystem::update(sf::Time deltaTime) {
        auto& registry = getRegistry();
        auto view = registry.view<CCollisionComponent, CCollisionLayerComponent>();
        for (auto it1 = view.begin(); it1 != view.end(); ++it1) {
            for (auto it2 = std::next(it1); it2 != view.end(); ++it2) {
                if (!registry.valid(*it1) || !registry.valid(*it2)) {
                    getLogger().logWarn("CollisionSystem: Invalid entity");
                    continue;
                }
                auto& layer1 = view.get<CCollisionLayerComponent>(*it1);
                auto& layer2 = view.get<CCollisionLayerComponent>(*it2);

                if (!CollisionUtils::shouldCollide(
                    layer1.getLayer(), layer2.getLayer(),
                    layer1.getMask(), layer2.getMask())) {
                    continue;
                }

                bool collision = false;
                collision |= checkCollisionBoxes(registry, *it1, *it2);
                collision |= checkCollisionCircles(registry, *it1, *it2);
                collision |= checkCollisionBoxCircle(registry, *it1, *it2);

                if (collision) {
                    emitSignal(registry, *it1, *it2);
                }
            }
        }

    }

    bool SCollisionSystem::checkCollisionBoxes(entt::registry& reg, const entt::entity& entity1, const entt::entity& entity2) {
        if (!(reg.any_of<CCollisionAABBComponent>(entity1) && reg.any_of<CCollisionAABBComponent>(entity2))) {
            return false;
        }
        const auto& pos1 = reg.get<CGlobalTransform>(entity1).getPosition();
        const auto& pos2 = reg.get<CGlobalTransform>(entity2).getPosition();

        const auto& boxSize1 = reg.get<CCollisionAABBComponent>(entity1).getBoundingBox();
        const auto& boxSize2 = reg.get<CCollisionAABBComponent>(entity2).getBoundingBox();

        return sf::FloatRect { pos1, boxSize1 }
            .findIntersection(sf::FloatRect { pos2, boxSize2 })
            .has_value();
    }

    bool SCollisionSystem::checkCollisionCircles(entt::registry& reg, const entt::entity& entity1, const entt::entity& entity2) {
        if (!(reg.any_of<CCollisionCircleComponent>(entity1) && reg.any_of<CCollisionCircleComponent>(entity2))) {
            return false;
        }
        const auto& pos1 = reg.get<CGlobalTransform>(entity1).getPosition();
        const auto& pos2 = reg.get<CGlobalTransform>(entity2).getPosition();

        auto rad1 = reg.get<CCollisionCircleComponent>(entity1).getRadius();
        auto rad2 = reg.get<CCollisionCircleComponent>(entity2).getRadius();

        return (pos1 - pos2).lengthSquared() < std::powf(rad1 + rad2, 2);
    }

    bool SCollisionSystem::checkCollisionBoxCircle(entt::registry& reg, const entt::entity& entity1, const entt::entity& entity2) {
        if (!(reg.any_of<CCollisionAABBComponent>(entity1) && reg.any_of<CCollisionCircleComponent>(entity2)) &&
            !(reg.any_of<CCollisionCircleComponent>(entity1) && reg.any_of<CCollisionAABBComponent>(entity2))) {
            return false;
        }
        if (reg.any_of<CCollisionAABBComponent>(entity1)) {
            const auto& pos1 = reg.get<CGlobalTransform>(entity1).getPosition();
            const auto& boxSize1 = reg.get<CCollisionAABBComponent>(entity1).getBoundingBox();
            auto rad1 = boxSize1.length() / 2;

            const auto& pos2 = reg.get<CGlobalTransform>(entity2).getPosition();
            auto rad2 = reg.get<CCollisionCircleComponent>(entity2).getRadius();
            return (pos1 - pos2).lengthSquared() < std::powf(rad1 + rad2, 2);
        }
        if (reg.any_of<CCollisionCircleComponent>(entity1)) {
            const auto& pos1 = reg.get<CGlobalTransform>(entity1).getPosition();
            auto rad1 = reg.get<CCollisionCircleComponent>(entity1).getRadius();

            const auto& pos2 = reg.get<CGlobalTransform>(entity2).getPosition();
            const auto& boxSize2 = reg.get<CCollisionAABBComponent>(entity2).getBoundingBox();
            auto rad2 = boxSize2.length() / 2;
            return (pos1 - pos2).lengthSquared() < std::powf(rad1 + rad2, 2);
        }
        return false;
    }

    void SCollisionSystem::emitSignal(entt::registry& reg, const entt::entity& entity1, const entt::entity& entity2) {
        getGame().getEventDispatcher().trigger<EOnCollisionEvent>(EOnCollisionEvent { entity1, entity2 });
    }
} // game