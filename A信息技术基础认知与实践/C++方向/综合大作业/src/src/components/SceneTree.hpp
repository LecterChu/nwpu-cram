// Game - NWPU C++ sp25
// Created on 2025/5/16
// by konakona418 (https://github.com/konakona418)

#ifndef SCENETREE_HPP
#define SCENETREE_HPP
#include <set>
#include <entt/entity/entity.hpp>

namespace game {
    struct CNode {};
    struct CUnmount {};

    struct CParent {
        CParent() = default;
        explicit CParent(const entt::entity parent) : m_parent(parent) {}

        void setParent(const entt::entity parent) { m_parent = parent; }
        [[nodiscard]] entt::entity getParent() const { return m_parent; }
    private:
        entt::entity m_parent { entt::null };
    };

    struct CChild {
        CChild() = default;
        explicit CChild(const entt::entity child) { m_children.insert(child); }
        explicit CChild(const std::set<entt::entity>& children) { m_children.insert(children.begin(), children.end()); }

        void addChild(const entt::entity child) { m_children.insert(child); }
        void removeChild(const entt::entity child) { m_children.erase(child); }

        [[nodiscard]] const std::set<entt::entity>& getChildren() const { return m_children; }
        [[nodiscard]] bool hasChild(const entt::entity child) const { return m_children.find(child) != m_children.end(); }

        void clearChildren() { m_children.clear(); }

        [[nodiscard]] bool hasChildren() const { return !m_children.empty(); }

    private:
        std::set<entt::entity> m_children {};
    };

    struct CSceneElementNeedsUpdate {};
}

#endif //SCENETREE_HPP
