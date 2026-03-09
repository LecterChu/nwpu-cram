// Game - NWPU C++ sp25
// Created on 2025/5/21
// by konakona418 (https://github.com/konakona418)

#ifndef MOVEMENTUTILS_HPP
#define MOVEMENTUTILS_HPP


#include <entt/entity/entity.hpp>

#include "components/Layout.hpp"
#include "SFML/System/Vector2.hpp"

namespace game {
    class MovementUtils {
    public:
        struct Builder {
            Builder() = default;

            Builder& setSize(const sf::Vector2f size) {
                m_size = size;
                return *this;
            }

            Builder& setLocalPosition(const sf::Vector2f localPos) {
                m_localPos = localPos;
                return *this;
            }

            /**
             * avoid using this method
             * @param globalPos
             * @return
             */
            Builder& setGlobalPosition(const sf::Vector2f globalPos) {
                m_globalPos = globalPos;
                return *this;
            }

            Builder& setAnchor(const CLayout::Anchor anchor) {
                m_anchor = anchor;
                return *this;
            }

            Builder& setLayoutType(const CLayout::LayoutType layoutType) {
                m_layoutType = layoutType;
                return *this;
            }

            Builder& setScale(const sf::Vector2f scale) {
                m_scale = scale;
                return *this;
            }

            void build(const entt::entity& entity) const;

        private:
            sf::Vector2f m_size, m_localPos, m_globalPos, m_scale;
            CLayout::Anchor m_anchor{CLayout::Anchor::TopLeft()};
            CLayout::LayoutType m_layoutType{CLayout::LayoutType::Relative};
        };

        static Builder builder() {
            return {};
        }

        struct Flip {
            constexpr static sf::Vector2f Horizontal = {-1.f, 1.f};
            constexpr static sf::Vector2f Vertical = {1.f, -1.f};
            constexpr static sf::Vector2f None = {1.f, 1.f};
            constexpr static sf::Vector2f Both = {-1.f, -1.f};

            static bool isHorizontallyFlipped(const sf::Vector2f& scaleVec);
            static bool isVerticallyFlipped(const sf::Vector2f& scaleVec);
        };

        static entt::entity attachLayoutComponents(entt::entity entity);
        static void markAsDirty(entt::entity entity);
        static void markAsClean(entt::entity entity);

        static void setPosition(entt::entity entity, sf::Vector2f position);
        static void setSize(entt::entity entity, sf::Vector2f size);
        static void setScale(entt::entity entity, sf::Vector2f scale);

        static void setAnchor(entt::entity entity, CLayout::Anchor anchor);
        static void setLayoutType(entt::entity entity, CLayout::LayoutType layoutType);

        static void move(entt::entity entity, sf::Vector2f offset);

        static void flip(entt::entity entity, sf::Vector2f flip);
        static void flipHorizontal(entt::entity entity, bool flip);
        static void flipVertical(entt::entity entity, bool flip);

        static bool isOutOfMapBounds(entt::entity entity, sf::Vector2f minBound, sf::Vector2f maxBound, sf::Vector2f offset);
    };
} // game

#endif //MOVEMENTUTILS_HPP
