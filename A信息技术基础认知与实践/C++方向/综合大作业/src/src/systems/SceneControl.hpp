// Game - NWPU C++ sp25
// Created on 2025/5/16
// by konakona418 (https://github.com/konakona418)

#ifndef SCENECONTROL_HPP
#define SCENECONTROL_HPP

#include <entt/entt.hpp>

#include "Common.hpp"


namespace game {
    struct CChild;
    struct CParent;
    struct CNode;

    class SceneTreeUtils {
    public:
        SceneTreeUtils() = default;

        /**
         * note that this function just initializes the entity with the scene tree components,
         * it does not add anything to the scene tree.
         * @param entity
         * @return
         */
        static entt::entity attachSceneTreeComponents(entt::entity entity);

        static entt::entity detachSceneTreeComponents(entt::entity entity);

        static entt::entity attachChild(entt::entity parent, entt::entity child);

        static entt::entity detachChild(entt::entity parent, entt::entity child);

        static entt::entity attachParent(entt::entity child, entt::entity parent);

        static entt::entity detachParent(entt::entity child, entt::entity parent);

        static entt::entity markAsDirty(entt::entity entity);

        static entt::entity markAsClean(entt::entity entity);

        static entt::entity markAsCleanRecurse(entt::entity entity);

        static bool isDirty(entt::entity entity);

        static void unmount(entt::entity entity);
    };

    class SScenePositionUpdateSystem {
    public:
        SScenePositionUpdateSystem() = default;

        static void update();

        /**
         * Every time the entity is updated, it should be manually marked as dirty.
         * @param entity
         */
        static void markEntityAsDirty(entt::entity entity);

        static void markEntityAsClean(entt::entity entity);
    private:
        static void calculateLayout(entt::entity entity);
    };

    class SSceneUnmountSystem {
    public:
        SSceneUnmountSystem() = default;

        static void update();

        static void unmount(entt::entity entity);
    };

    class UnmountUtils {
    public:
        static void queueUnmount(entt::entity entity);
        static bool isUnmountingQueued(entt::entity entity);
    };

    class TreeLike {
    public:
        void unmount() {
            if (!isUnmounted()) {
                m_unmounted = true;
                game::SceneTreeUtils::unmount(m_entity);
            }
        }

        void mountChild(entt::entity child) const {
            game::SceneTreeUtils::attachChild(m_entity, child);
        }

        void unmountChild(entt::entity child) const {
            game::SceneTreeUtils::detachChild(m_entity, child);
            game::SceneTreeUtils::unmount(child);
        }

        [[nodiscard]] bool isUnmounted() const {
            return m_unmounted || !getRegistry().valid(m_entity);
        }

        [[nodiscard]] entt::entity getEntity() const { return m_entity; }

    protected:
        entt::entity m_entity {};
    private:
        // this should only work internally
        bool m_unmounted { false };
    };
}



#endif //SCENECONTROL_HPP
