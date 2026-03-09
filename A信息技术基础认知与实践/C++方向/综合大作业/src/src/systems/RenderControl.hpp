// Game - NWPU C++ sp25
// Created on 2025/5/16
// by konakona418 (https://github.com/konakona418)

#ifndef RENDERCONTROL_HPP
#define RENDERCONTROL_HPP
#include <entt/entity/entity.hpp>

#include "SFML/System/Time.hpp"


namespace sf {
    class RenderTarget;
}

namespace game {
    class SRenderSystem {
    public:
        static void update(sf::RenderTarget& target, size_t targetId, sf::Time deltaTime);
    private:
        static bool checkRenderTargetMask(size_t targetId, size_t mask);
    };

    class RenderUtils {
    public:
        [[nodiscard]] static bool isVisible(entt::entity entity);
        static void markAsInvisible(entt::entity entity);
        static void markAsVisible(entt::entity entity);
        static void markAsInvisibleNotRecurse(entt::entity entity);
        static void markAsVisibleNotRecurse(entt::entity entity);
    };
}



#endif //RENDERCONTROL_HPP
