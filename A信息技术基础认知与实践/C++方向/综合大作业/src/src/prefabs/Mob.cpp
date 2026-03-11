// Game - NWPU C++ sp25
// Created on 2025/5/22
// by konakona418 (https://github.com/konakona418)

#include "Mob.hpp"

#include "Bullet.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include "components/Scripts.hpp"
#include "components/Velocity.hpp"
#include "utils/TextureGenerator.hpp"
#include "utils/LazyLoader.hpp"
#include "utils/MovementUtils.hpp"
#include "Root.hpp"
#include "components/Lighting.hpp"
#include "components/Collision.hpp"
#include "PlayerBullet.hpp"

namespace game::prefab {
    Mob Mob::create() {
        return create(sf::Vector2f {0.f, 0.f});
    }

    Mob Mob::create(sf::Vector2f pos) {
        static entt::connection collisionConn;
        collisionConn = getEventDispatcher().sink<game::EOnCollisionEvent>().connect<&Mob::onCollision>();
        return Mob { pos };
    }

    Mob::Mob(sf::Vector2f pos) {
        static size_t renderOrderAccumulator = 0;

        auto& registry = game::getRegistry();
        auto entity = registry.create();
        m_entity = entity;

        game::MovementUtils::builder()
            .setLocalPosition(pos)
            .setSize({32, 48})
            .setScale({1.0, 1.0})
            .setAnchor(game::CLayout::Anchor::MiddleCenter())
            .build(entity);
        game::SceneTreeUtils::attachSceneTreeComponents(entity);

        registry.emplace<game::CRenderComponent>(entity);
        registry.emplace<game::CRenderLayerComponent>(entity, RENDER_LAYER, renderOrderAccumulator++);
        registry.emplace<game::CRenderTargetComponent>(entity, game::CRenderTargetComponent::GameComponent);

        auto animations = loadAnimationResources();
        registry.emplace<game::CAnimatedSpriteRenderComponent>(entity, (*animations)["idle"], true);
        InvokeUpdateDelegate delegate;
        delegate.connect<&Mob::mobUpdate>();

        registry.emplace<game::CScriptsComponent>(entity, delegate);
        registry.emplace<game::CVelocity>(entity);

        registry.emplace<game::CCollisionComponent>(entity);
        registry.emplace<game::CCollisionCircleComponent>(entity, 32.f);
        // on layer 4, collide with player bullets(3)
        registry.emplace<game::CCollisionLayerComponent>(entity,
                                                         CollisionUtils::getCollisionMask(4), CollisionUtils::getCollisionMask(3));

        registry.emplace<game::CLightingComponent>(entity, sf::Color(64, 96, 255, 255), 50.f);

        registry.emplace<game::prefab::GMobComponent>(entity, animations);

        auto smallMapIndicator = registry.create();
        makeSmallMapIndicator(smallMapIndicator);
        SceneTreeUtils::attachChild(entity, smallMapIndicator);
    }

    MobSharedAnimation Mob::loadAnimationResources() {
        static Lazy<MobSharedAnimation> animations {
            [] {
                auto res = std::make_shared<std::unordered_map<std::string, entt::resource<AnimatedFrames>>>();
                res->emplace("idle", ResourceManager::getAnimatedFramesCache()
                    .load(entt::hashed_string { "mobIdleAnimation"},
                    game::AnimatedTextureGenerator()
                               .setOffset(sf::Vector2f{0, 0})
                               .setPlacement(sf::Vector2u{1, 3})
                               .setSize(sf::Vector2f{32, 48})
                               .setDuration(sf::seconds(0.3))
                               .generate("mobIdle", "assets/image/slime.png")).first->second);
                return res;
            }
        };

        return *animations;
    }

    void Mob::mobUpdate(entt::entity entity, sf::Time deltaTime) {
        auto& registry = game::getRegistry();
        auto& mobComponent = registry.get<game::prefab::GMobComponent>(entity);

        if (mobComponent.health <= 0) {
            UnmountUtils::queueUnmount(entity);
            game::getEventDispatcher().trigger<EOnMobDeathEvent>(EOnMobDeathEvent { entity });
            return;
        }

        auto& playerSelector = *registry.view<game::prefab::GPlayerComponent>().begin();
        if (!registry.valid(playerSelector)) {
            auto& velocityComponent = registry.get<game::CVelocity>(entity);
            velocityComponent.setAcceleration(sf::Vector2f {0, 0});
            velocityComponent.setVelocity(sf::Vector2f {0, 0});
            return;
        }

        const auto& playerPos = registry.get<game::CGlobalTransform>(playerSelector).getPosition();
        const auto& mobPos = registry.get<game::CGlobalTransform>(entity).getPosition();
        auto delta = (playerPos - mobPos).normalized();

        if (mobComponent.attackClock.getElapsedTime() > GMobComponent::ATTACK_INTERVAL && randomBool(0.75f)) {
            Bullet bullet = Bullet::create(mobPos, delta, random(100.f, 200.f));
            mobComponent.bullets.push_back(bullet.getEntity());

            auto& root = game::prefab::Root::create();
            root.mountChild(bullet.getEntity());

            if (mobComponent.bullets.size() > GMobComponent::MAX_BULLET_NUM) {
                SceneTreeUtils::unmount(mobComponent.bullets.front());
                mobComponent.bullets.pop_front();
            }

            mobComponent.attackClock.restart();
        }

        if (mobComponent.moveClock.getElapsedTime() > GMobComponent::MOVE_INTERVAL && randomBool(0.75f)) {
            auto& velocityComponent = registry.get<game::CVelocity>(entity);

            auto velocity = (delta + random({-0.1f, 0.1f}, {-0.1f, 0.1f})) * random(50.f, 100.f);
            auto acceleration = -velocity / (random(1.0f, 1.5f) * GMobComponent::MOVE_INTERVAL.asSeconds());

            velocityComponent.setAcceleration(acceleration);
            velocityComponent.setVelocity(velocity);

            // the asset is facing left, so we need to flip it back.
            // this behavior is quite absurd, so
            // use a better asset.
            if (velocity.x > 0) {
                mobComponent.flipH = true;
            } else {
                mobComponent.flipH = false;
            }

            mobComponent.moveClock.restart();
        }

        game::MovementUtils::flipHorizontal(entity, mobComponent.flipH);
    }

    void Mob::onCollision(game::EOnCollisionEvent e) {
        auto& registry = game::getRegistry();
        auto pair = game::which<game::prefab::GPlayerBulletComponent, game::prefab::GMobComponent>(e.collider1, e.collider2);
        if (pair) {
            auto& playerBulletComponent = registry.get<game::prefab::GPlayerBulletComponent>(pair->first);
            auto& mobComponent = registry.get<game::prefab::GMobComponent>(pair->second);
            mobComponent.health -= playerBulletComponent.damage;

            UnmountUtils::queueUnmount(pair->first);

            getEventDispatcher().trigger<EOnMobHitEvent>(EOnMobHitEvent { pair->second });
        }
    }

    void Mob::makeSmallMapIndicator(entt::entity indicator) {
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
        circleShape->setFillColor(sf::Color(255, 96, 96, 196));
        circleShape->setOutlineColor(sf::Color(255, 255, 255, 196));
        circleShape->setOutlineThickness(SMALL_MAP_INDICATOR_OUTLINE);

        auto uniqueShape = std::unique_ptr<sf::CircleShape>(circleShape);
        registry.emplace<game::CShapeRenderComponent>(indicator, std::move(uniqueShape));
    }
} // game