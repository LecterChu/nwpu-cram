// Game - NWPU C++ sp25
// Created on 2025/5/24
// by konakona418 (https://github.com/konakona418)

#include "DialogGenerator.hpp"

namespace game {
    DialogGenerator& DialogGenerator::addSpeaker(const sf::String& name, const sf::Color& color,
                                                 std::optional<entt::resource<Texture>> portrait,
                                                 sf::Vector2f portraitScalingFactor, size_t* outId) {
        if (outId != nullptr) {
            *outId = m_currentSpeakerId;
        }

        m_dialogCollection.speakers.insert({m_currentSpeakerId++, DialogSpeaker {name, color, std::move(portrait), portraitScalingFactor} });
        return *this;
    }

    DialogGenerator& DialogGenerator::addLine(size_t speakerId, const sf::String& text) {
        m_dialogCollection.lines.push_back(DialogLine{text, speakerId});
        return *this;
    }

    DialogCollection DialogGenerator::generate() {
        return m_dialogCollection;
    }

    DialogGenerator &DialogGenerator::fromJson(const std::string& jsonFilePath) {
        std::ifstream jsonFile(jsonFilePath);
        nlohmann::json json = nlohmann::json::parse(jsonFile);
        for (auto& speaker : json["speakers"]) {
            std::optional<entt::resource<Texture>> portrait;

            auto name = speaker["name"].get<std::string>();
            auto portraitFileName = speaker["portrait"].get<std::string>();
            auto hexColorString = speaker["color"].get<std::string>();

            auto scalingFactor = speaker["portrait_scaling_factor"];
            auto portraitScalingFactorX = scalingFactor[0].get<float>();
            auto portraitScalingFactorY = scalingFactor[1].get<float>();

            auto textureRect = speaker["texture_rect"];
            auto textureRectBeginX = textureRect[0].get<int>();
            auto textureRectBeginY = textureRect[1].get<int>();
            auto textureRectWidth = textureRect[2].get<int>();
            auto textureRectHeight = textureRect[3].get<int>();

            if (!portraitFileName.empty()) {
                portrait = ResourceManager::getTextureCache()
                        .load(entt::hashed_string{portraitFileName.c_str()},
                              portraitFileName,
                              sf::IntRect{{textureRectBeginX, textureRectBeginY},
                                          {textureRectWidth,  textureRectHeight}}).first->second;
            } else {
                portrait = std::nullopt;
            }

            addSpeaker(sf::String::fromUtf8(name.begin(), name.end()), fromHex(hexColorString), std::move(portrait),
                       sf::Vector2f {portraitScalingFactorX, portraitScalingFactorY});
        }

        for (auto& line : json["lines"]) {
            auto str = line["text"].get<std::string>();
            addLine(line["speaker_id"].get<size_t>(), sf::String::fromUtf8(str.begin(), str.end()));
        }
        return *this;
    }

    sf::Color DialogGenerator::fromHex(const std::string &hex) {
        return sf::Color {static_cast<uint8_t>(std::stoi(hex.substr(1, 2), nullptr, 16)),
                         static_cast<uint8_t>(std::stoi(hex.substr(3, 2), nullptr, 16)),
                         static_cast<uint8_t>(std::stoi(hex.substr(5, 2), nullptr, 16))};
    }
} // game