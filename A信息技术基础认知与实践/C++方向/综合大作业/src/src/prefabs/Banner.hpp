// Game - NWPU C++ sp25
// Created on 2025/5/27
// by konakona418 (https://github.com/konakona418)

#ifndef GAME25SP_BANNER_HPP
#define GAME25SP_BANNER_HPP

#include "systems/SceneControl.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

namespace game::prefab {

    struct EOnBannerCompleteEvent {
        entt::entity banner;
    };

    struct GBannerComponent {
        enum class BannerState {
            BANNER_IDLE = 0,
            BANNER_READY = 1,
            BANNER_FADE_IN,
            BANNER_DISPLAY,
            BANNER_FADE_OUT,
        };

        entt::entity bannerText { entt::null };
        BannerState bannerState { BannerState::BANNER_IDLE };
        sf::String textString { "PLACEHOLDER" };
    };

    class Banner : public game::TreeLike {
    public:
        static Banner create();
        void launch();
        void setText(const sf::String& text);
    private:
        static constexpr size_t RENDER_LAYER = 512;
        static constexpr size_t TEXT_FONT_SIZE = 96;
        static constexpr sf::Color TEXT_COLOR = sf::Color::White;

        Banner();
        static entt::resource<sf::Font> loadBannerFont();
        static void makeContainer(entt::entity container);
        static void makeText(entt::entity text);
        static void onUpdate(entt::entity entity, sf::Time deltaTime);
        static void onTweenUpdate(entt::entity entity, float value);
        static void onTweenComplete(entt::entity entity);
        static float getTextWidth(const sf::String& text);
    };

} // game

#endif //GAME25SP_BANNER_HPP
