// Game - NWPU C++ sp25
// Created on 2025/5/20
// by konakona418 (https://github.com/konakona418)

#ifndef COLLISION_HPP
#define COLLISION_HPP
#include <cstdint>
#include <vector>

#include "SFML/Graphics/Rect.hpp"

namespace game {
    namespace _internal {
        inline bool mask(const uint32_t mask, const size_t layerOffset) {
            return !!(mask & (0x1 << layerOffset));
        }
    }
    struct CCollisionComponent {};

    struct CCollisionAABBComponent {
        explicit CCollisionAABBComponent(const sf::Vector2f& size) : m_boundingBoxSize(size) {}

        [[nodiscard]] sf::Vector2f getBoundingBox() const { return m_boundingBoxSize; }
        void setBoundingBox(sf::Vector2f size) { m_boundingBoxSize = size; }
    private:
        sf::Vector2f m_boundingBoxSize;
    };

    struct CCollisionCircleComponent {
        explicit CCollisionCircleComponent(float radius) : m_radius(radius) {}

        [[nodiscard]] float getRadius() const { return m_radius; }
        void setRadius(float radius) { m_radius = radius; }
    private:
        float m_radius;
    };

    struct CCollisionLayerComponent {
        CCollisionLayerComponent() = default;
        CCollisionLayerComponent(uint32_t layer, uint32_t mask) : m_layer(layer), m_mask(mask) {}

        [[nodiscard]] uint32_t getLayer() const { return m_layer; }
        void setLayer(uint32_t layer) { m_layer = layer; }

        [[nodiscard]] bool isOnLayer(size_t layerOffset) const { return _internal::mask(m_mask, layerOffset); }

        void setMask(uint32_t mask) { m_mask = mask; }
        [[nodiscard]] uint32_t getMask() const { return m_mask; }

        [[nodiscard]] bool isOnMask(size_t layerOffset) const { return _internal::mask(m_mask, layerOffset); }

    private:
        uint32_t m_layer;
        uint32_t m_mask;
    };

    class CollisionUtils {
    public:
        static uint32_t getCollisionMask(size_t layer);
        static uint32_t getCollisionMask(const std::vector<size_t>& layers);

        static bool shouldCollide(uint32_t layer1, uint32_t layer2, uint32_t mask1, uint32_t mask2);

        template <
            typename... Layers,
            std::enable_if_t<(sizeof...(Layers) > 1), int> = 0
        >
        static uint32_t getCollisionMask(Layers... layers) {
            return getCollisionMask(std::vector<size_t> { layers... });
        }
    };

} // game

#endif //COLLISION_HPP
