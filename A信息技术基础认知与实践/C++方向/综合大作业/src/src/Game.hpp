// Game - NWPU C++ sp25
// Created on 2025/5/15
// by konakona418 (https://github.com/konakona418)

#ifndef GAME_HPP
#define GAME_HPP

#include <entt/entt.hpp>

#include "ResourceManager.hpp"
#include "SFML/System/String.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Keyboard.hpp"

namespace game {
    class Logger;
    class ThreadPool;
    class Window;

    class Game {
        friend class Window;
    public:
        struct KeyBoard {
            struct Key {
                bool isPressed { false };
                bool isReleased { false };
            };
            KeyBoard() = default;
            void press(sf::Keyboard::Key key);
            void release(sf::Keyboard::Key key);

            bool isKeyPressed(sf::Keyboard::Key key) const;
            bool isKeyReleased(sf::Keyboard::Key key) const;
        private:
            std::unordered_map<sf::Keyboard::Key, Key> m_keys;
        };

        struct Config {
            Config() = default;

            sf::Vector2u windowSize { 1280, 720 };
            sf::String windowTitle { "Game" };
            int fps { 60 };
            bool vsync { true };
        };

        static Game& createGame();

        ~Game();

        void run();

        entt::registry& getRegistry();

        Logger& getLogger();

        ThreadPool& getThreadPool();

        ResourceManager& getResourceManager();

        entt::dispatcher& getEventDispatcher();

        KeyBoard& getKeyboard();

        static Game& getInstance();

        static bool isInitialized();

        Window& getWindow();

        [[nodiscard]] bool isRunning() const;

        [[nodiscard]] Config getConfig() const;

        void setConfig(const Config& config);

        template <typename Fn, std::enable_if_t<std::is_invocable_v<Fn>, int> = 0>
        static void runBlocking(Fn fn) {
            fn();
        }

        template <typename Fn, std::enable_if_t<std::is_invocable_v<Fn>, int> = 0>
        static void runAsync(Fn fn) {
            static_assert(std::is_convertible_v<Fn, std::function<void()>> ||
                std::is_same_v<Fn, std::function<void()>>, "Fn must be convertible to std::function<void()> or std::function<void()>.");
            if constexpr (std::is_same_v<Fn, std::function<void()>>) {
                getInstance().runAsyncImpl(fn);
            }
            getInstance().runAsyncImpl(std::function<void()>(fn));
        }

        void setTimeScale(float timeScale) { m_timeScale = timeScale; }
        [[nodiscard]] float getTimeScale() const { return m_timeScale; }

    private:
        entt::registry m_registry;
        entt::dispatcher m_dispatcher;
        uint32_t m_hardwareConcurrency;
        bool m_isRunning { false };
        Config m_config;
        float m_timeScale { 1.f };

        Game(Game&& other) noexcept = default;
        Game& operator=(Game&& other) noexcept = default;

        Game();

        void init();
        void cleanup();
        void runAsyncImpl(std::function<void()> fn);
    };

    inline bool s_gameInitialized = false;
    inline std::unique_ptr<Game> g_gameInstance { nullptr };
}


#endif //GAME_HPP
