// Game - NWPU C++ sp25
// Created on 2025/5/15
// by konakona418 (https://github.com/konakona418)

#include "Common.hpp"

#include <random>

#include "Game.hpp"

namespace game {
    Game& getGame() {
        return Game::getInstance();
    }

    Logger& getLogger() {
        return getGame().getLogger();
    }

    ThreadPool& getThreadPool() {
        return getGame().getThreadPool();
    }

    entt::registry& getRegistry() {
        return getGame().getRegistry();
    }

    ResourceManager& getResourceManager() {
        return getGame().getResourceManager();
    }

    entt::dispatcher& getEventDispatcher() {
        return getGame().getEventDispatcher();
    }

    float random(float min, float max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution dis(min, max);
        return dis(gen);
    }

    sf::Vector2f random(sf::Vector2f min, sf::Vector2f max) {
        return {random(min.x, max.x), random(min.y, max.y)};
    }

    sf::Vector2f random(sf::Vector2f max) {
        return random(sf::Vector2f(0, 0), max);
    }

    bool randomBool() {
        return randomBool(0.5f);
    }

    bool randomBool(float chance) {
        return random(0, 1) > chance;
    }

    float lerp(float from, float dest, float damping) {
        return from + (dest - from) * damping;
    }

    sf::Vector2f lerp(sf::Vector2f from, sf::Vector2f dest, float damping) {
        return from + (dest - from) * damping;
    }

    float lerp(float from, float dest, float damping, sf::Time deltaTime) {
        return lerp(from, dest, 1.f - std::powf(damping, deltaTime.asSeconds()));
    }

    sf::Vector2f lerp(sf::Vector2f from, sf::Vector2f dest, float damping, sf::Time deltaTime) {
        return lerp(from, dest, 1.f - std::powf(damping, deltaTime.asSeconds()));
    }
}
