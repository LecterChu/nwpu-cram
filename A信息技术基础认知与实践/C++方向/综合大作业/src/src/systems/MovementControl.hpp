// Game - NWPU C++ sp25
// Created on 2025/5/20
// by konakona418 (https://github.com/konakona418)

#ifndef MOVEMENTCONTROL_HPP
#define MOVEMENTCONTROL_HPP
#include <entt/entity/entity.hpp>

#include "components/Layout.hpp"
#include "SFML/System/Vector2.hpp"

namespace game {
    class SMovementSystem {
    public:
        static void update(sf::Time deltaTime);
    };
} // game

#endif //MOVEMENTCONTROL_HPP
