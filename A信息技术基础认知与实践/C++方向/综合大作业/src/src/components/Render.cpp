// Game - NWPU C++ sp25
// Created on 2025/5/16
// by konakona418 (https://github.com/konakona418)

#include "Render.hpp"

#include "Common.hpp"
#include "Layout.hpp"
#include "Logger.hpp"

#include "ResourceManager.hpp"

game::CSpriteRenderComponent::CSpriteRenderComponent(const std::string& resourceName, const SpriteFrame& frame) {
    m_frame = ResourceManager::getSpriteFrameCache().load(entt::hashed_string { resourceName.c_str() },
        frame).first->second;
}

void game::CSpriteRenderComponent::update(sf::RenderTarget& target, const CGlobalTransform& globalTransform) {
    // this is not even a temporary solution.
    if (!m_sprite.has_value()) {
        if (m_frame->texture->textureRect.has_value()) {
            m_sprite = sf::Sprite(m_frame->texture->rawTextureRef->texture, m_frame->texture->textureRect.value());
        } else {
            m_sprite = sf::Sprite(m_frame->texture->rawTextureRef->texture);
        }
        // without this line, some strange rendering bug occurs
        // bug after adding this line, it just works fine, and I have no idea why.
        return;
    }

    m_sprite->setPosition(globalTransform.getPosition());
    m_sprite->setScale(globalTransform.getScale());
    m_sprite->setOrigin(globalTransform.getOrigin());

    auto size = globalTransform.getSize();

    auto textureRect = m_frame->texture->textureRect;
    if (textureRect.has_value() &&
        (textureRect.value().size.x >= static_cast<int>(size.x) && textureRect.value().size.y >= static_cast<int>(size.y))) {
        m_sprite->setTextureRect(textureRect.value());
    } else {
        m_sprite->setTextureRect({textureRect->position, {static_cast<int>(size.x), static_cast<int>(size.y)}});
    }
    target.draw(*m_sprite);
}

game::CTextRenderComponent::CTextRenderComponent(const std::string& resourceName, sf::Font&& font) {
    m_font = ResourceManager::getFontCache()
        .load(entt::hashed_string { resourceName.c_str() }, std::forward<sf::Font>(font))
        .first->second;
}

void game::CTextRenderComponent::update(sf::RenderTarget& target, const CGlobalTransform& globalTransform) {
    if (!m_textSprite.has_value()) {
        m_textSprite = sf::Text(m_font);
        return;
    }
    m_textSprite->setPosition(globalTransform.getPosition());
    m_textSprite->setScale(globalTransform.getScale());
    m_textSprite->setOrigin(globalTransform.getOrigin());

    m_textSprite->setString(processText(m_text, globalTransform.getSize()));

    m_textSprite->setFont(*m_font);
    m_textSprite->setFillColor(m_color);
    m_textSprite->setStyle(m_style);
    m_textSprite->setCharacterSize(m_textSize);

    target.draw(*m_textSprite);
}

sf::String game::CTextRenderComponent::processText(const sf::String& text, const sf::Vector2f& regionSize) const {
    sf::String result;
    float aggregateWidth = 0;
    for (size_t i = 0; i < text.getSize(); i++) {
        auto character = text[i];
        auto characterWidth = m_font->getGlyph(character, m_textSize, false).advance;
        if (aggregateWidth + characterWidth >= regionSize.x) {
            result += '\n';
            aggregateWidth = 0;
        }
        result += character;
        aggregateWidth += characterWidth;
    }
    return result;
}

game::CAnimatedSpriteRenderComponent::CAnimatedSpriteRenderComponent(const std::string& resourceName,
                                                                     const AnimatedFrames& frames, const bool loop) {
    auto frameRef = ResourceManager::getAnimatedFramesCache()
                    .load(entt::hashed_string{resourceName.c_str()}, frames).first->second;
    m_frameControl = FrameControl{frameRef, loop};
}

void game::CAnimatedSpriteRenderComponent::update(sf::RenderTarget& target, sf::Time deltaTime, const CGlobalTransform& globalTransform) {
    if (!m_sprite.has_value()) {
        if (m_frameControl.getCurrentFrame()->textureRect.has_value()) {
            m_sprite = sf::Sprite(m_frameControl.getCurrentFrame()->rawTextureRef->texture,
                m_frameControl.getCurrentFrame()->textureRect.value());
        } else {
            m_sprite = sf::Sprite(m_frameControl.getCurrentFrame()->rawTextureRef->texture);
        }
        // this is not necessary, just to keep behaviors consistent
        return;
    }

    m_sprite->setPosition(globalTransform.getPosition());
    m_sprite->setScale(globalTransform.getScale());
    m_sprite->setOrigin(globalTransform.getOrigin());

    auto size = globalTransform.getSize();

    m_frameControl.update(deltaTime);
    const auto currentFrame = m_frameControl.getCurrentFrame();
    m_sprite->setTexture(currentFrame->rawTextureRef->texture);

    auto textureRect = m_frameControl.getCurrentFrame()->textureRect;
    if (textureRect.has_value() &&
        (textureRect.value().size.x >= static_cast<int>(size.x) && textureRect.value().size.y >= static_cast<int>(size.y))) {
        m_sprite->setTextureRect(textureRect.value());
    } else {
        m_sprite->setTextureRect({{0, 0}, {static_cast<int>(size.x), static_cast<int>(size.y)}});
    }
    target.draw(*m_sprite);
}

void game::CAnimatedSpriteRenderComponent::FrameControl::update(const sf::Time deltaTime) {
    /*const auto totalTime = deltaTime + m_timeAccumulated;
    const auto frameOffset = static_cast<size_t>(std::roundf(totalTime / m_frames.duration));
    // getLogger().logDebug("FrameControl::update: " + std::to_string(frameOffset));
    for (size_t i = 0; i < frameOffset; i++) {
        nextFrame();
    }
    m_timeAccumulated = totalTime - m_frames.duration * static_cast<float>(frameOffset);*/
    m_timeAccumulated += deltaTime;
    auto offset = static_cast<size_t>(std::roundf(m_timeAccumulated / m_frames->duration));
    m_frameIndex = offset % m_frameCount;
    //getLogger().logDebug("FrameControl::update: " + std::to_string(deltaTime.asMilliseconds()));
}

void game::CAnimatedSpriteRenderComponent::FrameControl::nextFrame() {
    m_frameIndex = (m_frameIndex + 1) % m_frameCount;
}

entt::resource<game::Texture> game::CAnimatedSpriteRenderComponent::FrameControl::getCurrentFrame() const {
    return m_frames->frames[m_frameIndex];
}
void game::CAnimatedSpriteRenderComponent::FrameControl::reset() {
    m_frameIndex = 0;
}

void game::CTiledRenderComponent::addTile(TileIdType id, const SpriteFrame& frame) {
    m_tileControl.m_tiles.insert({id, Tile {frame, id}});
}

void game::CTiledRenderComponent::addTile(Tile tile) {
    m_tileControl.m_tiles.insert({tile.id, std::move(tile)});
}

void game::CTiledRenderComponent::addTile(TileIdType id, sf::Vector2i tilePlacement, sf::Vector2i tileSize) {
    m_tileControl.m_tileItemList.emplace_back(id, tilePlacement, tileSize);
}

void game::CTiledRenderComponent::addTile(const SingleTileItem& tileItem) {
    m_tileControl.m_tileItemList.push_back(tileItem);
}

void game::CTiledRenderComponent::update(sf::RenderTarget& target, sf::Time deltaTime, sf::Vector2f position,
    sf::Vector2f size, sf::Vector2f scale) {
    // size will be ignored
    m_tileControl.update(deltaTime);

    for (auto& tileItem : m_tileControl.m_tileItemList) {
        auto tile = m_tileControl.getTileById(tileItem.tileId);
        if (!tileItem.sprite.has_value()) {
            tileItem.sprite = sf::Sprite(tile.frame.texture->rawTextureRef->texture);
            tileItem.sprite->setTextureRect(tile.frame.texture->textureRect.value());
            // todo: implement tile animation
            tileItem.sprite->setOrigin(m_tileControl.m_baseTilePixelSize * 0.5f);

            auto placement = sf::Vector2f{
                static_cast<float>(tileItem.tilePlacement.x) * m_tileControl.m_baseTilePixelSize.x,
                static_cast<float>(tileItem.tilePlacement.y) * m_tileControl.m_baseTilePixelSize.y};
            tileItem.sprite->setPosition(position + placement);
            tileItem.sprite->setScale(scale);
        }
        target.draw(*tileItem.sprite);
    }
}

void game::CTiledRenderComponent::TileControl::update(sf::Time deltaTime) {
    // todo : implement tile animation
}

void game::CTiledRenderComponent::TileControl::reset() {
    // todo : implement tile animation
}

game::Tile& game::CTiledRenderComponent::TileControl::getTileById(TileIdType id) {
    return m_tiles.at(id);
}

void game::CShapeRenderComponent::update(sf::RenderTarget& target, const CGlobalTransform& globalTransform) const {
    if (!m_shape) {
        return;
    }

    m_shape->setPosition(globalTransform.getPosition());
    setShapeSize(m_shape.get(), globalTransform.getSize());
    m_shape->setScale(globalTransform.getScale());
    m_shape->setOrigin(globalTransform.getOrigin());

    target.draw(*m_shape);
}

void game::CShapeRenderComponent::setShapeSize(sf::Shape* rawPtr, const sf::Vector2f& size) {
    if (dynamic_cast<sf::RectangleShape*>(rawPtr) != nullptr) {
        dynamic_cast<sf::RectangleShape*>(rawPtr)->setSize(size);
        return;
    }
    if (dynamic_cast<sf::CircleShape*>(rawPtr) != nullptr) {
        dynamic_cast<sf::CircleShape*>(rawPtr)->setRadius(size.x * 0.5f);
        return;
    }
    throw std::runtime_error("CShapeRenderComponent::setShapeSize: unsupported shape type");
    // todo: add other shapes
}
