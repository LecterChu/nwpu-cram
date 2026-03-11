// Game - NWPU C++ sp25
// Created on 2025/5/16
// by konakona418 (https://github.com/konakona418)

#include "ResourceManager.hpp"

game::TextureLoader::result_type
game::TextureLoader::operator()( const std::string& fileName, const sf::IntRect& rect) {
    auto raw = ResourceManager::getRawTextureCache()
            .load(entt::hashed_string { fileName.c_str() }, fileName).first->second;
    return std::make_shared<Texture>(raw, rect);
}

game::TextureLoader::result_type game::TextureLoader::operator()(const std::string &fileName) {
    auto raw = ResourceManager::getRawTextureCache()
            .load(entt::hashed_string { fileName.c_str() }, fileName).first->second;
    return std::make_shared<Texture>(raw);
}
