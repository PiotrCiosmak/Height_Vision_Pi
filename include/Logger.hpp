#pragma once

#include <iostream>
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
        static void log(Level level, const std::string& format, Args... args)
        {
            std::ostringstream oss;
            formatMessage(oss, format, args...);

            switch (level)
            {
            case Level::INFO:
                std::cout << "[INFO] " << oss.str() << '\n' << std::flush;
                break;
            case Level::WARN:
                std::cout << "[WARN] " << oss.str() << '\n' << std::flush;
                break;
            case Level::ERROR:
                std::cerr << "[ERROR] " << oss.str() << '\n' << std::flush;
                std::exit(EXIT_FAILURE);
            }
        }

        template<typename... Args> static void info(const std::string& format, Args... args)
        {
            log(Level::INFO, format, args...);
        }

        template<typename... Args> static void warn(const std::string& format, Args... args)
        {
            log(Level::WARN, format, args...);
        }

        template<typename... Args> static void error(const std::string& format, Args... args)
        {
            log(Level::ERROR, format, args...);
        }

    private:
        template<typename T, typename... Args>
        static void formatMessage(std::ostringstream& oss,
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

        static void formatMessage(std::ostringstream& oss, const std::string& format);
    };
} // namespace height_vision_pi
