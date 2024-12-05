#pragma once

#include <sstream>
#include <string>
#include <vector>

namespace height_vision_pi
{
    class MockLogger final
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
            auto oss = std::ostringstream{};
            formatMessage(oss, format, args...);

            switch (level)
            {
            case Level::INFO:
                logs.emplace_back("[INFO] " + oss.str());
                break;
            case Level::WARN:
                logs.emplace_back("[WARN] " + oss.str());
                break;
            case Level::ERROR:
                logs.emplace_back("[ERROR] " + oss.str());
                errorOccurred = true;
                break;
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

        static auto getLogs() -> const std::vector<std::string>& { return logs; }

        static auto hasErrorOccurred() -> bool { return errorOccurred; }

        static void clearLogs()
        {
            logs.clear();
            errorOccurred = false;
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

        static std::vector<std::string> logs;
        static bool errorOccurred;
    };
} // namespace height_vision_pi
