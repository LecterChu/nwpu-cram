// Game - NWPU C++ sp25
// Created on 2025/5/21
// by konakona418 (https://github.com/konakona418)

#include "Music.hpp"

#include "Common.hpp"
#include "Logger.hpp"

game::CMusicComponent::CMusicComponent(entt::resource<BinaryFile> musicData, game::MusicConfig config) {
    this->musicData = std::move(musicData);
    this->config = config;
    musicRef = std::make_shared<sf::Music>();

    if(!musicRef->openFromMemory(this->musicData->data.data(), this->musicData->data.size())) {
        getLogger().logError("Failed to load music: " + this->musicData->name);
    }
    getLogger().logInfo("Loaded music: " + this->musicData->name);
    musicRef->setVolume(config.volume);
    musicRef->setLooping(config.loop);
}

sf::Music::Status game::CMusicComponent::getStatus() const {
    return musicRef->getStatus();
}

void game::CMusicComponent::setStatus(sf::Music::Status status) const {
    switch (status) {
        case sf::Music::Status::Stopped:
            musicRef->stop();
            break;
        case sf::Music::Status::Paused:
            musicRef->pause();
            break;
        case sf::Music::Status::Playing:
            musicRef->play();
            break;
        default:
            getLogger().logError("Invalid music status");
            break;
    }
}

void game::CMusicComponent::update(const MixerConfig& mixerConfig) {
    musicRef->setVolume(mixerConfig.volumeMultiplier * config.volume);
    if (!launched) {
        setStatus(sf::Music::Status::Playing);
        launched = true;
    }
}

bool game::CMusicComponent::shouldDispose() const {
    return (getStatus() == sf::Music::Status::Stopped) && !config.loop && launched;
}
