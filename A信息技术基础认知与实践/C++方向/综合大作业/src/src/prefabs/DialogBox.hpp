// Game - NWPU C++ sp25
// Created on 2025/5/23
// by konakona418 (https://github.com/konakona418)

#ifndef DIALOGBOX_HPP
#define DIALOGBOX_HPP

#include "ResourceManager.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/System/Time.hpp"
#include "systems/SceneControl.hpp"

namespace game::prefab {
    struct EOnDialogBoxCompletedEvent {
        entt::entity entity;
    };

    struct GDialogBoxComponent {
        bool isOpen = false;

        entt::entity container { entt::null };
        entt::entity nameText { entt::null };
        entt::entity contentText { entt::null };
        entt::entity portrait { entt::null };

        std::optional<entt::resource<DialogCollection>> dialogCollection {};
        size_t currentDialogLine = 0;

        sf::String line {};

        bool keydown { false };

        GDialogBoxComponent() = default;
    };

    class DialogBox : public TreeLike {
    public:
        static DialogBox create();
        void setVisibility(bool isVisible) const;
        void loadDialog(entt::resource<DialogCollection> dialogCollection);
        void loadDialog(const std::string& resourceName, const DialogCollection& dialogCollection);

        ~DialogBox() = default;
    private:
        static constexpr size_t RENDER_LAYER = 128;
        static constexpr size_t NAME_FONT_SIZE = 24;
        static constexpr size_t CONTENT_FONT_SIZE = 18;
        static constexpr float SINGLE_CHAR_TIME = 0.02f;

        DialogBox();

        static void onUpdate(entt::entity entity, sf::Time deltaTime);
        static void onTweenCallback(entt::entity entity, float value);
        static void onTweenCompletionCallback(entt::entity entity);

        static void nextDialogLine(entt::entity entity);

        static entt::resource<sf::Font> loadFont();
        static entt::resource<DialogCollection> loadDialogCollection();

        static void makeContainer(entt::entity container);
        static void makeNameText(entt::entity text);
        static void makeContentText(entt::entity text);
        static void makePortrait(entt::entity portrait);
    };
} // game

#endif //DIALOGBOX_HPP
