// Game - NWPU C++ sp25
// Created on 2025/5/15
// by konakona418 (https://github.com/konakona418)

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <atomic>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <string>
#include <thread>


namespace game {
    class Logger {
    public:
        enum class LogLevel {
            Debug = 0,
            Info = 1,
            Warn = 2,
            Error = 3,
            Fatal = 4,
        };

        static std::string asLiteral(const LogLevel level) {
            switch (level) {
            case LogLevel::Debug:
                return "DEBUG";
            case LogLevel::Info:
                return "INFO";
            case LogLevel::Warn:
                return "WARN";
            case LogLevel::Error:
                return "ERROR";
            case LogLevel::Fatal:
                return "FATAL";
            default:
                return "LOG";
            }
        }

        Logger() = default;

        explicit Logger(bool debugging);

        ~Logger();

        void run();
        void close();

        static std::string concatLineFile(const std::string& message, int line, const std::string& file);
        void log(const std::string& message, LogLevel level);
        void logDebug(const std::string& message);
        void logInfo(const std::string& message);
        void logWarn(const std::string& message);
        void logError(const std::string& message);
        void logFatal(const std::string& message);

    private:
        std::deque<std::tuple<std::string, LogLevel, int32_t>> m_logQueue;
        std::mutex m_mutex;
        std::condition_variable m_cv;
        std::atomic<bool> m_cancellationToken{ false };
        std::thread m_worker;

        bool m_debugging { false };

        std::chrono::system_clock::time_point m_startTime;

        void logImpl();
    };
}


#endif //LOGGER_HPP
