// Game - NWPU C++ sp25
// Created on 2025/5/15
// by konakona418 (https://github.com/konakona418)

#include "Game.hpp"

#include "Common.hpp"
#include "Logger.hpp"
#include "ThreadPool.hpp"
#include "Window.hpp"

game::Game::Game() {
    m_hardwareConcurrency = std::thread::hardware_concurrency();
}

void game::Game::init() {
    auto& ctx = m_registry.ctx();

    // my advice is, do not write log in the destructor of components,
    // as it can be pretty random - at least unknown - when logger will be destroyed.
    ctx.emplace<Logger>(true);
    auto& logger = m_registry.ctx().get<Logger>();
    logger.run();
    logger.logInfo("Logger up and running!");

    logger.logInfo("Initializing game");

    logger.logDebug("Current hardware concurrency: " + std::to_string(m_hardwareConcurrency));

    // one reserved for the render thread,
    // which is basically the main thread. another for the main thread.
    ctx.emplace<ThreadPool>(m_hardwareConcurrency - 2);
    auto& threadPool = m_registry.ctx().get<ThreadPool>();
    threadPool.run();

    logger.logInfo("Initializing resource manager");
    ctx.emplace<ResourceManager>();

    logger.logInfo("Initializing window");
    ctx.emplace<Window>();
    auto& window = m_registry.ctx().get<Window>();

    logger.logInfo("Initializing keyboard utilities");
    ctx.emplace<KeyBoard>();
}

void game::Game::cleanup() {
    auto& ctx = m_registry.ctx();

    ctx.erase<KeyBoard>();
    ctx.erase<Window>();
    ctx.erase<ResourceManager>();
    ctx.erase<ThreadPool>();

    getLogger().logInfo("Closing logger");
    ctx.erase<Logger>();
}

void game::Game::runAsyncImpl(std::function<void()> fn) {
    getThreadPool().schedule(std::move(fn));
}

void game::Game::KeyBoard::press(sf::Keyboard::Key key) {
    if (m_keys.find(key) == m_keys.end()) {
        m_keys.emplace(key, Key { false, false});
    }
    m_keys[key].isPressed = true;
    m_keys[key].isReleased = false;
}

void game::Game::KeyBoard::release(sf::Keyboard::Key key) {
    if (m_keys.find(key) == m_keys.end()) {
        m_keys.emplace(key, Key { false, false});
    }
    m_keys[key].isPressed = false;
    m_keys[key].isReleased = true;
}

bool game::Game::KeyBoard::isKeyPressed(const sf::Keyboard::Key key) const {
    return m_keys.find(key) != m_keys.end() && m_keys.at(key).isPressed;
}

bool game::Game::KeyBoard::isKeyReleased(const sf::Keyboard::Key key) const {
    return m_keys.find(key) != m_keys.end() && m_keys.at(key).isReleased;
}

game::Game& game::Game::createGame() {
    if (!s_gameInitialized) {
        s_gameInitialized = true;
        g_gameInstance = std::unique_ptr<Game>(new Game);
        g_gameInstance->init();
    }
    return *g_gameInstance;
}

game::Game& game::Game::getInstance() { return *g_gameInstance; }

bool game::Game::isInitialized() { return s_gameInitialized; }

game::Window& game::Game::getWindow() {
    return m_registry.ctx().get<Window>();
}

bool game::Game::isRunning() const { return m_isRunning; }

game::Game::Config game::Game::getConfig() const { return m_config; }

void game::Game::setConfig(const Config& config) { m_config = config;}

game::Game::~Game() {
    getLogger().logInfo("Closing game");
    cleanup();
}

void game::Game::run() {
    getLogger().logInfo("Starting game");
    runBlocking([this]() -> void {
        auto& window = getWindow();

        window.setWindowSize(m_config.windowSize);
        window.setWindowTitle(m_config.windowTitle);
        window.setVideoPreferences(m_config.fps, m_config.vsync);

        window.run();
    });
}

entt::registry& game::Game::getRegistry() {
    return m_registry;
}

game::Logger& game::Game::getLogger() {
    return m_registry.ctx().get<Logger>();
}

game::ThreadPool& game::Game::getThreadPool() {
    return m_registry.ctx().get<ThreadPool>();
}

game::ResourceManager& game::Game::getResourceManager() {
    return m_registry.ctx().get<ResourceManager>();
}

entt::dispatcher& game::Game::getEventDispatcher() {
    return m_dispatcher;
}

game::Game::KeyBoard& game::Game::getKeyboard() {
    return m_registry.ctx().get<KeyBoard>();
}
