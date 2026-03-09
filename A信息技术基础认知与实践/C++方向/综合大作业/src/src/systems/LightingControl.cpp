// Game - NWPU C++ sp25
// Created on 2025/5/24
// by konakona418 (https://github.com/konakona418)

#include "LightingControl.hpp"
#include "Common.hpp"
#include "components/Lighting.hpp"
#include "components/Layout.hpp"
#include "components/SceneTree.hpp"

namespace game {
    void SLightingSystem::update(sf::RenderTarget& target) {
        auto& registry = game::getRegistry();
        auto& shader = getShader();

        for (auto [entity, lighting] : registry.view<CLightingComponent>().each()) {
            // this means that the entity's position hasn't been properly calculated.
            // by doing so, we can avoid to many entities' illumination set at the origin,
            // which is the default position of un-calculated entities.
            if (registry.any_of<game::CSceneElementNeedsUpdate>(entity)) {
                continue;
            }

            auto& globalTransform = registry.get<CGlobalTransform>(entity);
            auto radius = lighting.getRadius();

            sf::RectangleShape shape({radius * 2.f, radius * 2.f});
            shape.setOrigin({radius, radius});
            shape.setPosition(globalTransform.getPosition());
            shape.setFillColor(lighting.getColor());
            shape.setTexture(&getDummyTexture());

            shader.setUniform("lightColor", sf::Glsl::Vec4(lighting.getColor()));
            shader.setUniform("attenuationExponent", lighting.getAttenuationExponent());

            target.draw(shape, sf::RenderStates(&shader));
        }
    }

    sf::Shader& SLightingSystem::getShader() {
        static sf::Shader s_shader;
        static bool s_initialized = false;

        const static std::string c_vertShader = R"(
            void main()
            {
                gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
                gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
                gl_FrontColor = gl_Color;
            }
        )";

        const static std::string c_fragShader = R"(
            #version 120

            uniform vec4 lightColor;
            uniform float attenuationExponent;

            float absolute(float x) {
                return x < 0.0 ? -x : x;
            }
            void main() {
                vec2 texCoords = gl_TexCoord[0].xy;
                vec2 relativePos = texCoords - vec2(0.5);

                float distance = length(relativePos);
                if (distance > 0.5) {
                    discard;
                    return;
                }

                float realDistance = distance * 2.0;
                //float attenuation = 1.0 / (attenuationConstant + attenuationLinear * realDistance + attenuationQuadratic * realDistance * realDistance);
                float attenuation = pow(1.0 - realDistance, attenuationExponent);

                vec4 finalColor = lightColor;
                finalColor.a = lightColor.a * attenuation;

                gl_FragColor = finalColor;
            }
        )";

        if (!s_initialized) {
            if (!s_shader.loadFromMemory(std::string_view(c_vertShader), std::string_view(c_fragShader))) {
                throw std::runtime_error("LightingControl: failed to load shader");
            }
            s_initialized = true;
        }
        return s_shader;
    }

    sf::Texture& SLightingSystem::getDummyTexture() {
        static sf::Texture s_dummyTexture;
        static sf::Image s_dummyImage;
        static bool s_initialized = false;

        if (!s_initialized) {
            s_dummyImage = sf::Image({1, 1});
            s_dummyTexture = sf::Texture(s_dummyImage);
            s_initialized = true;
        }
        return s_dummyTexture;
    }
}