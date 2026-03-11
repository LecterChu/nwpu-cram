// Game - NWPU C++ sp25
// Created on 2025/5/24
// by konakona418 (https://github.com/konakona418)

#ifndef GAME25SP_LIGHTING_HPP
#define GAME25SP_LIGHTING_HPP

#include "SFML/Graphics/Color.hpp"

namespace game {

    struct CLightingComponent {
        CLightingComponent() = default;
        CLightingComponent(sf::Color color, float radius) : color(color), radius(radius) {}
        CLightingComponent(sf::Color color, float radius, float attenuationExponent) : color(color), radius(radius), attenuationExponent(attenuationExponent) {}

        void setColor(sf::Color c) { this->color = c; }
        [[nodiscard]] sf::Color getColor() const { return color; }

        void setRadius(float r) {  this->radius = r; }
        [[nodiscard]] float getRadius() const { return radius; }

        void setAttenuationExponent(float a) { this->attenuationExponent = a; }
        [[nodiscard]] float getAttenuationExponent() const { return attenuationExponent; }

    private:
        sf::Color color { sf::Color::White };
        float radius { 1.0f };
        float attenuationExponent { 1.0f };
    };

} // game

#endif //GAME25SP_LIGHTING_HPP
