// Game - NWPU C++ sp25
// Created on 2025/5/15
// by konakona418 (https://github.com/konakona418)

#ifndef WINDOW_H
#define WINDOW_H

#include <utility>

#include "SFML/Graphics.hpp"

namespace game {
    class Window {
    public:
        Window() : m_windowSize(1280.f, 720.f), m_aspectRatio(1280.f / 720.f) {};

        explicit Window(const sf::Vector2u& windowSize)
            : m_windowSize(windowSize),
            m_aspectRatio(static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y)) {}

        Window(const sf::Vector2u& windowSize, sf::String title)
            : m_windowSize(windowSize),
            m_aspectRatio(static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y)), m_windowTitle(std::move(title)) {}

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        ~Window() = default;

        void setVideoPreferences(int fps, bool vsync);

        void setZoomFactor(float zoomFactor);

        void setWindowTitle(sf::String title);

        void setWindowSize(const sf::Vector2u& windowSize);

        [[nodiscard]] sf::Vector2u getWindowSize() const { return m_windowSize; }

        void run();

        void setViewCenter(sf::Vector2f center) {
            /*auto view = m_window->getView();
            view.setCenter(center);
            m_window->setView(view);*/
            m_logicalView.setCenter(center);
        }

        sf::Vector2f getViewCenter() const {
            return m_logicalView.getCenter();
        }

        sf::RenderWindow* getRawWindow() { return m_window.get(); }

        void setSmallMapVisibility(bool isVisible) { m_misc.showSmallMap = isVisible; }
        bool isSmallMapVisible() const { return m_misc.showSmallMap; }

    private:
        struct VideoPreference {
            int fps = 60;
            bool vsync = false;
            float zoomFactor = 1.f;
        };

        struct Misc {
            bool showSmallMap { false };
        };

        std::unique_ptr<sf::RenderWindow> m_window { nullptr };
        sf::Vector2u m_windowSize;
        sf::String m_windowTitle = u8"Game";
        float m_aspectRatio { 0 };
        VideoPreference m_videoPreference;
        Misc m_misc;
        sf::View m_logicalView;

        void keepViewportScale() const;
        static sf::View getLetterboxView(sf::View view, sf::Vector2u windowSize);
    };
} // game

#endif //WINDOW_H
