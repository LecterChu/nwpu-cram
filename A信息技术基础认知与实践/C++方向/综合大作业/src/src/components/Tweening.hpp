// Game - NWPU C++ sp25
// Created on 2025/5/23
// by konakona418 (https://github.com/konakona418)

#ifndef TWEENING_HPP
#define TWEENING_HPP
#include <functional>
#include <utility>
#include <entt/entity/entity.hpp>

#include "SFML/System/Time.hpp"

namespace game {

    struct CTweenComponent {
        struct EasingFunction {
            static float linear(float progress) { return progress; }
            static float quadratic(float progress);
            static float cubic(float progress);
            static float quartic(float progress);
            static float sine(float progress);
            static float exponential(float progress);
            static float circular(float progress);
        };

        CTweenComponent() = default;
        CTweenComponent(float beginValue, float endValue)
            : m_beginValue(beginValue), m_endValue(endValue) {}

        void setDuration(sf::Time duration) { m_duration = duration; }
        [[nodiscard]] sf::Time getDuration() const { return m_duration; }

        void setDelay(sf::Time delay) { m_delay = delay; }
        [[nodiscard]] sf::Time getDelay() const { return m_delay; }

        void setBeginValue(float beginValue) { m_beginValue = beginValue; }
        [[nodiscard]] float getBeginValue() const { return m_beginValue; }

        void setEndValue(float endValue) { m_endValue = endValue; }
        [[nodiscard]] float getEndValue() const { return m_endValue; }

        void setRange(float beginValue, float endValue) {
            m_beginValue = beginValue;
            m_endValue = endValue;
        }
        [[nodiscard]] std::pair<float, float> getRange() const { return { m_beginValue, m_endValue }; }

        void setEasingFunction(std::function<float(float progress)> easingFunction) { m_easingFunction = std::move(easingFunction); }
        void setCallback(std::function<void(entt::entity entity, float value)> callback) { m_callback = std::move(callback); }
        void setCompletionCallback(std::function<void(entt::entity entity)> callback) { m_completionCallback = std::move(callback); }

        [[nodiscard]] float getRatioValue() const;

        template <typename Fn, std::enable_if_t<std::is_invocable_v<Fn>, int> = 0>
        void setEasingFunction(Fn&& easingFunction) {
            m_easingFunction = std::function<float(float)>(std::forward<Fn>(easingFunction));
        }

        template <typename Fn, std::enable_if_t<std::is_invocable_v<Fn, float>, int> = 0>
        void setCallback(Fn&& callback) {
            m_callback = std::function<void(entt::entity, float)>(std::forward<Fn>(callback));
        }

        template <typename Fn, std::enable_if_t<std::is_invocable_v<Fn>, int> = 0>
        void setCompletionCallback(Fn&& callback) {
            m_completionCallback = std::function<void(entt::entity)>(std::forward<Fn>(callback));
        }

        void update(entt::entity entity, sf::Time deltaTime);
        void restart();

    private:
        sf::Time m_duration;
        sf::Time m_elapsed;
        sf::Time m_delay;

        bool m_running { false };

        float m_beginValue { 0.f };
        float m_endValue { 1.f };

        std::function<float(float progress)> m_easingFunction { EasingFunction::linear };
        std::function<void(entt::entity entity, float value)> m_callback;
        std::function<void(entt::entity entity)> m_completionCallback;
    };

} // game

#endif //TWEENING_HPP
