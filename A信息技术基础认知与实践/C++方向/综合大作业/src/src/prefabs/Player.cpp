// Game - NWPU C++ sp25
// Created on 2025/5/21
// by konakona418 (https://github.com/konakona418)

#include "Player.hpp"

#include "PlayerBullet.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include "components/Collision.hpp"
#include "components/Layout.hpp"
#include "components/Scripts.hpp"
#include "components/Lighting.hpp"
#include "systems/CollisionControl.hpp"
#include "systems/MovementControl.hpp"
#include "systems/SceneControl.hpp"
#include "utils/TextureGenerator.hpp"
#include "utils/LazyLoader.hpp"
#include "utils/MovementUtils.hpp"
#include "Window.hpp"

void game::prefab::Player::onUpdate(entt::entity entity, sf::Time deltaTime) {
    auto& registry = game::getRegistry();
    auto& game = game::getGame();
    auto& keyboard = game.getKeyboard();

    auto& player = registry.get<game::prefab::GPlayerComponent>(entity);

    sf::Vector2f velocity = sf::Vector2f{0, 0};
    if (keyboard.isKeyPressed(sf::Keyboard::Key::Up)) {
        velocity.y = -1;
    }
    if (keyboard.isKeyPressed(sf::Keyboard::Key::Down)) {
        velocity.y = 1;
    }
    if (keyboard.isKeyPressed(sf::Keyboard::Key::Left)) {
        velocity.x = -1;
    }
    if (keyboard.isKeyPressed(sf::Keyboard::Key::Right)) {
        velocity.x = 1;
    }
    if (keyboard.isKeyPressed(sf::Keyboard::Key::LShift)) {
        game.setTimeScale(0.5f);
    } else {
        game.setTimeScale(1.0f);
    }

    if (keyboard.isKeyPressed(sf::Keyboard::Key::M)) {
        player.smallMapKeyDown = true;
    }
    if (keyboard.isKeyReleased(sf::Keyboard::Key::M) && player.smallMapKeyDown) {
        auto& window = game.getWindow();
        window.setSmallMapVisibility(!window.isSmallMapVisible());
        player.smallMapKeyDown = false;
    }

    if (keyboard.isKeyPressed(sf::Keyboard::Key::F1)) {
        player.allowCheating = true;
        player.health = 100.f;
    }

    if (velocity.x < 0) {
        player.flipH = true;
    }
    else if (velocity.x > 0) {
        player.flipH = false;
    }

    auto& animatedSprite = registry.get<game::CAnimatedSpriteRenderComponent>(entity);
    if (velocity.lengthSquared() > 0) {
        animatedSprite.setFrames(player.animations["walk"]);
    }
    else {
        animatedSprite.setFrames(player.animations["idle"]);
    }

    game::MovementUtils::flipHorizontal(entity, player.flipH);

    auto& localTransform = registry.get<game::CLocalTransform>(entity);
    auto position = localTransform.getPosition();
    auto destination = localTransform.getPosition() + velocity * 400.0f * deltaTime.asSeconds();
    if (canMoveTo(destination)) {
        game::MovementUtils::move(entity, destination - position);
    }

    auto& window = getGame().getWindow();
    auto lastCameraPosition = window.getViewCenter();
    auto lerpedPosition = lerp(lastCameraPosition, destination, DAMPING_FACTOR, deltaTime);
    window.setViewCenter(lerpedPosition);

    if (keyboard.isKeyPressed(sf::Keyboard::Key::X) && (player.attackCoolDown.getElapsedTime() > ATTACK_COOLDOWN || player.allowCheating)) {
        player.attackKeyDown = true;
    }
    if (keyboard.isKeyReleased(sf::Keyboard::Key::X) && player.attackKeyDown) {
        game::prefab::PlayerBullet::create(position);
        player.attackKeyDown = false;
        player.attackCoolDown.restart();
    }

    if (keyboard.isKeyPressed(sf::Keyboard::Key::Z) && player.normalAttackCoolDown.getElapsedTime() > NORMAL_ATTACK_COOLDOWN) {
        game::prefab::PlayerBullet::create(position, PlayerBullet::Type::Normal);
        player.normalAttackCoolDown.restart();
    }

    auto& mpTextRenderComponent = registry.get<game::CTextRenderComponent>(player.mpCoolDownText);
    float mpCoolDownRatio = std::clamp(player.attackCoolDown.getElapsedTime().asSeconds() / ATTACK_COOLDOWN.asSeconds(), 0.f, 1.f) * 100.f;
    mpTextRenderComponent.setText(std::to_string(static_cast<int32_t>(std::ceil(mpCoolDownRatio))) + "%");

    auto& hpTextRenderComponent = registry.get<game::CTextRenderComponent>(player.hpText);
    hpTextRenderComponent.setText(std::to_string(static_cast<int32_t>(std::floor(player.health)))
        + (player.allowCheating ? "*" : ""));

    auto lerpedPositionFast = lerp(lastCameraPosition, destination, DAMPING_FACTOR_FAST);
    auto& hpTextLocalTransform = registry.get<game::CLocalTransform>(player.hpText);
    MovementUtils::setPosition(player.hpText, lerpedPositionFast + sf::Vector2f{18.f, -24.f});

    auto& mpCoolDownTextLocalTransform = registry.get<game::CLocalTransform>(player.mpCoolDownText);
    MovementUtils::setPosition(player.mpCoolDownText, lerpedPositionFast + sf::Vector2f{18.f, 0.f});
};

void game::prefab::Player::onCollision(game::EOnCollisionEvent e) {
    auto& registry = game::getRegistry();
    auto entity1 = e.collider1;
    auto entity2 = e.collider2;

    auto pair = game::which<
        game::prefab::GPlayerComponent,
        game::prefab::GBulletComponent>(entity1, entity2);
    if (pair) {
        auto& playerComponent = registry.get<game::prefab::GPlayerComponent>(pair->first);
        UnmountUtils::queueUnmount(pair->second);

        if (!playerComponent.allowCheating) {
            playerComponent.health -= 10;
        } else {
            getLogger().logDebug("Using cheating mode, player health unchanged");
        }

        game::getLogger().logDebug("Player health: " + std::to_string(playerComponent.health));

        game::getEventDispatcher().trigger<EOnPlayerDamageEvent>({ pair->first, playerComponent.health });

        if (playerComponent.health <= 0) {
            UnmountUtils::queueUnmount(pair->first);
            game::getLogger().logInfo("Player died!");
            game::getEventDispatcher().trigger<EOnPlayerDeathEvent>({ pair->first });

            UnmountUtils::queueUnmount(playerComponent.hpText);
            UnmountUtils::queueUnmount(playerComponent.mpCoolDownText);
        }
    }
}

game::prefab::Player game::prefab::Player::create() {
    static entt::connection collisionConn;
    collisionConn = game::getEventDispatcher().sink<game::EOnCollisionEvent>().connect<&onCollision>();
    return {};
}

game::prefab::Player::Player() : TreeLike() {
    auto& registry = game::getRegistry();
    auto entity = registry.create();
    m_entity = entity;

    game::MovementUtils::builder()
        .setLocalPosition({0.0, 0.0})
        .setSize({32, 48})
        .setScale({1.5, 1.5})
        .setAnchor(game::CLayout::Anchor::MiddleCenter())
        .build(entity);
    game::SceneTreeUtils::attachSceneTreeComponents(entity);

    registry.emplace<game::CRenderComponent>(entity);
    registry.emplace<game::CRenderLayerComponent>(entity, RENDER_LAYER, 0);
    registry.emplace<game::CRenderTargetComponent>(entity, game::CRenderTargetComponent::GameComponent);

    auto animations = loadAnimationResources();
    registry.emplace<game::CAnimatedSpriteRenderComponent>(entity, animations["idle"], true);
    entt::delegate<void(entt::entity, sf::Time)> delegate{};

    delegate.connect<&onUpdate>();
    registry.emplace<game::CScriptsComponent>(entity, delegate);

    registry.emplace<game::CCollisionComponent>(entity);
    registry.emplace<game::CCollisionAABBComponent>(entity, sf::Vector2f {16.f, 24.f});
    // on layer 1, collide with enemy bullet(2)
    registry.emplace<game::CCollisionLayerComponent>(entity,
        CollisionUtils::getCollisionMask(1), CollisionUtils::getCollisionMask(2));

    registry.emplace<game::CLightingComponent>(entity, sf::Color(255, 0, 255, 196), 100.f);

    auto& playerComponent = registry.emplace<game::prefab::GPlayerComponent>(entity, animations);
    playerComponent.attackCoolDown.restart();
    playerComponent.normalAttackCoolDown.restart();

    entt::entity hpText = registry.create();
    makeHpText(hpText);
    playerComponent.hpText = hpText;

    entt::entity mpCoolDownText = registry.create();
    makeMpCoolDownText(mpCoolDownText);
    playerComponent.mpCoolDownText = mpCoolDownText;

    auto smallMapIndicator = registry.create();
    makeSmallMapIndicator(smallMapIndicator);
    SceneTreeUtils::attachChild(entity, smallMapIndicator);
}

std::unordered_map<std::string, entt::resource<game::AnimatedFrames>> game::prefab::Player::loadAnimationResources() {
    static game::Lazy<std::unordered_map<std::string, entt::resource<AnimatedFrames>>> animations {
        [] {
            std::unordered_map<std::string, entt::resource<AnimatedFrames>> res;
            res.emplace("idle", ResourceManager::getAnimatedFramesCache()
                .load(entt::hashed_string {"playerIdleAnimation"},
                    game::AnimatedTextureGenerator()
                        .setOffset(sf::Vector2f{0, 0})
                        .setPlacement(sf::Vector2u{1, 6})
                        .setSize(sf::Vector2f{32, 48})
                        .setDuration(sf::seconds(0.16))
                        .generate("playerIdle", "assets/image/idle.png")).first->second);
            res.emplace("walk", ResourceManager::getAnimatedFramesCache()
                .load(entt::hashed_string {"playerWalkAnimation"},
                    game::AnimatedTextureGenerator()
                        .setOffset(sf::Vector2f{0, 0})
                        .setPlacement(sf::Vector2u{1, 8})
                        .setSize(sf::Vector2f{32, 48})
                        .setDuration(sf::seconds(0.16))
                        .generate("playerWalk", "assets/image/walk.png")).first->second);
            return res;
        }
    };

    return *animations;
}

std::shared_ptr<sf::Image> game::prefab::Player::loadCollisionTexture() {
    static game::Lazy<std::shared_ptr<sf::Image>> collisionTexture {
        [] {
            auto image = std::make_shared<sf::Image>();
            if (!image->loadFromFile("assets/image/collision.png")) {
                game::getLogger().logError("Failed to load collision texture");
            }
            return image;
        }
    };
    return *collisionTexture;
}

bool game::prefab::Player::canMoveTo(sf::Vector2f target) {
    auto collisionTexture = loadCollisionTexture();
    constexpr sf::Vector2f originOffset = { X_LIM, Y_LIM };

    if (target.x < -X_LIM || target.x > X_LIM || target.y < -Y_LIM || target.y > Y_LIM) {
        return false;
    }

    auto pixel = collisionTexture->getPixel({static_cast<uint32_t>(target.x + originOffset.x), static_cast<uint32_t>(target.y + originOffset.y)});
    if (pixel.r != 0) {
        return true;
    }

    return false;
}

void game::prefab::Player::makeHpText(entt::entity text) {
    auto& registry = game::getRegistry();

    game::MovementUtils::builder()
            .setLocalPosition({0.f, 0.f})
            .setSize({100.f, 30.f})
            .setScale({1.0, 1.0})
            .setAnchor(game::CLayout::Anchor::TopLeft())
            .build(text);
    SceneTreeUtils::attachSceneTreeComponents(text);

    registry.emplace<game::CRenderComponent>(text);
    registry.emplace<game::CRenderLayerComponent>(text, TEXT_RENDER_LAYER, 0);
    registry.emplace<game::CRenderTargetComponent>(text, game::CRenderTargetComponent::GameComponent);

    auto font = loadFont();
    auto& textRenderComponent = registry.emplace<game::CTextRenderComponent>(text, font);
    textRenderComponent.setTextSize(HP_FONT_SIZE);
    textRenderComponent.setColor(sf::Color(255, 96, 0));
    textRenderComponent.setText("100");
}

void game::prefab::Player::makeMpCoolDownText(entt::entity text) {
    auto& registry = game::getRegistry();
    auto windowSize = getGame().getWindow().getWindowSize();

    game::MovementUtils::builder()
            .setLocalPosition({0.f, 0.f})
            .setSize({100.f, 30.f})
            .setScale({1.0, 1.0})
            .setAnchor(game::CLayout::Anchor::TopLeft())
            .build(text);
    SceneTreeUtils::attachSceneTreeComponents(text);

    registry.emplace<game::CRenderComponent>(text);
    registry.emplace<game::CRenderLayerComponent>(text, TEXT_RENDER_LAYER, 1);
    registry.emplace<game::CRenderTargetComponent>(text, game::CRenderTargetComponent::GameComponent);

    auto font = loadFont();
    auto& textRenderComponent = registry.emplace<game::CTextRenderComponent>(text, font);
    textRenderComponent.setTextSize(MP_FONT_SIZE);
    textRenderComponent.setColor(sf::Color(0, 196, 196));
    textRenderComponent.setText("100%");
}

entt::resource<sf::Font> game::prefab::Player::loadFont() {
    static Lazy font = Lazy<entt::resource<sf::Font>>(
            [] {
                return ResourceManager::getFontCache()
                        .load(entt::hashed_string { "Tiny5" },
                              "assets/font/tiny5/Tiny5-Regular.ttf").first->second;
            });

    return *font;
}

void game::prefab::Player::makeSmallMapIndicator(entt::entity indicator) {
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
    circleShape->setFillColor(sf::Color(0, 255, 96, 196));
    circleShape->setOutlineColor(sf::Color(255, 255, 255, 196));
    circleShape->setOutlineThickness(SMALL_MAP_INDICATOR_OUTLINE);

    auto uniqueShape = std::unique_ptr<sf::CircleShape>(circleShape);
    registry.emplace<game::CShapeRenderComponent>(indicator, std::move(uniqueShape));
}
