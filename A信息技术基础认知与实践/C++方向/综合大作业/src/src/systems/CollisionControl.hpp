// Game - NWPU C++ sp25
// Created on 2025/5/20
// by konakona418 (https://github.com/konakona418)

#ifndef COLLISIONCONTROL_HPP
#define COLLISIONCONTROL_HPP

#include <entt/entity/entity.hpp>

#include "SFML/System/Time.hpp"

namespace game {

    struct EOnCollisionEvent {
        entt::entity collider1;
        entt::entity collider2;
    };

    class SCollisionSystem {
    public:
        SCollisionSystem() = default;

        static void update(sf::Time deltaTime);
    private:
        static bool checkCollisionBoxes(entt::registry& reg, const entt::entity& entity1, const entt::entity& entity2);
        static bool checkCollisionCircles(entt::registry& reg, const entt::entity& entity1, const entt::entity& entity2);
        static bool checkCollisionBoxCircle(entt::registry& reg, const entt::entity& entity1, const entt::entity& entity2);
        static void emitSignal(entt::registry& reg, const entt::entity& entity1, const entt::entity& entity2);
    };

} // game

#endif //COLLISIONCONTROL_HPP
