// Game - NWPU C++ sp25
// Created on 2025/5/25
// by konakona418 (https://github.com/konakona418)


#include "SimpleMapLayer.hpp"
#include "components/Velocity.hpp"
#include "utils/TextureGenerator.hpp"
#include "utils/MovementUtils.hpp"
#include "utils/LazyLoader.hpp"
#include "ResourceManager.hpp"

namespace game::prefab {
    SimpleMapLayer SimpleMapLayer::create() {
        return SimpleMapLayer {};
    }

    SimpleMapLayer SimpleMapLayer::create(size_t renderOrder) {
        return SimpleMapLayer {renderOrder};
    }

    SimpleMapLayer::SimpleMapLayer(size_t renderOrder) {
        auto& registry = game::getRegistry();
        auto entity = registry.create();
        m_entity = entity;

        game::MovementUtils::builder()
                .setLocalPosition({0, 0})
                .setSize({2048, 2048})
                .setScale({1.0, 1.0})
                .setAnchor(game::CLayout::Anchor::MiddleCenter())
                .build(entity);
        game::SceneTreeUtils::attachSceneTreeComponents(entity);

        registry.emplace<game::CRenderComponent>(entity);
        registry.emplace<game::CRenderLayerComponent>(entity, renderOrder, 0);
        registry.emplace<game::CRenderTargetComponent>(
                entity,
                game::CRenderTargetComponent::GameComponent | game::CRenderTargetComponent::SmallMap);

        auto frame = loadTextureLayer(renderOrder);
        registry.emplace<game::CSpriteRenderComponent>(entity, frame);
    }

    entt::resource<game::SpriteFrame> SimpleMapLayer::loadTextureLayer(size_t layer) {
        return ResourceManager::getSpriteFrameCache().load(
                        entt::hashed_string {  ("layerMap" + std::to_string(layer)).c_str() },
                        StaticTextureGenerator()
                                .setOffset({0, 0})
                                .setSize({32, 32})
                                .generate("layerMap" + std::to_string(layer), "assets/image/map-layer" + std::to_string(layer) + ".png"))
                .first->second;
    }
} // game