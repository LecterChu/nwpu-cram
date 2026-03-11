// Game - NWPU C++ sp25
// Created on 2025/5/22
// by konakona418 (https://github.com/konakona418)

#ifndef VELOCITY_HPP
#define VELOCITY_HPP

#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"

namespace game {
    struct CVelocity {
        CVelocity() = default;
        explicit CVelocity(sf::Vector2f velocity) : m_velocity(velocity) {}
        CVelocity(const sf::Vector2f velocity, const sf::Vector2f acceleration)
            : m_velocity(velocity), m_acceleration(acceleration) {}

        [[nodiscard]] sf::Vector2f getVelocity() const { return m_velocity; }
        void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }

        [[nodiscard]] sf::Vector2f getAcceleration() const { return m_acceleration; }
        void setAcceleration(sf::Vector2f acceleration) { m_acceleration = acceleration; }

        void update(sf::Time deltaTime) { m_velocity += m_acceleration * deltaTime.asSeconds(); }
    private:
        sf::Vector2f m_velocity;
        sf::Vector2f m_acceleration;
    };
} // game

#endif //VELOCITY_HPP
