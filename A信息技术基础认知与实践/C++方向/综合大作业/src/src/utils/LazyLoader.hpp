// Game - NWPU C++ sp25
// Created on 2025/5/21
// by konakona418 (https://github.com/konakona418)

#ifndef LAZYLOADER_HPP
#define LAZYLOADER_HPP

#include <functional>
#include <optional>
#include <stdexcept>

namespace game {

    template <typename T>
    class Lazy {
    public:

        template <typename Fn, std::enable_if_t<std::is_invocable_v<Fn>, int> = 0>
        explicit Lazy(Fn&& fn) {
            m_fn = std::function<T()>(std::forward<Fn>(fn));
        }

        T get() {
            if (!m_fn) { throw std::runtime_error("Lazy value not initialized"); }

            if (!m_value.has_value()) {
                m_value = m_fn();
            }
            return m_value.value();
        }

        T operator*() {
            return get();
        }

    private:
        std::optional<T> m_value { std::nullopt };
        std::function<T()> m_fn { nullptr };
    };

} // game

#endif //LAZYLOADER_HPP
