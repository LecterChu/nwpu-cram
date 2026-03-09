// Game - NWPU C++ sp25
// Created on 2025/5/15
// by konakona418 (https://github.com/konakona418)

#include "ThreadPool.hpp"

#include "Common.hpp"
#include "Logger.hpp"

game::ThreadPool::~ThreadPool() {
    close();
}

void game::ThreadPool::close() {
    getLogger().logDebug("ThreadPool::close()");
    if (!m_cancellationToken.exchange(false, std::memory_order_acq_rel)) {
        return;
    }

    m_cv.notify_all();
    for (auto& thread : m_threads) {
        thread.join();
    }
}

void game::ThreadPool::syncWait(Task&& task) {
    std::mutex waitMutex;
    std::condition_variable waitCond;
    std::atomic<bool> waitFlag = false;

    schedule([&]() {
        task.run();
        waitFlag.store(true, std::memory_order_release);
        waitCond.notify_one();
    });

    std::unique_lock waitLock(waitMutex);
    waitCond.wait(waitLock, [&]() { return waitFlag.load(std::memory_order_acquire); });
}

void game::ThreadPool::waitForAll(const std::vector<Task>& tasks) {
    std::mutex waitMutex;
    std::condition_variable waitCond;
    std::atomic<int> waitCount = 0;
    size_t taskCount = tasks.size();

    for (auto& task : tasks) {
        // explicit better than implicit
        schedule([&waitMutex, &waitCond, &waitCount, task, taskCount]() {
            task.run();
            if (waitCount.fetch_add(1, std::memory_order_acq_rel) == taskCount - 1) {
                waitCond.notify_one();
            }
        });
    }
    std::unique_lock<std::mutex> waitLock(waitMutex);
    waitCond.wait(waitLock, [&waitCount, taskCount]() { return waitCount.load(std::memory_order_acquire) == taskCount; });
}

void game::ThreadPool::schedule(const Task& task) {
    std::unique_lock lock(m_tasksMutex);
    m_tasks.push_back(task);

    m_cv.notify_one();
}

void game::ThreadPool::schedule(std::function<void()> task) {
    schedule(Task(std::move(task)));
}

bool game::ThreadPool::isBusy() const {
    return !m_tasks.empty();
}

void game::ThreadPool::run() {
    getLogger().logDebug("ThreadPool::run");
    m_cancellationToken.exchange(true, std::memory_order_relaxed);
    m_threads.reserve(m_threadCount);

    for (uint32_t i = 0; i < m_threadCount; i++) {
        m_threads.emplace_back(&ThreadPool::executor, this);
    }
}

void game::ThreadPool::executor() {
    while (m_cancellationToken.load(std::memory_order_acquire)) {
        {
            std::unique_lock<std::mutex> lock(m_waitMutex);
            m_cv.wait(lock, [this] { return !m_tasks.empty() || !m_cancellationToken.load(std::memory_order_relaxed); });
        }

        if (!m_cancellationToken.load(std::memory_order_acquire)) {
            while (!m_tasks.empty()) {
                Task task;
                {
                    std::scoped_lock scopedLock(m_tasksMutex);

                    // in case that fake waking up occurred.
                    if (!m_tasks.empty()) {
                        task = m_tasks.front();
                        m_tasks.pop_front();
                    }
                }
                task.run();
            }
            return;
        }

        while (!m_tasks.empty()) {
            Task task;
            {
                std::scoped_lock scopedLock(m_tasksMutex);
                if (!m_tasks.empty()) {
                    task = m_tasks.front();
                    m_tasks.pop_front();
                }
            }
            task.run();
        }
    }
}
