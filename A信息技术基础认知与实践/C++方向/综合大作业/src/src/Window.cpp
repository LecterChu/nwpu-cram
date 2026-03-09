// Game - NWPU C++ sp25
// Created on 2025/5/15
// by konakona418 (https://github.com/konakona418)

#include "Window.hpp"

#include "Common.hpp"
#include "Game.hpp"
#include "Logger.hpp"
#include "ThreadPool.hpp"
#include "systems/CollisionControl.hpp"
#include "systems/MovementControl.hpp"
#include "systems/MusicControl.hpp"
#include "systems/RenderControl.hpp"
#include "systems/SceneControl.hpp"
#include "systems/ScriptsControl.hpp"
#include "systems/TweeningControl.hpp"
#include "systems/LightingControl.hpp"

namespace game {
    void Window::setVideoPreferences(const int fps, const bool vsync) {
        m_videoPreference = { fps, vsync, m_videoPreference.zoomFactor };
        if (m_window != nullptr) {
            m_window->setFramerateLimit(fps);
            m_window->setVerticalSyncEnabled(vsync);
            getLogger().logDebug("Video preferences applied.");
        } else {
            getLogger().logDebug("Window not initialized, video preferences will be applied when window is created.");
        }
        getLogger().logInfo("Video preferences set to: " + std::to_string(fps) + " fps, " + (vsync ? "using" : "not using") + " vsync");
    }

    void Window::setWindowTitle(sf::String title) {
        m_windowTitle = std::move(title);
    }

    void Window::setWindowSize(const sf::Vector2u& windowSize) {
        m_windowSize = windowSize;
    }

    void Window::run() {
        m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_windowSize), m_windowTitle);
        setVideoPreferences(m_videoPreference.fps, m_videoPreference.vsync);

        m_logicalView = m_window->getView();
        m_logicalView.setCenter({0, 0}); // place the view at the center of the window

        auto& game = getGame();
        auto& keyboard = game.getKeyboard();

        // fps display
        constexpr float FPS_LIMIT = 50.f;
        constexpr float FPS_SAMPLE_INTERVAL = 0.5f;
        auto font = ResourceManager::getFontCache()
                .load(entt::hashed_string { "NotoSansSC" },
                      "assets/font/NotoSansSC-Regular.ttf").first->second;
        sf::Text fpsText(font);
        fpsText.setPosition({ 24.f, 24.f });
        fpsText.setCharacterSize(20);
        sf::Clock fpsSampleClock;
        fpsSampleClock.start();

        sf::Clock internalClock;
        internalClock.start();

        sf::Clock crtScanlineClock;
        crtScanlineClock.start();

        sf::RenderTexture gameComponents(m_windowSize);
        sf::RenderTexture ui(m_windowSize);
        sf::RenderTexture illumination(m_windowSize);
        sf::RenderTexture ambientIllumination(m_windowSize);
        sf::RenderTexture primaryOutput(m_windowSize);

        sf::RenderTexture pixelated(m_windowSize);
        sf::RenderTexture uiPixelated(m_windowSize);

        sf::RenderTexture postProcessingCrt(m_windowSize);
        sf::RenderTexture uiPostProcessingCrt(m_windowSize);

        sf::RenderTexture postProcessingBloomBrightness(m_windowSize);
        sf::RenderTexture postProcessingBloomBlurV(m_windowSize);
        sf::RenderTexture postProcessingBloomBlurH(m_windowSize);

        sf::RenderTexture smallMapOutput(m_windowSize);
        sf::RenderTexture finalOutput(m_windowSize);

        entt::resource<sf::Shader> pixelShader = ResourceManager::getShaderCache()
                .load(entt::hashed_string { "pixelShader" }, "assets/shader/common.vert", "assets/shader/pixel.frag").first->second;
        entt::resource<sf::Shader> crtShader = ResourceManager::getShaderCache()
                .load(entt::hashed_string { "crtShader" }, "assets/shader/common.vert", "assets/shader/crt.frag").first->second;
        entt::resource<sf::Shader> bloomShader = ResourceManager::getShaderCache()
                .load(entt::hashed_string { "bloomBrightness" }, "assets/shader/common.vert", "assets/shader/bloom/brightness.frag").first->second;
        entt::resource<sf::Shader> bloomBlurShader = ResourceManager::getShaderCache()
                .load(entt::hashed_string { "bloomBlur" }, "assets/shader/common.vert", "assets/shader/bloom/gaussian.frag").first->second;

        constexpr sf::Color ambientIlluminationColor(255, 255, 255, 160);

        while (m_window->isOpen()) {
            while (auto event = m_window->pollEvent()) {
                if (event.has_value()) {
                    if (event->is<sf::Event::Closed>()) {
                        m_window->close();
                        return;
                    }
                    if (event->is<sf::Event::Resized>()) {
                        keepViewportScale();
                    }
                    if (event->is<sf::Event::KeyPressed>()) {
                        keyboard.press(event->getIf<sf::Event::KeyPressed>()->code);
                    }
                    if (event->is<sf::Event::KeyReleased>()) {
                        keyboard.release(event->getIf<sf::Event::KeyReleased>()->code);
                    }
                }
            }

            auto deltaTime = internalClock.restart();
            const auto timeScale = game.getTimeScale();

            auto originalDeltaTime = deltaTime;
            deltaTime *= timeScale;

            // DO NOT write the logic in event polling loop!!
            SScriptsSystem::update(deltaTime);

            SMovementSystem::update(deltaTime);
            SScenePositionUpdateSystem::update();
            SCollisionSystem::update(deltaTime);
            STweenSystem::update(deltaTime);

            SMusicSystem::update();

            // --- render pipeline --- //

            auto zoomedView = m_logicalView;
            zoomedView.zoom(m_videoPreference.zoomFactor);

            auto smallMapView = sf::View(m_logicalView.getCenter(), sf::Vector2f { 400.f, 400.f });
            smallMapView.zoom(3.0f);

            sf::RectangleShape smallMapShape({ 180.f, 180.f });
            sf::Texture texture;
            if (m_misc.showSmallMap) {
                smallMapOutput.setView(smallMapView);
                smallMapOutput.clear(sf::Color{96, 96, 128, 196});
                SRenderSystem::update(smallMapOutput, game::CRenderTargetComponent::SmallMap, deltaTime);
                smallMapOutput.display();

                texture = smallMapOutput.getTexture();
                smallMapShape.setTexture(&texture);
                smallMapShape.setOutlineColor(sf::Color{32, 32, 96});
                smallMapShape.setOutlineThickness(2.f);
                smallMapShape.setPosition(sf::Vector2f{static_cast<float>(m_windowSize.x) * 0.05f,
                                                       static_cast<float>(m_windowSize.y) * 0.05f});
            }

            // phase: game components
            gameComponents.setView(zoomedView);
            gameComponents.clear(sf::Color::Black);
            SRenderSystem::update(gameComponents, game::CRenderTargetComponent::GameComponent, deltaTime);
            gameComponents.display();
            sf::Sprite gameComponentsSprite(gameComponents.getTexture());

            ui.clear(sf::Color::Transparent);
            SRenderSystem::update(ui, game::CRenderTargetComponent::UI, deltaTime);
            ui.display();

            sf::Sprite uiSprite(ui.getTexture());
            uiSprite.setPosition({0.f, 0.f});

            // phase: illumination with light source
            illumination.setView(zoomedView);
            illumination.clear(sf::Color::Transparent);
            SLightingSystem::update(illumination);
            illumination.display();

            sf::Sprite illuminationSprite(illumination.getTexture());
            //illuminationSprite.setPosition(positioningOffset); // it just works.

            // phase: ambient illumination
            ambientIllumination.setView(zoomedView);
            ambientIllumination.clear(ambientIlluminationColor);
            ambientIllumination.display();

            sf::Sprite ambientIlluminationSprite(ambientIllumination.getTexture());

            // phase: primary output - mix game components, ambient illumination and normal illumination
            primaryOutput.clear(sf::Color::Transparent);
            primaryOutput.draw(gameComponentsSprite);
            primaryOutput.draw(ambientIlluminationSprite, sf::RenderStates(sf::BlendMultiply));
            primaryOutput.draw(illuminationSprite, sf::RenderStates(sf::BlendAdd));
            //primaryOutput.draw(uiSprite);
            primaryOutput.display();
            sf::Sprite primaryOutputSprite(primaryOutput.getTexture());
            primaryOutputSprite.setPosition({0.f, 0.f});

            // phase: pixelation
            pixelated.clear(sf::Color::Transparent);
            pixelShader->setUniform("u_texture", sf::Shader::CurrentTexture);
            pixelShader->setUniform("u_resolution", sf::Vector2f(m_windowSize));
            pixelShader->setUniform("u_pixel_size", sf::Vector2f { 1.5f, 1.5f });
            pixelated.draw(primaryOutputSprite, &*pixelShader);
            pixelated.display();
            sf::Sprite pixelatedSprite(pixelated.getTexture());
            pixelatedSprite.setPosition({0.f, 0.f});

            // phase(ui): pixelation
            uiPixelated.clear(sf::Color::Transparent);
            pixelShader->setUniform("u_pixel_size", sf::Vector2f { 1.0f, 1.0f });
            uiPixelated.draw(uiSprite, &*pixelShader);
            uiPixelated.display();
            sf::Sprite uiPixelatedSprite(uiPixelated.getTexture());
            uiPixelatedSprite.setPosition({0.f, 0.f});

            // phase: post-processing - add crt effects
            postProcessingCrt.clear(sf::Color::Transparent);
            crtShader->setUniform("u_texture", sf::Shader::CurrentTexture);
            crtShader->setUniform("u_time", static_cast<float>(crtScanlineClock.getElapsedTime().asMilliseconds()));
            crtShader->setUniform("u_chromatic_strength", 0.015f);
            postProcessingCrt.draw(pixelatedSprite, &*crtShader);
            postProcessingCrt.display();
            sf::Sprite postProcessingCrtSprite(postProcessingCrt.getTexture());
            postProcessingCrtSprite.setPosition({0.f, 0.f});

            // phase(ui): post-processing - add crt effects
            uiPostProcessingCrt.clear(sf::Color::Transparent);
            crtShader->setUniform("u_chromatic_strength", 0.005f);
            uiPostProcessingCrt.draw(uiPixelatedSprite, &*crtShader);
            if (m_misc.showSmallMap) {
                uiPostProcessingCrt.draw(smallMapShape, &*crtShader);
            }
            uiPostProcessingCrt.display();
            sf::Sprite uiPostProcessingCrtSprite(uiPostProcessingCrt.getTexture());
            uiPostProcessingCrtSprite.setPosition({0.f, 0.f});

            // phase: post-processing - add bloom - brightness calculation
            postProcessingBloomBrightness.clear(sf::Color::Transparent);
            bloomShader->setUniform("u_texture", sf::Shader::CurrentTexture);
            bloomShader->setUniform("u_brightness_threshold", 0.55f);
            postProcessingBloomBrightness.draw(postProcessingCrtSprite, &*bloomShader);
            postProcessingBloomBrightness.display();
            sf::Sprite postProcessingBloomBrightnessSprite(postProcessingBloomBrightness.getTexture());
            postProcessingBloomBrightnessSprite.setPosition({0.f, 0.f});

            // phase: post-processing - add bloom - gaussian blurring
            postProcessingBloomBlurH.clear(sf::Color::Transparent);
            bloomBlurShader->setUniform("u_texture", sf::Shader::CurrentTexture);
            bloomBlurShader->setUniform("u_resolution", sf::Vector2f(m_windowSize));
            bloomBlurShader->setUniform("u_direction", sf::Vector2f(1.f, 0.f));
            postProcessingBloomBlurH.draw(postProcessingBloomBrightnessSprite, &*bloomBlurShader);
            postProcessingBloomBlurH.display();
            sf::Sprite postProcessingBloomBlurHSprite(postProcessingBloomBlurH.getTexture());
            postProcessingBloomBlurHSprite.setPosition({0.f, 0.f});

            postProcessingBloomBlurV.clear(sf::Color::Transparent);
            bloomBlurShader->setUniform("u_texture", sf::Shader::CurrentTexture);
            bloomBlurShader->setUniform("u_resolution", sf::Vector2f(m_windowSize));
            bloomBlurShader->setUniform("u_direction", sf::Vector2f(0.f, 1.f));
            postProcessingBloomBlurV.draw(postProcessingBloomBlurHSprite, &*bloomBlurShader);
            postProcessingBloomBlurV.display();
            sf::Sprite postProcessingBloomBlurVSprite(postProcessingBloomBlurV.getTexture());
            postProcessingBloomBlurVSprite.setPosition({0.f, 0.f});

            // phase: final output - from crt post-processing, add bloom, ui
            finalOutput.clear(sf::Color::Transparent);
            finalOutput.draw(postProcessingCrtSprite);
            finalOutput.draw(postProcessingBloomBlurVSprite, sf::RenderStates(sf::BlendAdd));
            finalOutput.draw(uiPostProcessingCrtSprite);
            finalOutput.display();
            sf::Sprite finalOutputSprite(finalOutput.getTexture());
            finalOutputSprite.setPosition({0.f, 0.f});

            if (fpsSampleClock.getElapsedTime() > sf::seconds(FPS_SAMPLE_INTERVAL)) {
                auto fps = 1.f / originalDeltaTime.asSeconds();
                if (fps < FPS_LIMIT) {
                    fpsText.setFillColor(sf::Color::Red);
                } else {
                    fpsText.setFillColor(sf::Color::Green);
                }
                fpsText.setString(std::to_string(static_cast<int32_t>(std::roundf(fps))));
                fpsSampleClock.restart();
            }

            m_window->clear();

            // phase: render final output
            m_window->draw(finalOutputSprite);

            m_window->draw(fpsText);

            m_window->display();
            // --- end of render pipeline --- //

            SSceneUnmountSystem::update();
        }
    }

    // letterboxing code from:
    // https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view
    sf::View Window::getLetterboxView(sf::View view, sf::Vector2u windowSize) {

        // Compares the aspect ratio of the window to the aspect ratio of the view,
        // and sets the view's viewport accordingly in order to achieve a letterbox effect.
        // A new view (with a new viewport set) is returned.

        float windowRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
        float viewRatio = view.getSize().x / view.getSize().y;
        float sizeX = 1;
        float sizeY = 1;
        float posX = 0;
        float posY = 0;

        bool horizontalSpacing = true;
        if (windowRatio < viewRatio)
            horizontalSpacing = false;

        // If horizontalSpacing is true, the black bars will appear on the left and right side.
        // Otherwise, the black bars will appear on the top and bottom.

        if (horizontalSpacing) {
            sizeX = viewRatio / windowRatio;
            posX = (1 - sizeX) / 2.f;
        } else {
            sizeY = windowRatio / viewRatio;
            posY = (1 - sizeY) / 2.f;
        }

        std::stringstream ss;
        ss << "Letterboxing viewport set, with: ";
        ss << "posX: " << posX << ", posY: " << posY << ", sizeX: " << sizeX << ", sizeY: " << sizeY;
        getLogger().logDebug(ss.str());

        view.setViewport( sf::FloatRect({posX, posY}, {sizeX, sizeY}) );

        return view;
    }

    void Window::keepViewportScale() const {
        auto windowViewOrigin = m_window->getView().getCenter();
        auto view = m_logicalView;
        auto windowSize = m_window->getSize();

        auto letterboxed = getLetterboxView(view, windowSize);
        letterboxed.setCenter(windowViewOrigin);
        m_window->setView(letterboxed);
    }

    void Window::setZoomFactor(float zoomFactor) {
        getLogger().logInfo("Setting zoom factor to: " + std::to_string(zoomFactor));
        m_videoPreference.zoomFactor = zoomFactor;
    }
} // game
