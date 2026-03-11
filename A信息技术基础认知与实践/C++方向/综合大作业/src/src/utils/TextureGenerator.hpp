// Game - NWPU C++ sp25
// Created on 2025/5/20
// by konakona418 (https://github.com/konakona418)

#ifndef ANIMATEDTEXTUREGENERATOR_HPP
#define ANIMATEDTEXTUREGENERATOR_HPP
#include "components/Render.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"

namespace game {
    struct RawTexture;

    class AnimatedTextureGenerator {
    public:
        AnimatedTextureGenerator() = default;
        AnimatedTextureGenerator& setSize(sf::Vector2f size) { m_size = size; return *this; }
        AnimatedTextureGenerator& setPlacement(sf::Vector2u placement) { m_placement = placement; return *this; }
        AnimatedTextureGenerator& setOffset(sf::Vector2f offset) { m_offset = offset; return *this; }
        AnimatedTextureGenerator& setDuration(sf::Time duration) { m_duration = duration; return *this; }

        [[nodiscard]] AnimatedFrames generate(const std::string& resourceName, const std::string& filePath) const;
        [[nodiscard]] AnimatedFrames generate(const std::string& resourceName, const entt::resource<RawTexture>& rawTexture) const;
    private:
        sf::Vector2f m_size { 0.f, 0.f };
        sf::Vector2u m_placement { 1, 1 };
        sf::Vector2f m_offset { 0.f, 0.f };
        sf::Time m_duration { sf::seconds(1) };
    };

    class StaticTextureGenerator {
    public:
        StaticTextureGenerator() = default;
        StaticTextureGenerator& setSize(sf::Vector2i size) { m_size = size; return *this; }
        StaticTextureGenerator& setOffset(sf::Vector2i offset) { m_offset = offset; return *this; }

        [[nodiscard]] SpriteFrame generate(const std::string& resourceName, const std::string& filePath) const;
        [[nodiscard]] SpriteFrame generate(const std::string& resourceName, const entt::resource<game::RawTexture>& rawTexture) const;
    private:
        sf::Vector2i m_size { 0, 0 };
        sf::Vector2i m_offset { 0, 0 };
    };

} // game

#endif //ANIMATEDTEXTUREGENERATOR_HPP
