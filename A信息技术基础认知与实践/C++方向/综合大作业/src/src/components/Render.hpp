// Game - NWPU C++ sp25
// Created on 2025/5/16
// by konakona418 (https://github.com/konakona418)

#ifndef RENDER_HPP
#define RENDER_HPP
#include <entt/resource/resource.hpp>
#include <utility>

#include "Common.hpp"
#include "Logger.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/String.hpp"
#include "SFML/System/Time.hpp"

namespace game {
    struct Texture;
    struct CGlobalTransform;

    struct CRenderComponent {};

    // specify the layer for the component to be rendered
    struct CRenderLayerComponent {
        CRenderLayerComponent() = default;
        explicit CRenderLayerComponent(size_t layer) : m_layer(layer), m_order(0) {}
        CRenderLayerComponent(size_t layer, size_t order) : m_layer(layer), m_order(order) {}

        [[nodiscard]] size_t getLayer() const { return m_layer; }
        void setLayer(size_t layer) { m_layer = layer; }
        [[nodiscard]] size_t getOrder() const { return m_order; }
        void setOrder(size_t order) { m_order = order; }
    private:
        size_t m_layer;
        size_t m_order;
    };

    struct CRenderTargetComponent {
        CRenderTargetComponent() = default;
        explicit CRenderTargetComponent(size_t targetId) : m_targetId(targetId) {}

        static constexpr size_t GameComponent = (1 << 0);
        static constexpr size_t UI = (1 << 1);
        static constexpr size_t SmallMap = (1 << 2);

        void setTargetId(size_t targetId) { m_targetId = targetId; }
        [[nodiscard]] size_t getTargetId() const { return m_targetId; }
    private:
        size_t m_targetId { GameComponent };
    };

    struct SpriteFrame {
        sf::Time duration;
        entt::resource<Texture> texture;

        SpriteFrame(const SpriteFrame& other) = default;
        SpriteFrame(entt::resource<Texture> texture, sf::Time duration) : duration(duration), texture(std::move(texture)) {}
        explicit SpriteFrame(entt::resource<Texture> texture) : duration(sf::seconds(1)), texture(std::move(texture)) {}
    };

    struct CSpriteRenderComponent {
        CSpriteRenderComponent(const std::string& resourceName, const SpriteFrame& frame);

        explicit CSpriteRenderComponent(entt::resource<SpriteFrame> frame) : m_frame(std::move(frame)) {}

        void setFrame(entt::resource<SpriteFrame> frame) { m_frame = std::move(frame); }
        [[nodiscard]] entt::resource<SpriteFrame> getFrame() const { return m_frame; }

        std::optional<sf::Sprite*> getSprite() { return (m_sprite.has_value() ? std::optional<sf::Sprite*>(&*m_sprite) : std::nullopt); }

        void update(sf::RenderTarget& target, const CGlobalTransform& globalTransform);
    private:
        entt::resource<SpriteFrame> m_frame;
        std::optional<sf::Sprite> m_sprite;
    };

    struct CTextRenderComponent {
        CTextRenderComponent(const std::string& resourceName, sf::Font&& font);
        explicit CTextRenderComponent(entt::resource<sf::Font> font) : m_font(std::move(font)) {}

        void setFont(entt::resource<sf::Font> font) { m_font = std::move(font); }
        [[nodiscard]] entt::resource<sf::Font> getFont() const { return m_font; }

        void setColor(sf::Color color) { m_color = color; }
        [[nodiscard]] sf::Color getColor() const { return m_color; }

        void setStyle(sf::Text::Style style) { m_style = style; }
        [[nodiscard]] sf::Text::Style getStyle() const { return m_style; }

        void setText(const sf::String& text) { m_text = text; }
        [[nodiscard]] const sf::String& getText() const { return m_text; }

        void setTextSize(size_t textSize) { m_textSize = textSize; }
        [[nodiscard]] size_t getTextSize() const { return m_textSize; }

        void update(sf::RenderTarget& target, const CGlobalTransform& globalTransform);
    private:
        entt::resource<sf::Font> m_font;
        std::optional<sf::Text> m_textSprite { std::nullopt };
        sf::String m_text;
        sf::Color m_color { sf::Color::White };
        sf::Text::Style m_style { sf::Text::Style::Regular };
        size_t m_textSize { 16 };

        sf::String processText(const sf::String& text, const sf::Vector2f& regionSize) const;
    };

    struct AnimatedFrames {
        entt::hashed_string animationName { "<anonymous>" };
        std::vector<entt::resource<Texture>> frames;
        bool loop = true;
        sf::Time duration;
    };

    struct CAnimatedSpriteRenderComponent {
        CAnimatedSpriteRenderComponent(const std::string& resourceName, const AnimatedFrames& frames, bool loop = true);
        explicit CAnimatedSpriteRenderComponent(entt::resource<AnimatedFrames> frames, const bool loop = true)
            : m_frameControl(std::move(frames), loop) {}

        /**
         * This may cause unintended behavior.
         * Refer to: setFrames()
         * @param frames
         */
        void setFramesForced(entt::resource<AnimatedFrames> frames) {
            m_frameControl = FrameControl { std::move(frames), m_frameControl.m_loop };
        }

        /**
         * Only change the frames if the animation name is different.
         * @param frames
         */
        void setFrames(entt::resource<AnimatedFrames> frames) {
            if (m_frameControl.m_frames->animationName != frames->animationName) {
                m_frameControl = FrameControl { std::move(frames), m_frameControl.m_loop };
            }
        }

        [[nodiscard]] entt::resource<AnimatedFrames> getFrames() const { return m_frameControl.m_frames; }
        void update(sf::RenderTarget& target, sf::Time deltaTime, const CGlobalTransform& globalTransform);

    private:
        struct FrameControl {
            entt::resource<AnimatedFrames> m_frames;
            size_t m_frameIndex;
            size_t m_frameCount;
            bool m_loop;
            sf::Time m_timeAccumulated = sf::Time::Zero;

            FrameControl(entt::resource<AnimatedFrames> frames, bool loop)
                : m_frames(std::move(frames)), m_frameIndex(0), m_frameCount(m_frames->frames.size()), m_loop(loop) {
                if (m_frames->frames.empty()) {
                    getLogger().logError("AnimatedFrames is empty. Is this a desired behavior?");
                }
            }
            void update(sf::Time deltaTime);
            void nextFrame();
            [[nodiscard]] entt::resource<Texture> getCurrentFrame() const;
            void reset();
        };

        FrameControl m_frameControl { entt::resource<AnimatedFrames>(nullptr), false};
        std::optional<sf::Sprite> m_sprite;
    };

    using TileIdType = uint32_t;
    struct Tile {
        SpriteFrame frame;
        TileIdType id {};

        Tile(const SpriteFrame& frame, TileIdType id) : frame(frame), id(id) {}
    };

    struct SingleTileItem {
        TileIdType tileId;
        sf::Vector2i tilePlacement;
        sf::Vector2i tileSize;
        std::optional<sf::Sprite> sprite;

        SingleTileItem(TileIdType tileId, sf::Vector2i tilePlacement, sf::Vector2i tileSize)
            : tileId(tileId), tilePlacement(tilePlacement), tileSize(tileSize) {}
    };

    struct CTiledRenderComponent {
        explicit CTiledRenderComponent(sf::Vector2f baseTilePixelSize) : m_tileControl(baseTilePixelSize) {}
        void addTile(TileIdType id, const SpriteFrame& frame);
        void addTile(Tile tile);

        void addTile(TileIdType id, sf::Vector2i tilePlacement, sf::Vector2i tileSize);
        void addTile(const SingleTileItem& tileItem);

        void update(sf::RenderTarget& target, sf::Time deltaTime,
            sf::Vector2f position, sf::Vector2f size, sf::Vector2f scale);
    private:
        struct TileControl {
            std::unordered_map<TileIdType, Tile> m_tiles {};
            std::vector<SingleTileItem> m_tileItemList {};
            sf::Vector2f m_baseTilePixelSize;

            void update(sf::Time deltaTime);
            void reset();
            Tile& getTileById(TileIdType id);

            explicit TileControl(sf::Vector2f baseTilePixelSize) : m_baseTilePixelSize(baseTilePixelSize) {};
        };
        TileControl m_tileControl;

    };

    struct CShapeRenderComponent {
        explicit CShapeRenderComponent(std::unique_ptr<sf::Shape> shape) : m_shape(std::move(shape)) {}
        void update(sf::RenderTarget& target, const CGlobalTransform& globalTransform) const;

        void setShape(std::unique_ptr<sf::Shape> shape) { m_shape = std::move(shape); }
        [[nodiscard]] sf::Shape* getShape() const { return m_shape.get(); }
    private:
        std::unique_ptr<sf::Shape> m_shape { nullptr };
        static void setShapeSize(sf::Shape* rawPtr, const sf::Vector2f& size);
    };
} // game

#endif //RENDER_HPP
