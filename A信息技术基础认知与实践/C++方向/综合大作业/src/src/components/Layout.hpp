// Game - NWPU C++ sp25
// Created on 2025/5/16
// by konakona418 (https://github.com/konakona418)

#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <entt/entity/entity.hpp>

#include "Common.hpp"
#include "Logger.hpp"
#include "SFML/Graphics.hpp"


namespace game {
    struct CHasLayout {};

    struct CLocalTransform {
        /**
         * When using any of the methods below,
         * remember to mark the entity as dirty.
         */

        CLocalTransform() = default;
        explicit CLocalTransform(const sf::Vector2f position) : m_position(position) {}

        void setPosition(const sf::Vector2f position) { m_position = position; }
        [[nodiscard]] sf::Vector2f getPosition() const { return m_position; }
        void move(const sf::Vector2f offset) { m_position += offset; }

        void setSize(const sf::Vector2f size) { m_size = size; }
        [[nodiscard]] sf::Vector2f getSize() const { return m_size; }

        void setScale(const sf::Vector2f scale) { m_scale = scale; }
        [[nodiscard]] sf::Vector2f getScale() const { return m_scale; }

    private:
        sf::Vector2f m_position {0.f, 0.f};
        sf::Vector2f m_size {0.f, 0.f};
        sf::Vector2f m_scale {1.f, 1.f};
    };

    struct CGlobalTransform {
        CGlobalTransform() = default;
        explicit CGlobalTransform(const sf::Vector2f position) : m_position(position) {}

        void setPosition(const sf::Vector2f position) { m_position = position; }
        [[nodiscard]] sf::Vector2f getPosition() const { return m_position; }

        void setSize(const sf::Vector2f size) { m_size = size; }
        [[nodiscard]] sf::Vector2f getSize() const { return m_size; }

        void setScale(const sf::Vector2f scale) { m_scale = scale; }
        [[nodiscard]] sf::Vector2f getScale() const { return m_scale; }

        void setOrigin(const sf::Vector2f origin) { m_origin = origin; }
        [[nodiscard]] sf::Vector2f getOrigin() const { return m_origin; }

    private:
        sf::Vector2f m_position {0.f, 0.f};
        sf::Vector2f m_size {0.f, 0.f};
        sf::Vector2f m_scale {1.f, 1.f};
        sf::Vector2f m_origin {0.f, 0.f};
    };

    struct CLayout {
        struct Anchor {
        private:
            sf::Vector2f m_anchor {0.f, 0.f};
        public:
            constexpr Anchor() = default;
            constexpr explicit Anchor(const sf::Vector2f anchor) : m_anchor(anchor) {}
            constexpr Anchor(float x, float y) : m_anchor(x, y) {}

            [[nodiscard]] sf::Vector2f getAnchorVec() const { return m_anchor; }

            constexpr static Anchor TopLeft() { return {0.f, 0.f}; }
            constexpr static Anchor TopCenter() { return {0.5f, 0.f}; }
            constexpr static Anchor TopRight() { return {1.f, 0.f}; }
            constexpr static Anchor MiddleLeft() { return {0.f, 0.5f}; }
            constexpr static Anchor MiddleCenter() { return {0.5f, 0.5f}; }
            constexpr static Anchor MiddleRight() { return {1.f, 0.5f}; }
            constexpr static Anchor BottomLeft() { return {0.f, 1.f}; }
            constexpr static Anchor BottomCenter() { return {0.5f, 1.f}; }
            constexpr static Anchor BottomRight() { return {1.f, 1.f}; }
        };

        enum class LayoutType {
            Relative,
            Absolute
        };

        CLayout() = default;
        explicit CLayout(const Anchor anchor) : m_anchor(anchor) {}
        explicit CLayout(const LayoutType layoutType) : m_layoutType(layoutType) {}
        CLayout(const Anchor anchor, const LayoutType layoutType) : m_anchor(anchor), m_layoutType(layoutType) {}

        void setAnchor(const Anchor anchor) { m_anchor = anchor; }
        [[nodiscard]] Anchor getAnchor() const { return m_anchor; }
        void setLayoutType(const LayoutType layoutType) { m_layoutType = layoutType; }
        [[nodiscard]] LayoutType getLayoutType() const { return m_layoutType; }

    private:
        Anchor m_anchor {Anchor::MiddleCenter()};
        LayoutType m_layoutType {LayoutType::Relative};
    };
}



#endif //LAYOUT_HPP
