// Game - NWPU C++ sp25
// Created on 2025/5/15
// by konakona418 (https://github.com/konakona418)

#ifndef COMMON_HPP
#define COMMON_HPP
#include <optional>
#include <entt/entity/registry.hpp>

#include "SFML/System/String.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Time.hpp"

namespace game {
    class Game;
    class Logger;
    class ThreadPool;
    struct ResourceManager;

    Game& getGame();
    Logger& getLogger();
    ThreadPool& getThreadPool();

    entt::registry& getRegistry();
    ResourceManager& getResourceManager();

    entt::dispatcher& getEventDispatcher();

    sf::String cropString(const sf::String& str, size_t beginOffset, size_t endOffset);

    float random(float min, float max);
    sf::Vector2f random(sf::Vector2f min, sf::Vector2f max);
    sf::Vector2f random(sf::Vector2f max);
    bool randomBool();
    bool randomBool(float chance);

    template <typename TTarget, typename TOther>
    std::optional<std::pair<entt::entity, entt::entity>> which(entt::entity entity1, entt::entity entity2) {
        auto& registry = game::getRegistry();
        if (registry.any_of<TTarget>(entity1) && registry.any_of<TOther>(entity2)) {
            return std::make_pair(entity1, entity2);
        }
        if (registry.any_of<TTarget>(entity2) && registry.any_of<TOther>(entity1)) {
            return std::make_pair(entity2, entity1);
        }
        return std::nullopt;
    }

    template <
        typename TTarget, typename... Args,
        std::enable_if_t<(sizeof...(Args) > 2), int> = 0
    >
    std::optional<entt::entity> which(Args... args) {
        auto& registry = game::getRegistry();
        std::vector<entt::entity> entities {  args... };
        for (auto entity : entities) {
            if (registry.any_of<TTarget>(entity)) {
                return entity;
            }
        }
        return std::nullopt;
    }

    float lerp(float from, float dest, float damping);

    sf::Vector2f lerp(sf::Vector2f from, sf::Vector2f dest, float damping);

    float lerp(float from, float dest, float damping, sf::Time deltaTime);

    sf::Vector2f lerp(sf::Vector2f from, sf::Vector2f dest, float damping, sf::Time deltaTime);
}

#endif //COMMON_HPP
