// Game - NWPU C++ sp25
// Created on 2025/5/15
// by konakona418 (https://github.com/konakona418)

#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>


namespace game {

    struct Task {
        Task() = default;
        ~Task() = default;

        explicit Task(std::function<void()> task) : m_task(std::move(task)) {}
        Task(std::function<void()> task, std::function<void()> onCompletion) : m_task(std::move(task)), m_onCompletion(std::move(onCompletion)) {}

        template <typename Fn, std::enable_if_t<std::is_invocable_v<Fn>, int> = 0>
        explicit Task(Fn&& task) : m_task(std::function<void()>(std::forward<Fn>(task))) {}

        std::function<void()> m_task;
        std::function<void()> m_onCompletion;

        void run() const {
            if (m_task) {
                m_task();
            }
            if (m_onCompletion) {
                m_onCompletion();
            }
        }
    };

    class ThreadPool {
    public:
        ThreadPool() = default;
        explicit ThreadPool(const uint32_t threadCount) : m_threadCount(threadCount) {}

        ~ThreadPool();

        void close();

        void syncWait(Task&& task);

        template <
            typename... Args,
            std::enable_if_t<(std::is_same_v<Task, std::decay_t<Args>> && ...), int> = 0,
            std::enable_if_t<sizeof...(Args) >= 1, int> = 0
        >
        void waitForAll(Args&&... tasks) {
            waitForAll(std::vector<Task>{ std::forward<Args>(tasks)... });
        }

        void waitForAll(const std::vector<Task>& tasks);

        void schedule(const Task& task);
        void schedule(std::function<void()> task);

        [[nodiscard]] bool isBusy() const;

        template <typename Fn, std::enable_if_t<std::is_invocable_v<Fn>>>
        void schedule(Fn&& task) {
            schedule(std::function<void()>(std::forward<Fn>(task)));
        }

        void run();

    private:
        uint32_t m_threadCount { 4 };
        std::mutex m_waitMutex;
        std::condition_variable m_cv;
        std::vector<std::thread> m_threads;

        std::mutex m_tasksMutex;
        std::deque<Task> m_tasks;
        std::atomic<bool> m_cancellationToken { false };

        void executor();
    };

} // game



#endif //THREADPOOL_HPP
