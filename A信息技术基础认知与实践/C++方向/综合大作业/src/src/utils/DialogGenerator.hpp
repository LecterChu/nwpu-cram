// Game - NWPU C++ sp25
// Created on 2025/5/24
// by konakona418 (https://github.com/konakona418)

#ifndef DIALOGGENERATOR_HPP
#define DIALOGGENERATOR_HPP

#include <nlohmann/json.hpp>

#include "ResourceManager.hpp"

namespace game {

class DialogGenerator {
public:
    DialogGenerator() = default;
    ~DialogGenerator() = default;

    DialogGenerator& addSpeaker(const sf::String& name, const sf::Color& color,
                                std::optional<entt::resource<Texture>> portrait = std::nullopt,
                                sf::Vector2f portraitScalingFactor = {1.0f, 1.0f}, size_t* outId = nullptr);
    DialogGenerator& addLine(size_t speakerId, const sf::String& text);

    DialogGenerator& fromJson(const std::string& jsonFilePath);

    DialogCollection generate();
private:

    static sf::Color fromHex(const std::string& hex);

    DialogCollection m_dialogCollection {};
    size_t m_currentSpeakerId = 0;
};

} // game

#endif //DIALOGGENERATOR_HPP
