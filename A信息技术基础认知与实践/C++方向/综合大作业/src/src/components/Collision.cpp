// Game - NWPU C++ sp25
// Created on 2025/5/20
// by konakona418 (https://github.com/konakona418)

#include "Collision.hpp"

namespace game {
    uint32_t CollisionUtils::getCollisionMask(size_t layer) {
        return (0x1 << layer);
    }

    uint32_t CollisionUtils::getCollisionMask(const std::vector<size_t>& layers) {
        uint32_t mask = 0;
        for (const auto& layer : layers) {
            mask |= (0x1 << layer);
        }
        return mask;
    }

    bool CollisionUtils::shouldCollide(
        uint32_t layer1, uint32_t layer2,
        uint32_t mask1, uint32_t mask2) {
        return !!(layer1 & mask2) && !!(layer2 & mask1);
    }
} // game