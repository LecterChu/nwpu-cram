// Game - NWPU C++ sp25
// Created on 2025/5/20
// by konakona418 (https://github.com/konakona418)

#include "Scripts.hpp"

game::CScriptsComponent::CScriptsComponent(entt::delegate<void(entt::entity, sf::Time)> invokeUpdate) {
    m_invokeUpdate = invokeUpdate;
}

game::CScriptsComponent::CScriptsComponent(entt::delegate<void(entt::entity)> invokeOnce,
    entt::delegate<void(entt::entity, sf::Time)> invokeUpdate) {
    m_invokeOnce = invokeOnce;
    m_invokeUpdate = invokeUpdate;
}

void game::CScriptsComponent::invokeOnce(entt::entity entity) {
    if (m_invokeOnce.has_value()) {
        m_invokeOnce.value()(entity);
    }
    m_invokeOnce = std::nullopt;
}

void game::CScriptsComponent::invokeUpdate(entt::entity entity, sf::Time deltaTime) const {
    if (m_invokeUpdate.has_value()) {
        m_invokeUpdate.value()(entity, deltaTime);
    }
}
