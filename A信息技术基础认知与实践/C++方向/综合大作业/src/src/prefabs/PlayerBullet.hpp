// Game - NWPU C++ sp25
// Created on 2025/5/26
// by konakona418 (https://github.com/konakona418)

#ifndef GAME25SP_PLAYERBULLET_HPP
#define GAME25SP_PLAYERBULLET_HPP

#include "SFML/System/Vector2.hpp"

#include "systems/SceneControl.hpp"
#include "components/Render.hpp"
#include "systems/CollisionControl.hpp"

namespace game::prefab {

    struct GPlayerBulletComponent {
        float damage { 0.f };
    };

    class PlayerBullet : game::TreeLike {
    public:
        enum class Type {
            Normal,
            Big,
        };

        static PlayerBullet create() { return {}; }
        static PlayerBullet create(const sf::Vector2f& pos, const Type type = Type::Big) { return PlayerBullet { pos, type }; }
    private:
        static constexpr float RENDER_LAYER = 25;
        static constexpr float SPEED = 800.f;
        static constexpr float SMALL_MAP_INDICATOR_SIZE = 24.f;
        static constexpr float SMALL_MAP_INDICATOR_OUTLINE = 6.f;
        static constexpr size_t SMALL_MAP_INDICATOR_LAYER = 253;

        PlayerBullet();
        explicit PlayerBullet(const sf::Vector2f& pos, Type type = Type::Big);

        static entt::resource<SpriteFrame> loadTexture();
        static void onUpdate(entt::entity entity, sf::Time deltaTime);
        static void makeSmallMapIndicator(entt::entity indicator);
        static std::optional<std::pair<entt::entity, sf::Vector2f>> findNearestMobPosition(entt::entity self);
    };

} // game

#endif //GAME25SP_PLAYERBULLET_HPP
