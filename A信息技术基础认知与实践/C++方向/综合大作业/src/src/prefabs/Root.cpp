// Game - NWPU C++ sp25
// Created on 2025/5/21
// by konakona418 (https://github.com/konakona418)

#include "Root.hpp"

#include "Common.hpp"
#include "systems/SceneControl.hpp"
#include "utils/MovementUtils.hpp"

game::prefab::Root& game::prefab::Root::create() {
    auto& registry = getRegistry();

    static Root instance {};
    static bool isCreated = false;

    if (isCreated) {
        return instance;
    }

    instance.m_entity = registry.create();

    MovementUtils::attachLayoutComponents(instance.m_entity);
    SceneTreeUtils::attachSceneTreeComponents(instance.m_entity);

    isCreated = true;

    return instance;
}

void game::prefab::Root::unmount() {
    if (isUnmounted()) {
        return;
    }
    SceneTreeUtils::unmount(m_entity);
    m_unmounted = true;
}

void game::prefab::Root::mountChild(entt::entity child) const {
    SceneTreeUtils::attachChild(m_entity, child);
}

bool game::prefab::Root::isUnmounted() const {
    return m_unmounted || !getRegistry().valid(m_entity);
}

game::prefab::Root::~Root() {
    //unmount();
}
