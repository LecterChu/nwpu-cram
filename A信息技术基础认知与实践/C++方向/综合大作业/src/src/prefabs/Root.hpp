// Game - NWPU C++ sp25
// Created on 2025/5/21
// by konakona418 (https://github.com/konakona418)

#ifndef ROOT_HPP
#define ROOT_HPP
#include <entt/entity/entity.hpp>

namespace game::prefab {
    class Root {
    public:
        static Root& create();
        void unmount();
        void mountChild(entt::entity child) const;
        [[nodiscard]] bool isUnmounted() const;

        ~Root();
    private:
        entt::entity m_entity;
        bool m_unmounted = false;
        Root() = default;
    };
} // game

#endif //ROOT_HPP
