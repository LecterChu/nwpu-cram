// Game - NWPU C++ sp25
// Created on 2025/5/27
// by konakona418 (https://github.com/konakona418)

#include "Banner.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include "utils/LazyLoader.hpp"
#include "ResourceManager.hpp"
#include "systems/RenderControl.hpp"
#include "components/Scripts.hpp"
#include "utils/MovementUtils.hpp"
#include "components/Tweening.hpp"

namespace game::prefab {
    Banner Banner::create() {
        return {};
    }

    Banner::Banner() {
        auto& registry = game::getRegistry();
        entt::entity container = registry.create();
        m_entity = container;
        entt::entity text = registry.create();

        makeContainer(container);
        makeText(text);

        auto& bannerComponent = registry.emplace<GBannerComponent>(container);
        bannerComponent.bannerText = text;

        SceneTreeUtils::attachChild(container, text);
    }

    entt::resource<sf::Font> Banner::loadBannerFont() {
        static Lazy font = Lazy<entt::resource<sf::Font>> {
            [] {
                auto font = ResourceManager::getFontCache()
                        .load(entt::hashed_string { "Jersey20"}, "assets/font/jersey20/Jersey20-Regular.ttf")
                        .first->second;
                font->setSmooth(false);
                return font;
            }
        };
        return *font;
    }

    void Banner::makeContainer(entt::entity container) {
        auto& registry = game::getRegistry();
        auto windowSize = getGame().getWindow().getWindowSize();

        game::InvokeUpdateDelegate delegate;
        delegate.connect<&Banner::onUpdate>();
        registry.emplace<game::CScriptsComponent>(container, delegate);

        game::MovementUtils::builder()
                .setLocalPosition({static_cast<float>(windowSize.x) * 0.5f, static_cast<float>(windowSize.y) * 0.5f})
                .setSize({static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) * 0.0f})
                .setScale({1.0, 1.0})
                .setAnchor(game::CLayout::Anchor::MiddleCenter())
                .build(container);
        SceneTreeUtils::attachSceneTreeComponents(container);

        auto& tweenComponent = registry.emplace<game::CTweenComponent>(container);
        tweenComponent.setCallback(&Banner::onTweenUpdate);
        tweenComponent.setCompletionCallback(&Banner::onTweenComplete);
        tweenComponent.setEasingFunction(CTweenComponent::EasingFunction::exponential);

        //registry.emplace<game::CRenderComponent>(container);
        registry.emplace<game::CRenderLayerComponent>(container, RENDER_LAYER, 1);
        registry.emplace<game::CRenderTargetComponent>(container, game::CRenderTargetComponent::UI);

        auto rectShape = new sf::RectangleShape();
        rectShape->setFillColor(sf::Color(255, 96, 96, 230));

        auto uniqueShape = std::unique_ptr<sf::Shape>(rectShape);
        registry.emplace<game::CShapeRenderComponent>(container, std::move(uniqueShape));
    }

    void Banner::makeText(entt::entity text) {
        auto& registry = game::getRegistry();
        auto windowSize = getGame().getWindow().getWindowSize();

        auto yOffset = (static_cast<float>(windowSize.y) * 0.4f - TEXT_FONT_SIZE) * 0.5f;
        game::MovementUtils::builder()
                .setLocalPosition({0.f, yOffset})
                .setSize({static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) * 0.4f})
                .setScale({1.0, 1.0})
                .setAnchor(game::CLayout::Anchor::MiddleCenter())
                .build(text);
        SceneTreeUtils::attachSceneTreeComponents(text);

        //registry.emplace<game::CRenderComponent>(text);
        registry.emplace<game::CRenderLayerComponent>(text, RENDER_LAYER, 2);
        registry.emplace<game::CRenderTargetComponent>(text, game::CRenderTargetComponent::UI);

        auto font = loadBannerFont();
        auto& textRenderComponent = registry.emplace<game::CTextRenderComponent>(text, font);

        textRenderComponent.setTextSize(TEXT_FONT_SIZE);
        textRenderComponent.setText("PLACEHOLDER");
        textRenderComponent.setColor(TEXT_COLOR);
    }

    void Banner::onUpdate(entt::entity entity, sf::Time deltaTime) {
        auto& registry = game::getRegistry();
        auto& bannerComponent = registry.get<GBannerComponent>(entity);

        if (bannerComponent.bannerState == GBannerComponent::BannerState::BANNER_IDLE) {
            return;
        }

        if (bannerComponent.bannerState == GBannerComponent::BannerState::BANNER_READY) {
            bannerComponent.bannerState = GBannerComponent::BannerState::BANNER_FADE_IN;

            auto& tweenComponent = registry.get<game::CTweenComponent>(entity);
            tweenComponent.setRange(0.0f, 0.4f);
            tweenComponent.setDuration(sf::seconds(0.2f));
            tweenComponent.restart();
        }
    }

    void Banner::onTweenUpdate(entt::entity entity, float value) {
        auto windowSize = getGame().getWindow().getWindowSize();
        sf::Vector2f size = { static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) * value };
        MovementUtils::setSize(entity, size);

        auto& registry = game::getRegistry();
        auto& tweenComponent = registry.get<game::CTweenComponent>(entity);
        auto& bannerComponent = registry.get<GBannerComponent>(entity);
        auto& textRenderComponent = registry.get<game::CTextRenderComponent>(bannerComponent.bannerText);

        sf::Color color = TEXT_COLOR;
        // I found that using tweening like below will have some weird but cool effects.
        // this is because, in the DISPLAY stage, the ratio will be reset to 0,
        // and the color will be transparent:
        // 0~1 -> 0~1 -> 0~1.
        color.a = static_cast<uint8_t>(255.0f * tweenComponent.getRatioValue());
        textRenderComponent.setColor(color);
    }

    void Banner::onTweenComplete(entt::entity entity) {
        auto& registry = game::getRegistry();
        auto& bannerComponent = registry.get<GBannerComponent>(entity);
        auto& tweenComponent = registry.get<game::CTweenComponent>(entity);

        if (bannerComponent.bannerState == GBannerComponent::BannerState::BANNER_FADE_IN) {
            bannerComponent.bannerState = GBannerComponent::BannerState::BANNER_DISPLAY;
            tweenComponent.setRange(0.4f, 0.4f);
            tweenComponent.setDuration(sf::seconds(1.2f));
            tweenComponent.restart();
            return;
        }
        if (bannerComponent.bannerState == GBannerComponent::BannerState::BANNER_DISPLAY) {
            bannerComponent.bannerState = GBannerComponent::BannerState::BANNER_FADE_OUT;
            tweenComponent.setRange(0.4f, 0.0f);
            tweenComponent.setDuration(sf::seconds(0.2f));
            tweenComponent.restart();
            return;
        }
        if (bannerComponent.bannerState == GBannerComponent::BannerState::BANNER_FADE_OUT) {
            bannerComponent.bannerState = GBannerComponent::BannerState::BANNER_IDLE;
            game::getEventDispatcher().trigger<EOnBannerCompleteEvent>(EOnBannerCompleteEvent { entity });
            game::RenderUtils::markAsInvisible(entity);
        }
    }

    void Banner::launch() {
        auto& registry = game::getRegistry();
        auto& bannerComponent = registry.get<GBannerComponent>(m_entity);
        auto& textRenderComponent = registry.get<game::CTextRenderComponent>(bannerComponent.bannerText);
        auto& textLocalTransform = registry.get<game::CLocalTransform>(bannerComponent.bannerText);

        bannerComponent.bannerState = GBannerComponent::BannerState::BANNER_READY;
        textRenderComponent.setText(bannerComponent.textString);

        auto textWidth = getTextWidth(textRenderComponent.getText());
        auto size = textLocalTransform.getSize();
        size.x = textWidth;
        textLocalTransform.setSize(size);

        game::RenderUtils::markAsVisible(m_entity);
    }

    float Banner::getTextWidth(const sf::String& text) {
        sf::Text textObject(loadBannerFont());
        textObject.setString(text);
        textObject.setCharacterSize(TEXT_FONT_SIZE);
        return textObject.getLocalBounds().size.x + TEXT_FONT_SIZE; // it just works
    }

    void Banner::setText(const sf::String &text) {
        auto& registry = game::getRegistry();
        auto& bannerComponent = registry.get<GBannerComponent>(m_entity);
        bannerComponent.textString = text;
    }
} // game