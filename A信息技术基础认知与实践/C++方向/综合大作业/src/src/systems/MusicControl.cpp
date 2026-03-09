// Game - NWPU C++ sp25
// Created on 2025/5/21
// by konakona418 (https://github.com/konakona418)

#include "MusicControl.hpp"

#include "Common.hpp"
#include "Logger.hpp"
#include "components/Music.hpp"

void game::SMusicSystem::update() {
    auto& registry = getRegistry();
    for (auto [entity, music] : registry.view<CMusicComponent>().each()) {
        if (music.shouldDispose()) {
            getLogger().logDebug("Music disposed: " + music.musicData->name);
            registry.destroy(entity);
            continue;
        }
        music.update(getMixerConfig());
    }
}

void game::SMusicSystem::setMixerConfig(MixerConfig mixerConfig) {
    getMixerConfig() = mixerConfig;
}

game::MixerConfig& game::SMusicSystem::getMixerConfig() {
    static MixerConfig m_mixerConfig;
    return m_mixerConfig;
}

void game::SMusicSystem::playMusic(entt::resource<BinaryFile> musicData, MusicConfig config) {
    if (musicData->data.empty()) {
        return;
    }
    auto& registry = getRegistry();
    auto entity = registry.create();
    registry.emplace<CMusicComponent>(entity, musicData, config);
}
