// Game - NWPU C++ sp25
// Created on 2025/5/28
// by konakona418 (https://github.com/konakona418)

#ifndef GAME25SP_SPLASHSCREEN_HPP
#define GAME25SP_SPLASHSCREEN_HPP

#include "entt/resource/resource.hpp"
#include "components/Render.hpp"
#include "systems/SceneControl.hpp"

namespace game::prefab {

    struct EOnSplashScreenCompletedEvent {
        entt::entity entity;
    };

    struct GSplashScreenComponent {
        enum class SplashScreenState {
            SPLASH_SCREEN_IDLE,
            SPLASH_SCREEN_FADE_IN,
            SPLASH_SCREEN_WAIT,
            SPLASH_SCREEN_FADE_OUT,
        };

        SplashScreenState splashScreenState { SplashScreenState::SPLASH_SCREEN_FADE_IN };
    };

    class SplashScreen : game::TreeLike {
    public:
        static SplashScreen create() { return {}; };
    private:
        static constexpr float SPLASH_SCREEN_PHASE_DURATION = 1.0f;

        SplashScreen();
        static entt::resource<game::SpriteFrame> loadImage();
        static void onTweenCompleted(entt::entity entity);
        static void onTweenUpdate(entt::entity entity, float progress);

    };

} // game

#endif //GAME25SP_SPLASHSCREEN_HPP
