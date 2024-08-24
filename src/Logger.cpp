#include "Logger.hpp"

#include <iostream>

namespace height_vision_pi
{
    std::mutex Logger::exit_mutex;

    template<typename... Args>
    void Logger::log(const Level level, const std::string& format, Args... args)
    {
        std::ostringstream oss;
        formatMessage(oss, format, args...);

        switch (level)
        {
        case Level::INFO:
            std::cout << "[INFO] " << oss.str() << '\n';
            break;
        case Level::WARN:
            std::cout << "[WARN] " << oss.str() << '\n';
            break;
        case Level::ERROR:
            std::cerr << "[ERROR] " << oss.str() << '\n';
            exit_thread_safe();
        }
    }

    template<typename... Args> void Logger::info(const std::string& format, Args... args)
    {
        log(Level::INFO, format, args...);
    }

    template<typename... Args> void Logger::warn(const std::string& format, Args... args)
    {
        log(Level::WARN, format, args...);
    }

    template<typename... Args> void Logger::error(const std::string& format, Args... args)
    {
        log(Level::ERROR, format, args...);
    }

    template<typename T, typename... Args>
    void Logger::formatMessage(std::ostringstream& oss,
                               const std::string& format,
                               T value,
                               Args... args)
    {
        auto pos = format.find("{}");
        if (pos != std::string::npos)
        {
            oss << format.substr(0, pos) << value;
            formatMessage(oss, format.substr(pos + 2), args...);
        }
        else
        {
            oss << format;
        }
    }

    void Logger::formatMessage(std::ostringstream& oss, const std::string& format)
    {
        oss << format;
    }

    [[noreturn]] void Logger::exit_thread_safe()
    {
        const std::lock_guard lock(exit_mutex);
        std::exit(EXIT_FAILURE);
    }
} // namespace height_vision_pi
