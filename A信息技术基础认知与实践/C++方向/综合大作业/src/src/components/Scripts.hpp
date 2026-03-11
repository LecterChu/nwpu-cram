// Game - NWPU C++ sp25
// Created on 2025/5/20
// by konakona418 (https://github.com/konakona418)

#ifndef SCRIPTS_HPP
#define SCRIPTS_HPP
#include <optional>
#include <entt/entity/entity.hpp>
#include <entt/signal/delegate.hpp>

#include "SFML/System/Time.hpp"


namespace game {
    struct CScriptsComponent {
        CScriptsComponent() = default;
        explicit CScriptsComponent(entt::delegate<void(entt::entity, sf::Time)> invokeUpdate);
        CScriptsComponent(entt::delegate<void(entt::entity)> invokeOnce,
            entt::delegate<void(entt::entity, sf::Time)> invokeUpdate);

        void invokeOnce(entt::entity entity);
        void invokeUpdate(entt::entity entity, sf::Time deltaTime) const;

        void setInvokeOnce(entt::delegate<void(entt::entity)> invokeOnce) { m_invokeOnce = invokeOnce; }
        void setInvokeUpdate(entt::delegate<void(entt::entity, sf::Time)> invokeUpdate) { m_invokeUpdate = invokeUpdate; };
    private:
        std::optional<entt::delegate<void(entt::entity)>> m_invokeOnce;
        std::optional<entt::delegate<void(entt::entity, sf::Time)>> m_invokeUpdate;
    };

    using InvokeOnceDelegate = entt::delegate<void(entt::entity)>;
    using InvokeUpdateDelegate = entt::delegate<void(entt::entity, sf::Time)>;
} // game



#endif //SCRIPTS_HPP
