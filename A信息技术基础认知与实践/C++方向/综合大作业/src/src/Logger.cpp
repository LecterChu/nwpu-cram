// Game - NWPU C++ sp25
// Created on 2025/5/15
// by konakona418 (https://github.com/konakona418)

#include "Logger.hpp"

#include <iostream>
#include <sstream>

game::Logger::Logger(const bool debugging = false) {
    m_startTime = std::chrono::system_clock::now();
    m_debugging = debugging;
}

game::Logger::~Logger() {
    close();
}

void game::Logger::run() {
    m_cancellationToken.store(true, std::memory_order_release);

    m_worker = std::thread([this]() {
        while (m_cancellationToken.load(std::memory_order_acquire)) {
            std::unique_lock lock(m_mutex);
            m_cv.wait(lock, [this]() { return !m_logQueue.empty() || !m_cancellationToken.load(std::memory_order_acquire); });

            if (!m_cancellationToken.load(std::memory_order_acquire)) {
                while (!m_logQueue.empty()) {
                    logImpl();
                }
                break;
            }

            if (!m_logQueue.empty()) {
                while (!m_logQueue.empty()) {
                    logImpl();
                }
            }
        }
    });
}

void game::Logger::close() {
    if (!m_cancellationToken.exchange(false, std::memory_order_acq_rel)) {
        return;
    }
    m_cv.notify_one();
    m_worker.join();
}

std::string
game::Logger::concatLineFile(const std::string& message, int line, const std::string& file) {
    std::stringstream ss;
    ss << message << " (" << line << ":" << file << ")";
    return ss.str();
}

void game::Logger::log(const std::string& message, LogLevel level) {
    const auto timeSinceLaunch = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now() - m_startTime);

    {
        std::scoped_lock lock(m_mutex);
        m_logQueue.emplace_back(message, level, timeSinceLaunch.count());
        m_cv.notify_one();
    }
}

void game::Logger::logDebug(const std::string& message) {
    log(message, LogLevel::Debug);
}

void game::Logger::logInfo(const std::string& message) {
    log(message, LogLevel::Info);
}

void game::Logger::logWarn(const std::string& message) {
    log(message, LogLevel::Warn);
}

void game::Logger::logError(const std::string& message) {
    log(message, LogLevel::Error);
}

void game::Logger::logFatal(const std::string& message) {
    log(message, LogLevel::Fatal);
}

void game::Logger::logImpl() {
    auto msg = m_logQueue.front();
    m_logQueue.pop_front();
    std::cout << "[T+" << std::get<2>(msg) << "s] " << "[" << asLiteral(std::get<1>(msg)) << "] " << std::get<0>(msg) << std::endl;
}
