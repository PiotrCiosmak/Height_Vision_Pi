#pragma once

#include <mutex>
#include <sstream>

namespace height_vision_pi
{
    class Logger
    {
    public:
        enum class Level
        {
            INFO,
            WARN,
            ERROR
        };

        template<typename... Args>
        static void log(Level level, const std::string& format, Args... args);

        template<typename... Args> static void info(const std::string& format, Args... args);

        template<typename... Args> static void warn(const std::string& format, Args... args);

        template<typename... Args> static void error(const std::string& format, Args... args);

    private:
        template<typename T, typename... Args>
        static void formatMessage(std::ostringstream& oss,
                                  const std::string& format,
                                  T value,
                                  Args... args);
        static void formatMessage(std::ostringstream& oss, const std::string& format);
        static void exit_thread_safe();

        static std::mutex exit_mutex;
    };
} // namespace height_vision_pi
