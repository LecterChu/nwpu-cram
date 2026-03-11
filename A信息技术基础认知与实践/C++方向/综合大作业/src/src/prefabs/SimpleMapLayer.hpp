// Game - NWPU C++ sp25
// Created on 2025/5/25
// by konakona418 (https://github.com/konakona418)

#ifndef GAME25SP_SIMPLEMAPLAYER_HPP
#define GAME25SP_SIMPLEMAPLAYER_HPP

#include "systems/SceneControl.hpp"
#include "components/Render.hpp"

namespace game::prefab {

    class SimpleMapLayer : public game::TreeLike {
    public:
        static SimpleMapLayer create();
        static SimpleMapLayer create(size_t renderOrder);
    private:
        static constexpr size_t RENDER_LAYER = 0;
        explicit SimpleMapLayer(size_t renderOrder = 0);

        static entt::resource<game::SpriteFrame> loadTextureLayer(size_t layer);
    };

} // game

#endif //GAME25SP_SIMPLEMAPLAYER_HPP
