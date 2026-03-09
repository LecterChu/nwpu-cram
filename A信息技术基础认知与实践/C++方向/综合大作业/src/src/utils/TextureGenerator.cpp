// Game - NWPU C++ sp25
// Created on 2025/5/20
// by konakona418 (https://github.com/konakona418)

#include "TextureGenerator.hpp"

#include <entt/core/hashed_string.hpp>

#include "Common.hpp"
#include "Logger.hpp"
#include "ResourceManager.hpp"

namespace game {
    AnimatedFrames AnimatedTextureGenerator::generate(const std::string& resourceName, const std::string& filePath) const {
        auto rawTextureResult = ResourceManager::getRawTextureCache().load(entt::hashed_string { resourceName.c_str() }, filePath);
        if (!rawTextureResult.second) {
            getLogger().logWarn("Failed to load raw texture: " + filePath + ". Existing resource with the same name already exists!");
        }
        auto rawTexture = rawTextureResult.first->second;
        return generate(resourceName, rawTexture);
    }

    AnimatedFrames AnimatedTextureGenerator::generate(const std::string& resourceName, const entt::resource<RawTexture>& rawTexture) const {
        AnimatedFrames animatedFrames;

        auto sizeX = static_cast<int>(m_size.x);
        auto sizeY = static_cast<int>(m_size.y);
        auto offsetX = static_cast<int>(m_offset.x);
        auto offsetY = static_cast<int>(m_offset.y);

        if (sizeX == 0 || sizeY == 0) {
            getLogger().logError("Invalid tile size provided");
        }

        if (m_placement.x == 0 || m_placement.y == 0) {
            getLogger().logError("Invalid tile placement provided");
        }

        for (int i = 0; i < m_placement.x; i++) {
            for (int j = 0; j < m_placement.y; j++) {
                auto texture = ResourceManager::getTextureCache().load(
                    entt::hashed_string { (resourceName + "_sep_" + std::to_string(i) + std::to_string(j)).c_str() },
                    rawTexture,
                    sf::IntRect {
                        {i * (sizeX + offsetX), j * (sizeY + offsetY)},
                        {sizeX, sizeY} }).first->second;
                animatedFrames.frames.push_back(texture);
            }
        }

        animatedFrames.duration = m_duration;
        animatedFrames.loop = true;
        animatedFrames.animationName = entt::hashed_string { resourceName.c_str() };
        return animatedFrames;
    }

    SpriteFrame StaticTextureGenerator::generate(const std::string& resourceName, const std::string& filePath) const {
        auto rawTextureResult = ResourceManager::getRawTextureCache().load(entt::hashed_string { resourceName.c_str() }, filePath);
        if (!rawTextureResult.second) {
            getLogger().logWarn("Failed to load raw texture: " + filePath + ". Existing resource with the same name already exists!");
        }
        auto rawTexture = rawTextureResult.first->second;
        return generate(resourceName, rawTexture);
    }

    SpriteFrame StaticTextureGenerator::generate(const std::string& resourceName,
        const entt::resource<RawTexture>& rawTexture) const {
        sf::IntRect rect { m_offset, m_size };
        return SpriteFrame { ResourceManager::getTextureCache().load(
            entt::hashed_string { resourceName.c_str() },
            rawTexture,
            rect).first->second
        };
    }
} // game