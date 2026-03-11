// Game - NWPU C++ sp25
// Created on 2025/5/28
// by konakona418 (https://github.com/konakona418)

#include "SplashScreen.hpp"
#include "utils/LazyLoader.hpp"
#include "ResourceManager.hpp"
#include "utils/TextureGenerator.hpp"
#include "utils/MovementUtils.hpp"
#include "components/Tweening.hpp"

namespace game::prefab {
    SplashScreen::SplashScreen() : game::TreeLike() {
        auto& registry = game::getRegistry();
        auto entity = registry.create();
        m_entity = entity;

        game::MovementUtils::builder()
                .setLocalPosition({0.f, 0.f})
                .setSize({1280.f, 720.f})
                .setScale({1.0, 1.0})
                .setAnchor(game::CLayout::Anchor::TopLeft())
                .build(entity);
        game::SceneTreeUtils::attachSceneTreeComponents(entity);

        registry.emplace<game::CRenderComponent>(entity);
        registry.emplace<game::CRenderLayerComponent>(entity, 0, 0);
        registry.emplace<game::CRenderTargetComponent>(entity, game::CRenderTargetComponent::UI);

        auto frame = loadImage();
        registry.emplace<game::CSpriteRenderComponent>(entity, frame);

        registry.emplace<GSplashScreenComponent>(entity);

        auto& tweenComponent = registry.emplace<game::CTweenComponent>(entity);
        tweenComponent.setCallback(&SplashScreen::onTweenUpdate);
        tweenComponent.setCompletionCallback(&SplashScreen::onTweenCompleted);
        tweenComponent.setBeginValue(0.f);
        tweenComponent.setEndValue(1.f);
        tweenComponent.setDuration(sf::seconds(SPLASH_SCREEN_PHASE_DURATION));
        tweenComponent.restart();
    }

    entt::resource<game::SpriteFrame> SplashScreen::loadImage() {
        static Lazy image = Lazy<entt::resource<game::SpriteFrame>> {
            [] {
                return ResourceManager::getSpriteFrameCache()
                    .load(entt::hashed_string { "splashScreenSprite" },
                          StaticTextureGenerator()
                            .setOffset({0, 0})
                            .setSize({32, 32})
                            .generate("splashScreen",
                                      "assets/image/splash-screen.png"))
                                      .first->second;
            }
        };
        return *image;
    }

    void SplashScreen::onTweenCompleted(entt::entity entity) {
        auto& registry = game::getRegistry();
        auto& splashScreenComponent = registry.get<GSplashScreenComponent>(entity);
        auto& tweenComponent = registry.get<game::CTweenComponent>(entity);

        if (splashScreenComponent.splashScreenState == GSplashScreenComponent::SplashScreenState::SPLASH_SCREEN_FADE_IN) {
            splashScreenComponent.splashScreenState = GSplashScreenComponent::SplashScreenState::SPLASH_SCREEN_WAIT;
            tweenComponent.setBeginValue(1.f);
            tweenComponent.setEndValue(1.f);
            tweenComponent.setDuration(sf::seconds(SPLASH_SCREEN_PHASE_DURATION));
            tweenComponent.restart();

            return;
        }
        if (splashScreenComponent.splashScreenState == GSplashScreenComponent::SplashScreenState::SPLASH_SCREEN_WAIT) {
            splashScreenComponent.splashScreenState = GSplashScreenComponent::SplashScreenState::SPLASH_SCREEN_FADE_OUT;
            tweenComponent.setBeginValue(1.f);
            tweenComponent.setEndValue(0.f);
            tweenComponent.setDuration(sf::seconds(SPLASH_SCREEN_PHASE_DURATION * 2.0f));
            tweenComponent.restart();

            return;
        }
        if (splashScreenComponent.splashScreenState == GSplashScreenComponent::SplashScreenState::SPLASH_SCREEN_FADE_OUT) {
            splashScreenComponent.splashScreenState = GSplashScreenComponent::SplashScreenState::SPLASH_SCREEN_IDLE;
            game::getEventDispatcher().trigger<EOnSplashScreenCompletedEvent>(EOnSplashScreenCompletedEvent { entity });
        }
    }

    void SplashScreen::onTweenUpdate(entt::entity entity, float progress) {
        auto& registry = game::getRegistry();
        auto& splashScreenComponent = registry.get<GSplashScreenComponent>(entity);
        auto& tweenComponent = registry.get<game::CTweenComponent>(entity);
        auto& spriteRenderComponent = registry.get<game::CSpriteRenderComponent>(entity);

        auto sprite = spriteRenderComponent.getSprite();
        if (!sprite.has_value()) {
            return;
        }
        sprite.value()->setColor(sf::Color(255, 255, 255, static_cast<uint8_t>(progress * 255)));
    }
} // game