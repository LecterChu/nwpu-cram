// Game - NWPU C++ sp25
// Created on 2025/5/21
// by konakona418 (https://github.com/konakona418)

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <unordered_map>

#include "components/Render.hpp"
#include "systems/SceneControl.hpp"
#include "ResourceManager.hpp"

#include "SFML/System/Clock.hpp"


namespace game {
    struct EOnCollisionEvent;
}

namespace game::prefab {
    class Player;

    struct EOnPlayerDamageEvent {
        entt::entity player;
        float health;
    };

    struct EOnPlayerDeathEvent {
        entt::entity player;
    };

    struct GPlayerComponent {
        GPlayerComponent() = default;
        bool flipH = false;
        std::unordered_map<std::string, entt::resource<AnimatedFrames>> animations;

        float health = 100.f;

        bool attackKeyDown { false };
        sf::Clock attackCoolDown;
        sf::Clock normalAttackCoolDown;

        entt::entity hpText { entt::null };
        entt::entity mpCoolDownText { entt::null };
        bool allowCheating { false };

        bool smallMapKeyDown { false };

        explicit GPlayerComponent(std::unordered_map<std::string, entt::resource<AnimatedFrames>> animations)
            : animations(std::move(animations)) {};
    };

    class Player : public game::TreeLike {
    public:
        static Player create();

    private:
        static constexpr size_t RENDER_LAYER = 16;
        static constexpr size_t TEXT_RENDER_LAYER = 256;
        static constexpr float X_LIM = 1024.0;
        static constexpr float Y_LIM = 1024.0;
        static constexpr float DAMPING_FACTOR = 0.1f;
        static constexpr float DAMPING_FACTOR_FAST = 0.9f;
        static constexpr sf::Time ATTACK_COOLDOWN = sf::seconds(1.f);
        static constexpr sf::Time NORMAL_ATTACK_COOLDOWN = sf::seconds(0.5f);
        static constexpr size_t HP_FONT_SIZE = 24;
        static constexpr size_t MP_FONT_SIZE = 18;

        static constexpr float SMALL_MAP_INDICATOR_SIZE = 32.f;
        static constexpr float SMALL_MAP_INDICATOR_OUTLINE = 8.f;
        static constexpr size_t SMALL_MAP_INDICATOR_LAYER = 255;

        static bool canMoveTo(sf::Vector2f target);

        Player();
        static std::unordered_map<std::string, entt::resource<game::AnimatedFrames>> loadAnimationResources();
        static std::shared_ptr<sf::Image> loadCollisionTexture();
        static entt::resource<sf::Font> loadFont();
        static void onUpdate(entt::entity entity, sf::Time deltaTime);
        static void onCollision(game::EOnCollisionEvent);
        static void makeHpText(entt::entity text);
        static void makeMpCoolDownText(entt::entity text);
        static void makeSmallMapIndicator(entt::entity indicator);
    };
}


#endif //PLAYER_HPP
