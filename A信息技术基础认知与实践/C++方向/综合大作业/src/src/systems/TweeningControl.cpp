// Game - NWPU C++ sp25
// Created on 2025/5/23
// by konakona418 (https://github.com/konakona418)

#include "TweeningControl.hpp"

#include "Common.hpp"
#include "components/Tweening.hpp"

void game::STweenSystem::update(sf::Time deltaTime) {
    auto& registry = game::getRegistry();
    for (auto [entity, tweening] : registry.view<game::CTweenComponent>().each()) {
        tweening.update(entity, deltaTime);
    }
}
