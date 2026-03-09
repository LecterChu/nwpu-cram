// Game - NWPU C++ sp25
// Created on 2025/5/20
// by konakona418 (https://github.com/konakona418)

#include "ScriptsControl.hpp"

#include "Common.hpp"
#include "components/Scripts.hpp"

void game::SScriptsSystem::update(sf::Time deltaTime) {
    for (auto entity : getRegistry().view<CScriptsComponent>()) {
        auto& scripts = getRegistry().get<CScriptsComponent>(entity);

        scripts.invokeOnce(entity);
        scripts.invokeUpdate(entity, deltaTime);
    }
}
