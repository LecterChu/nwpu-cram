// Game - NWPU C++ sp25
// Created on 2025/5/23
// by konakona418 (https://github.com/konakona418)

#include "DialogBox.hpp"

#include <utility>

#include "Game.hpp"
#include "Window.hpp"
#include "components/Render.hpp"
#include "components/Scripts.hpp"
#include "components/Tweening.hpp"
#include "systems/RenderControl.hpp"
#include "utils/DialogGenerator.hpp"
#include "utils/LazyLoader.hpp"
#include "utils/MovementUtils.hpp"

namespace game::prefab {
    DialogBox DialogBox::create() {
        return {};
    }

    void DialogBox::setVisibility(bool isVisible) const {
        auto& registry = game::getRegistry();
        auto& dialogBoxComponent = registry.get<game::prefab::GDialogBoxComponent>(m_entity);
        dialogBoxComponent.isOpen = isVisible;
    }

    void DialogBox::loadDialog(entt::resource<DialogCollection> dialogCollection) {
        auto& registry = game::getRegistry();
        auto& dialogBoxComponent = registry.get<game::prefab::GDialogBoxComponent>(m_entity);
        dialogBoxComponent.dialogCollection = std::move(dialogCollection);
        dialogBoxComponent.currentDialogLine = 0;

        auto speaker = dialogBoxComponent.dialogCollection.value()->getSpeaker(dialogBoxComponent.dialogCollection.value()->lines[0].speakerId);
        auto& nameTextRender = registry.get<game::CTextRenderComponent>(dialogBoxComponent.nameText);
        nameTextRender.setText(speaker.name);
        nameTextRender.setColor(speaker.nameColor);

        auto* portraitShape = registry.get<game::CShapeRenderComponent>(dialogBoxComponent.portrait).getShape();
        auto& portraitPosition = registry.get<game::CLocalTransform>(dialogBoxComponent.portrait);
        if (speaker.portrait.has_value()) {
            RenderUtils::markAsVisible(dialogBoxComponent.portrait);
            portraitShape->setTexture(&speaker.portrait.value()->rawTextureRef->texture);
            portraitShape->setTextureRect(speaker.portrait.value()->textureRect.value());

            auto size = speaker.portrait.value()->textureRect.value().size;

            MovementUtils::setSize(dialogBoxComponent.portrait, { static_cast<float>(size.x), static_cast<float>(size.y) });
            MovementUtils::setScale(dialogBoxComponent.portrait, speaker.portraitScalingFactor);
        } else {
            RenderUtils::markAsInvisible(dialogBoxComponent.portrait);
            portraitShape->setTexture(nullptr);
        }

        auto& tween = registry.get<CTweenComponent>(m_entity);
        auto textLength = dialogBoxComponent.dialogCollection.value()->lines[0].text.getSize();
        tween.setDuration(sf::seconds(SINGLE_CHAR_TIME * static_cast<float>(textLength)));
        tween.setEndValue(static_cast<float>(dialogBoxComponent.dialogCollection.value()->lines[0].text.getSize()));
        tween.restart();
    }

    void DialogBox::loadDialog(const std::string& resourceName, const DialogCollection& dialogCollection) {
        auto dialogResourceResult = ResourceManager::getDialogCache().load(entt::hashed_string { resourceName.c_str() }, dialogCollection);
        auto dialogResource = dialogResourceResult.first->second;
        if (!dialogResourceResult.second) {
            getLogger().logError("Attempted to load a resource with the same name as an existing resource. Is this a desired behavior?");
        }
        loadDialog(dialogResource);
    }

    DialogBox::DialogBox() {
        auto& registry = game::getRegistry();
        auto container = registry.create();
        auto nameText = registry.create();
        auto contentText = registry.create();
        auto portrait = registry.create();

        m_entity = container;

        makeContainer(container);
        makeNameText(nameText);
        makeContentText(contentText);
        makePortrait(portrait);

        SceneTreeUtils::attachChild(container, nameText);
        SceneTreeUtils::attachChild(container, contentText);
        SceneTreeUtils::attachChild(container, portrait);

        auto& dialogBoxComponent = registry.emplace<game::prefab::GDialogBoxComponent>(container);
        dialogBoxComponent.container = container;
        dialogBoxComponent.contentText = contentText;
        dialogBoxComponent.nameText = nameText;
        dialogBoxComponent.portrait = portrait;

        auto& tween = registry.emplace<CTweenComponent>(container);
        tween.setBeginValue(0.f);
        // tween.setEndValue(static_cast<float>(dialogBoxComponent.dialogCollection->lines[0].text.getSize()));
        // tween.setDuration(sf::seconds(0.5f));
        tween.setCallback(DialogBox::onTweenCallback);
        tween.setCompletionCallback(DialogBox::onTweenCompletionCallback);

        //loadDialog(loadDialogCollection());
    }

    void DialogBox::onUpdate(entt::entity entity, sf::Time deltaTime) {
        auto& registry = game::getRegistry();
        auto& keyboard = getGame().getKeyboard();

        auto& dialogBoxComponent = registry.get<game::prefab::GDialogBoxComponent>(entity);
        if (!dialogBoxComponent.isOpen) {
            if (RenderUtils::isVisible(entity)) {
                RenderUtils::markAsInvisible(entity);
            }
            return;
        }
        RenderUtils::markAsVisibleNotRecurse(entity);
        RenderUtils::markAsVisibleNotRecurse(dialogBoxComponent.nameText);
        RenderUtils::markAsVisibleNotRecurse(dialogBoxComponent.contentText);

        if (keyboard.isKeyPressed(sf::Keyboard::Key::Space) && dialogBoxComponent.isOpen) {
            dialogBoxComponent.keydown = true;
        }
        if (keyboard.isKeyReleased(sf::Keyboard::Key::Space) && dialogBoxComponent.keydown && dialogBoxComponent.isOpen) {
            nextDialogLine(entity);
            dialogBoxComponent.keydown = false;
        }
        if (keyboard.isKeyPressed(sf::Keyboard::Key::LControl)) {
            nextDialogLine(entity);
        }

        if (!dialogBoxComponent.dialogCollection.has_value()) {
            return;
        }

        auto& contentText = registry.get<game::CTextRenderComponent>(dialogBoxComponent.contentText);
        contentText.setText(dialogBoxComponent.line);
    }

    void DialogBox::onTweenCallback(entt::entity entity, float value) {
        auto& registry = game::getRegistry();
        auto& dialogBoxComponent = registry.get<game::prefab::GDialogBoxComponent>(entity);

        if (dialogBoxComponent.currentDialogLine >= dialogBoxComponent.dialogCollection.value()->lines.size()) {
            return;
        }

        dialogBoxComponent.line =
            dialogBoxComponent.dialogCollection.value()->lines[dialogBoxComponent.currentDialogLine]
            .text.substring(0, std::ceil(value));
    }

    void DialogBox::onTweenCompletionCallback(entt::entity entity) {
        auto& registry = game::getRegistry();
        auto& dialogBoxComponent = registry.get<game::prefab::GDialogBoxComponent>(entity);

        if (dialogBoxComponent.currentDialogLine >= dialogBoxComponent.dialogCollection.value()->lines.size()) {
            return;
        }

        dialogBoxComponent.line =
                dialogBoxComponent.dialogCollection.value()->lines[dialogBoxComponent.currentDialogLine].text;
    }

    void DialogBox::nextDialogLine(entt::entity entity) {
        auto& registry = game::getRegistry();
        auto& dialogBoxComponent = registry.get<game::prefab::GDialogBoxComponent>(entity);

        if (!dialogBoxComponent.dialogCollection.has_value()) {
            return;
        }

        auto& tweenComponent = registry.get<game::CTweenComponent>(entity);

        // look out for minus-one errors
        if (dialogBoxComponent.dialogCollection.value()->lines.size() <= dialogBoxComponent.currentDialogLine + 1) {
            dialogBoxComponent.isOpen = false;
            getLogger().logInfo("DialogBox finished: nextDialogLine");
            getEventDispatcher().trigger<game::prefab::EOnDialogBoxCompletedEvent>({ entity });
            return;
        }

        getLogger().logDebug("Dialog line completed, offset: " + std::to_string(dialogBoxComponent.currentDialogLine));

        dialogBoxComponent.currentDialogLine++;

        auto textLength = dialogBoxComponent.dialogCollection.value()->lines[dialogBoxComponent.currentDialogLine].text.getSize();
        tweenComponent.setEndValue(static_cast<float>(textLength));
        tweenComponent.setDuration(sf::seconds(SINGLE_CHAR_TIME * static_cast<float>(textLength)));
        tweenComponent.restart();

        auto speaker = dialogBoxComponent.dialogCollection.value()->getSpeaker(dialogBoxComponent.dialogCollection.value()->lines[dialogBoxComponent.currentDialogLine].speakerId);
        auto& nameText = registry.get<game::CTextRenderComponent>(dialogBoxComponent.nameText);
        nameText.setText(speaker.name);
        nameText.setColor(speaker.nameColor);

        auto* portraitShape = registry.get<game::CShapeRenderComponent>(dialogBoxComponent.portrait).getShape();
        auto& portraitPosition = registry.get<game::CLocalTransform>(dialogBoxComponent.portrait);
        if (speaker.portrait.has_value()) {
            RenderUtils::markAsVisible(dialogBoxComponent.portrait);
            portraitShape->setTexture(&speaker.portrait.value()->rawTextureRef->texture);
            portraitShape->setTextureRect(speaker.portrait.value()->textureRect.value());

            auto size = speaker.portrait.value()->textureRect.value().size;

            MovementUtils::setSize(dialogBoxComponent.portrait, { static_cast<float>(size.x), static_cast<float>(size.y) });
            MovementUtils::setScale(dialogBoxComponent.portrait, speaker.portraitScalingFactor);
        } else {
            RenderUtils::markAsInvisible(dialogBoxComponent.portrait);
            portraitShape->setTexture(nullptr);
        }
    }

    entt::resource<sf::Font> DialogBox::loadFont() {
        static Lazy font = Lazy<entt::resource<sf::Font>>(
            [] {
                return ResourceManager::getFontCache()
                    .load(entt::hashed_string { "NotoSansSC" },
                        "assets/font/NotoSansSC-Regular.ttf").first->second;
        });

        return *font;
    }

    entt::resource<DialogCollection> DialogBox::loadDialogCollection() {
        static Lazy dialog = Lazy<entt::resource<DialogCollection>>(
            [] {
                auto dialogs = DialogGenerator()
                    .addSpeaker("John Doe", sf::Color::Red)
                    .addSpeaker("Jane Doe", sf::Color::Blue)
                    .addLine(0, "Hello, World!")
                    .addLine(1, "Hello, World. How are you?")
                    .addLine(0, "How are you?")
                    .addLine(1, "How are you? I'm fine.")
                    .addLine(0, "I'm fine too.")
                    .generate();
                return ResourceManager::getDialogCache()
                    .load(entt::hashed_string { "dialog" }, dialogs).first->second;
        });
        return *dialog;
    }

    void DialogBox::makeContainer(entt::entity container) {
        auto& registry = game::getRegistry();
        auto windowSize = getGame().getWindow().getWindowSize();

        game::InvokeUpdateDelegate delegate;
        delegate.connect<&DialogBox::onUpdate>();
        registry.emplace<game::CScriptsComponent>(container, delegate);

        game::MovementUtils::builder()
            .setLocalPosition({0.f, static_cast<float>(windowSize.y) * 0.7f})
            .setSize({static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) * 0.3f})
            .setScale({1.0, 1.0})
            .setAnchor(game::CLayout::Anchor::TopLeft())
            .build(container);
        SceneTreeUtils::attachSceneTreeComponents(container);
        registry.emplace<game::CRenderTargetComponent>(container, game::CRenderTargetComponent::UI);

        //registry.emplace<game::CRenderComponent>(container);
        registry.emplace<game::CRenderLayerComponent>(container, RENDER_LAYER, 1);

        auto rectShape = new sf::RectangleShape();
        rectShape->setFillColor(sf::Color(255, 255, 255, 240));

        auto uniqueShape = std::unique_ptr<sf::Shape>(rectShape);
        registry.emplace<game::CShapeRenderComponent>(container, std::move(uniqueShape));
    }

    void DialogBox::makeNameText(entt::entity text) {
        auto& registry = game::getRegistry();
        auto windowSize = getGame().getWindow().getWindowSize();

        game::MovementUtils::builder()
            .setLocalPosition({50.f, 30.f})
            .setSize({static_cast<float>(windowSize.x) - 100.f, 50.f})
            .setScale({1.0, 1.0})
            .setAnchor(game::CLayout::Anchor::TopLeft())
            .build(text);
        SceneTreeUtils::attachSceneTreeComponents(text);

        //registry.emplace<game::CRenderComponent>(text);
        registry.emplace<game::CRenderLayerComponent>(text, RENDER_LAYER, 2);
        registry.emplace<game::CRenderTargetComponent>(text, game::CRenderTargetComponent::UI);

        auto font = loadFont();
        auto& textRenderComponent = registry.emplace<game::CTextRenderComponent>(text, font);
        textRenderComponent.setTextSize(NAME_FONT_SIZE);
        textRenderComponent.setStyle(sf::Text::Style::Bold);
        textRenderComponent.setText("PLACEHOLDER");
    }

    void DialogBox::makeContentText(entt::entity text) {
        auto& registry = game::getRegistry();
        auto windowSize = getGame().getWindow().getWindowSize();

        game::MovementUtils::builder()
            .setLocalPosition({50.f, 75.f})
            .setSize({static_cast<float>(windowSize.x) * 0.85f, static_cast<float>(windowSize.y) * 0.3f - 100.f})
            .setScale({1.0, 1.0})
            .setAnchor(game::CLayout::Anchor::TopLeft())
            .build(text);
        SceneTreeUtils::attachSceneTreeComponents(text);

        //registry.emplace<game::CRenderComponent>(text);
        registry.emplace<game::CRenderLayerComponent>(text, RENDER_LAYER, 2);
        registry.emplace<game::CRenderTargetComponent>(text, game::CRenderTargetComponent::UI);

        auto font = loadFont();
        auto& textRenderComponent = registry.emplace<game::CTextRenderComponent>(text, font);

        textRenderComponent.setTextSize(CONTENT_FONT_SIZE);
        textRenderComponent.setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
        textRenderComponent.setColor(sf::Color::Black);
    }

    void DialogBox::makePortrait(entt::entity portrait) {
        auto& registry = game::getRegistry();
        auto windowSize = getGame().getWindow().getWindowSize();

        game::MovementUtils::builder()
                .setLocalPosition({static_cast<float>(windowSize.x) * 0.95f, static_cast<float>(windowSize.y) * 0.3f})
                .setSize({static_cast<float>(windowSize.x) * 0.3f, static_cast<float>(windowSize.y) * 0.8f})
                .setScale({1.0, 1.0})
                .setAnchor(game::CLayout::Anchor::BottomRight())
                .build(portrait);
        SceneTreeUtils::attachSceneTreeComponents(portrait);
        registry.emplace<game::CRenderTargetComponent>(portrait, game::CRenderTargetComponent::UI);

        //registry.emplace<game::CRenderComponent>(container);
        registry.emplace<game::CRenderLayerComponent>(portrait, RENDER_LAYER, 0);

        auto rectShape = new sf::RectangleShape();

        auto uniqueShape = std::unique_ptr<sf::Shape>(rectShape);
        rectShape->setTexture(nullptr);
        registry.emplace<game::CShapeRenderComponent>(portrait, std::move(uniqueShape));
    }
} // game