// Game - NWPU C++ sp25
// Created on 2025/5/21
// by konakona418 (https://github.com/konakona418)

#ifndef MUSIC_HPP
#define MUSIC_HPP
#include <entt/resource/resource.hpp>

#include "ResourceManager.hpp"
#include "SFML/Audio/Music.hpp"


namespace game {
    struct MixerConfig {
        float volumeMultiplier { 1.0f };
        MixerConfig() = default;
    };

    struct MusicConfig {
        float volume { 100.f };
        bool loop { false };

        MusicConfig() = default;
        MusicConfig(float volume, bool loop) : volume(volume), loop(loop) {}
        explicit MusicConfig(float volume) : volume(volume) {}
        explicit MusicConfig(bool loop) : loop(loop) {}
    };

    struct CMusicComponent {
        entt::resource<BinaryFile> musicData;
        std::shared_ptr<sf::Music> musicRef;
        MusicConfig config;
        bool launched { false };

        explicit CMusicComponent(entt::resource<BinaryFile> musicData, MusicConfig config = {});
        [[nodiscard]] sf::Music::Status getStatus() const;
        void setStatus(sf::Music::Status status) const;
        void update(const MixerConfig& mixerConfig);

        [[nodiscard]] bool shouldDispose() const;
    };
}



#endif //MUSIC_HPP
