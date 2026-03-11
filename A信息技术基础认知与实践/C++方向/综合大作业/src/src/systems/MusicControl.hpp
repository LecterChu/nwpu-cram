// Game - NWPU C++ sp25
// Created on 2025/5/21
// by konakona418 (https://github.com/konakona418)

#ifndef MUSICCONTROL_HPP
#define MUSICCONTROL_HPP
#include "components/Music.hpp"

namespace game {

    class SMusicSystem {
    public:
        SMusicSystem() = default;
        static void update();
        static void setMixerConfig(MixerConfig mixerConfig);
        [[nodiscard]] static MixerConfig& getMixerConfig();

        static void playMusic(entt::resource<BinaryFile> musicData, MusicConfig musicConfig = {});

    };

} // game

#endif //MUSICCONTROL_HPP
