// Game - NWPU C++ sp25
// Created on 2025/5/23
// by konakona418 (https://github.com/konakona418)

#include "Tweening.hpp"

#include <cmath>
#include <algorithm>

namespace game {
    float CTweenComponent::EasingFunction::quadratic(float progress) {
        if (progress < 0.5f) {
            return 2.0f * progress * progress;
        }
        return 1.0f - std::powf(-2.0f * progress + 2.0f, 2) / 2.0f;
    }

    float CTweenComponent::EasingFunction::cubic(float progress) {
        if (progress < 0.5f) {
            return 4.0f * progress * progress * progress;
        }
        return 1.0f - std::powf(-2.0f * progress + 2.0f, 3) / 2.0f;
    }

    float CTweenComponent::EasingFunction::quartic(float progress) {
        if (progress < 0.5f) {
            return 8.0f * progress * progress * progress * progress;
        }
        return 1.0f - std::powf(-2.0f * progress + 2.0f, 4) / 2.0f;
    }

    float CTweenComponent::EasingFunction::sine(float progress) {
        return -(std::cosf(M_PI * progress) - 1.0f) / 2.0f;
    }

    float CTweenComponent::EasingFunction::exponential(float progress) {
        if (progress == 0.0f) return 0.0f;
        if (progress == 1.0f) return 1.0f;
        if (progress < 0.5f) {
            return std::powf(2.0f, 20.0f * progress - 10.0f) / 2.0f;
        }
        return (2.0f - std::powf(2.0f, -20.0f * progress + 10.0f)) / 2.0f;
    }

    float CTweenComponent::EasingFunction::circular(float progress) {
        if (progress < 0.5f) {
            return (1.0f - std::sqrtf(1.0f - std::powf(2.0f * progress, 2))) / 2.0f;
        }
        return (std::sqrtf(1.0f - std::powf(-2.0f * progress + 2.0f, 2)) + 1.0f) / 2.0f;
    }

    void CTweenComponent::update(entt::entity entity, sf::Time deltaTime) {
        if (!m_running) {
            return;
        }

        m_elapsed += deltaTime;
        if (m_elapsed < m_delay) {
            return;
        }

        const auto realElapsed = m_elapsed - m_delay;

        if (realElapsed >= m_duration) {
            //m_elapsed = sf::Time::Zero;
            m_running = false;
            if (m_completionCallback) {
                m_completionCallback(entity);
            }
            return;
        }

        float progress = std::clamp(realElapsed.asSeconds() / m_duration.asSeconds(), 0.f, 1.f);
        if (m_callback) {
            m_callback(entity, m_easingFunction(progress) * (m_endValue - m_beginValue) + m_beginValue);
        }
    }

    void CTweenComponent::restart() {
        m_elapsed = sf::Time::Zero;
        m_running = true;
    }

    float CTweenComponent::getRatioValue() const {
        return m_easingFunction(m_elapsed.asSeconds() / m_duration.asSeconds());
    }
} // game