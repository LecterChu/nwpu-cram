// Game - NWPU C++ sp25
// Created on 2025/5/26
// by konakona418 (https://github.com/konakona418)

#include <cmath>

#include "PlayerBullet.hpp"
#include "utils/MovementUtils.hpp"
#include "components/Render.hpp"
#include "components/Velocity.hpp"
#include "components/Collision.hpp"
#include "components/Lighting.hpp"
#include "components/Scripts.hpp"
#include "utils/LazyLoader.hpp"
#include "ResourceManager.hpp"
#include "utils/TextureGenerator.hpp"

#include "Mob.hpp"

namespace game::prefab {
    PlayerBullet::PlayerBullet() : PlayerBullet({0.f, 0.f}) {
    }

    PlayerBullet::PlayerBullet(const sf::Vector2f& pos, const Type type) : game::TreeLike() {
        static size_t renderOrderAccumulator = 0;

        auto& registry = game::getRegistry();
        auto entity = registry.create();
        m_entity = entity;

        sf::Vector2f scale;
        float lightRadius;
        float damage;

        if (type == Type::Big) {
            scale = {1.f, 1.f};
            lightRadius = 36.f;
            damage = 100.f;
        } else {
            scale = {0.3f, 0.3f};
            lightRadius = 16.f;
            damage = 25.f;
        }

        game::MovementUtils::builder()
                .setLocalPosition(pos)
                .setSize({32.f, 32.f})
                .setScale(scale)
                .setAnchor(game::CLayout::Anchor::MiddleCenter())
                .build(entity);
        game::SceneTreeUtils::attachSceneTreeComponents(entity);

        registry.emplace<CVelocity>(entity);

        registry.emplace<game::CRenderComponent>(entity);
        registry.emplace<game::CRenderLayerComponent>(entity, RENDER_LAYER, renderOrderAccumulator++);
        registry.emplace<game::CRenderTargetComponent>(entity, game::CRenderTargetComponent::GameComponent);

        auto frame = loadTexture();
        registry.emplace<game::CSpriteRenderComponent>(entity, frame);

        registry.emplace<game::CCollisionComponent>(entity);
        registry.emplace<game::CCollisionCircleComponent>(entity, 16.f);
        // on layer 3, collide with mobs(4)
        registry.emplace<game::CCollisionLayerComponent>(entity,
                                                         CollisionUtils::getCollisionMask(3), CollisionUtils::getCollisionMask(4));

        game::InvokeUpdateDelegate delegate;
        delegate.connect<&PlayerBullet::onUpdate>();
        registry.emplace<game::CScriptsComponent>(entity, delegate);

        registry.emplace<game::CLightingComponent>(entity, sf::Color(255, 192, 203, 240), lightRadius);

        auto& bulletComponent = registry.emplace<game::prefab::GPlayerBulletComponent>(entity);
        bulletComponent.damage = damage;

        auto smallMapIndicator = registry.create();
        makeSmallMapIndicator(smallMapIndicator);
        SceneTreeUtils::attachChild(entity, smallMapIndicator);
    }

    entt::resource<SpriteFrame> PlayerBullet::loadTexture() {
        static Lazy texture = Lazy<entt::resource<SpriteFrame>> {
                []() {
                    entt::resource<SpriteFrame> texture =
                            ResourceManager::getSpriteFrameCache().load(
                                            entt::hashed_string {  "bulletSprite" },
                                            StaticTextureGenerator()
                                                    .setOffset({0, 0})
                                                    .setSize({32, 32})
                                                    .generate("bullet", "assets/image/bullet.png"))
                                    .first->second;
                    return texture;
                }
        };
        return *texture;
    }

    void PlayerBullet::onUpdate(entt::entity entity, sf::Time deltaTime) {
        auto& registry = game::getRegistry();
        auto bulletPos = registry.get<game::CGlobalTransform>(entity).getPosition();
        constexpr sf::Vector2f bound { 1024.0, 1024.0 };

        if (game::MovementUtils::isOutOfMapBounds(entity, -bound, bound, bulletPos)) {
            UnmountUtils::queueUnmount(entity);
        }

        auto maybeTarget = findNearestMobPosition(entity);
        if (maybeTarget.has_value()) {
            auto& velocity = registry.get<game::CVelocity>(entity);

            auto [target, targetPosition] = maybeTarget.value();
            auto normal = (targetPosition - bulletPos).normalized();
            auto lerped = game::lerp(velocity.getVelocity(), normal * SPEED, 0.05f);
            velocity.setVelocity(lerped);
        }
    }

    std::optional<std::pair<entt::entity, sf::Vector2f>> PlayerBullet::findNearestMobPosition(entt::entity self) {
        auto& registry = game::getRegistry();
        auto bulletPos = registry.get<game::CGlobalTransform>(self).getPosition();

        entt::entity target { entt::null };
        float minDistance = std::numeric_limits<float>::max();
        sf::Vector2f targetPosition;

        registry.view<GMobComponent>().each([&](entt::entity entity, const GMobComponent&) {
            auto mobPosition = registry.get<game::CGlobalTransform>(entity).getPosition();
            auto distance = (mobPosition - bulletPos).lengthSquared();
            if (distance < minDistance) {
                minDistance = distance;
                target = entity;
                targetPosition = mobPosition;
            }
        });

        if (target != entt::null) {
            return std::make_pair(target, targetPosition);
        }
        return std::nullopt;
    }

    void PlayerBullet::makeSmallMapIndicator(entt::entity indicator) {
        auto& registry = game::getRegistry();

        game::MovementUtils::builder()
                .setLocalPosition({0.f, 0.f})
                .setSize({SMALL_MAP_INDICATOR_SIZE, 0.f})
                .setScale({1.0, 1.0})
                .setAnchor(game::CLayout::Anchor::MiddleCenter())
                .build(indicator);
        SceneTreeUtils::attachSceneTreeComponents(indicator);

        registry.emplace<game::CRenderComponent>(indicator);
        registry.emplace<game::CRenderLayerComponent>(indicator, SMALL_MAP_INDICATOR_LAYER, 0);
        registry.emplace<game::CRenderTargetComponent>(indicator, game::CRenderTargetComponent::SmallMap);

        auto* circleShape = new sf::CircleShape(SMALL_MAP_INDICATOR_SIZE);
        circleShape->setFillColor(sf::Color(96, 196, 255, 196));
        circleShape->setOutlineColor(sf::Color(255, 255, 255, 196));
        circleShape->setOutlineThickness(SMALL_MAP_INDICATOR_OUTLINE);

        auto uniqueShape = std::unique_ptr<sf::CircleShape>(circleShape);
        registry.emplace<game::CShapeRenderComponent>(indicator, std::move(uniqueShape));
    }
} // game