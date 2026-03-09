// Game - NWPU C++ sp25
// Created on 2025/5/20
// by konakona418 (https://github.com/konakona418)

#include "MovementControl.hpp"

#include "components/Velocity.hpp"
#include "utils/MovementUtils.hpp"

namespace game {
    void SMovementSystem::update(sf::Time deltaTime) {
        auto& registry = getRegistry();
        auto view = registry.view<CLocalTransform, CVelocity>();
        for (auto entity : view) {
            MovementUtils::move(entity,
                view.get<CVelocity>(entity).getVelocity() * deltaTime.asSeconds());
            view.get<CVelocity>(entity).update(deltaTime);
        }
    }
} // game