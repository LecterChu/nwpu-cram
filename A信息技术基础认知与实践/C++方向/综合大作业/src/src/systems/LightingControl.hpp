// Game - NWPU C++ sp25
// Created on 2025/5/24
// by konakona418 (https://github.com/konakona418)

#ifndef GAME25SP_LIGHTINGCONTROL_HPP
#define GAME25SP_LIGHTINGCONTROL_HPP

#include <string>

#include "SFML/Graphics/RenderTarget.hpp"

namespace game {
    class SLightingSystem {
    public:
        static void update(sf::RenderTarget& target);
    private:
        static sf::Shader& getShader();
        static sf::Texture& getDummyTexture();
    };
}


#endif //GAME25SP_LIGHTINGCONTROL_HPP
