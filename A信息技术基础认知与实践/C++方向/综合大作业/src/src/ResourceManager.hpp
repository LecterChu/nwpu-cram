// Game - NWPU C++ sp25
// Created on 2025/5/16
// by konakona418 (https://github.com/konakona418)

#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <entt/resource/cache.hpp>

#include "components/Render.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Shader.hpp"


namespace game {
    struct BinaryFile {
        std::string name {};
        std::vector<uint8_t> data;

        explicit BinaryFile(const std::string& name) {
            this->name = name;
            data.resize(std::filesystem::file_size(name));
            std::ifstream file(name, std::ios::binary);
            file.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(data.size()));
            file.close();
        }
    };

    struct BinaryFileLoader {
        using result_type = std::shared_ptr<BinaryFile>;
        result_type operator()(const std::string& name) const {
            return std::make_shared<BinaryFile>(name);
        }
    };

    using BinaryFileCache = entt::resource_cache<BinaryFile, BinaryFileLoader>;

    struct RawTexture {
        sf::Texture texture;

        explicit RawTexture(const std::string& filename) : texture(filename) {};
    };

    struct RawTextureLoader {
        using result_type = std::shared_ptr<RawTexture>;

        result_type operator()(const std::string& name) const {
            return std::make_shared<RawTexture>(name);
        }
    };

    using RawTextureCache = entt::resource_cache<RawTexture, RawTextureLoader>;

    struct Texture {
        entt::resource<RawTexture> rawTextureRef;
        std::optional<sf::IntRect> textureRect { std::nullopt };

        explicit Texture(entt::resource<RawTexture> texture) : rawTextureRef(std::move(texture)) {};

        Texture(entt::resource<RawTexture> texture, const sf::IntRect& rect) : rawTextureRef(std::move(texture)), textureRect(rect) {};
    };

    struct TextureLoader {
        using result_type = std::shared_ptr<Texture>;

        result_type operator()(entt::resource<RawTexture> texture) const {
            return std::make_shared<Texture>(std::move(texture));
        }

        result_type operator()(entt::resource<RawTexture> texture, const sf::IntRect& rect) const {
            return std::make_shared<Texture>(std::move(texture), rect);
        }

        result_type operator()(const std::string& fileName);

        result_type operator()(const std::string& fileName, const sf::IntRect& rect);
    };

    using TextureCache = entt::resource_cache<Texture, TextureLoader>;

    struct SpriteFrameLoader {
        using result_type = std::shared_ptr<SpriteFrame>;

        result_type operator()(const SpriteFrame& frame) const {
            return std::make_shared<SpriteFrame>(frame);
        }
    };

    using SpriteFrameCache = entt::resource_cache<SpriteFrame, SpriteFrameLoader>;

    struct AnimatedFramesLoader {
        using result_type = std::shared_ptr<AnimatedFrames>;

        result_type operator()(const AnimatedFrames& frames) const {
            return std::make_shared<AnimatedFrames>(frames);
        }
    };

    using AnimatedFramesCache = entt::resource_cache<AnimatedFrames, AnimatedFramesLoader>;

    struct FontLoader {
        using result_type = std::shared_ptr<sf::Font>;

        result_type operator()(const std::string& name) const {
            auto font = std::make_shared<sf::Font>();
            if (!font->openFromFile(name)) {
                throw std::runtime_error("Failed to load font: " + name);
            }
            return font;
        }

        result_type operator()(const uint8_t* buf, size_t size) const {
            auto font = std::make_shared<sf::Font>();
            if (!font->openFromMemory(buf, size)) {
                throw std::runtime_error("Failed to load font from memory");
            }
            return font;
        }

        result_type operator()(const std::vector<uint8_t>& buf) const {
            return operator()(buf.data(), buf.size());
        }

        result_type operator()(sf::Font&& font) {
            return std::make_shared<sf::Font>(std::forward<sf::Font>(font));
        }
    };

    using FontCache = entt::resource_cache<sf::Font, FontLoader>;

    struct DialogLine {
        sf::String text;
        size_t speakerId;
    };

    struct DialogSpeaker {
        sf::String name;
        sf::Color nameColor { sf::Color::White };
        std::optional<entt::resource<Texture>> portrait;
        sf::Vector2f portraitScalingFactor { 1.0f, 1.0f };
    };

    struct DialogCollection {
        std::unordered_map<size_t, DialogSpeaker> speakers;
        std::vector<DialogLine> lines;

        DialogSpeaker getSpeaker(size_t id) {
            if (speakers.find(id) == speakers.end()) {
                speakers[id] = DialogSpeaker();
            }
            return speakers[id];
        }
    };

    struct DialogLoader {
        using result_type = std::shared_ptr<DialogCollection>;

        result_type operator()(const DialogCollection& collection) const {
            return std::make_shared<DialogCollection>(collection);
        }
    };

    using DialogCache = entt::resource_cache<DialogCollection, DialogLoader>;

    struct ShaderLoader {
        using result_type = std::shared_ptr<sf::Shader>;

        result_type operator()(const std::string& fileName, sf::Shader::Type type) const {
            auto shader = std::make_shared<sf::Shader>();
            if (!shader->loadFromFile(fileName, type)) {
                throw std::runtime_error("Failed to load shader: " + fileName);
            }
            return shader;
        }

        result_type operator()(const std::string& vertFileName, const std::string& fragFileName) {
            auto shader = std::make_shared<sf::Shader>();
            if (!shader->loadFromFile(vertFileName, fragFileName)) {
                throw std::runtime_error("Failed to load shader: " + vertFileName + " " + fragFileName);
            }
            return shader;
        }
    };

    using ShaderCache = entt::resource_cache<sf::Shader, ShaderLoader>;

    struct ResourceManager {
        ResourceManager() = default;

        static BinaryFileCache& getBinaryFileCache() {
            static BinaryFileCache cache;
            return cache;
        }

        static TextureCache& getTextureCache() {
            static TextureCache cache;
            return cache;
        }

        static RawTextureCache& getRawTextureCache() {
            static RawTextureCache cache;
            return cache;
        }

        static SpriteFrameCache& getSpriteFrameCache() {
            static SpriteFrameCache cache;
            return cache;
        }

        static AnimatedFramesCache& getAnimatedFramesCache() {
            static AnimatedFramesCache cache;
            return cache;
        }

        static FontCache& getFontCache() {
            static FontCache cache;
            return cache;
        }

        static DialogCache& getDialogCache() {
            static DialogCache cache;
            return cache;
        }

        static ShaderCache& getShaderCache() {
            static ShaderCache cache;
            return cache;
        }
    };

}



#endif //RESOURCE_HPP
