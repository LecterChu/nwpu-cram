// Game - NWPU C++ sp25
// Created on 2025/5/20
// by konakona418 (https://github.com/konakona418)

#ifndef SCRIPTSCONTROL_HPP
#define SCRIPTSCONTROL_HPP
#include "SFML/System/Time.hpp"

namespace game {
    class SScriptsSystem {
    public:
        SScriptsSystem() = default;
        static void update(sf::Time deltaTime);
    };

} // game

#endif //SCRIPTSCONTROL_HPP
