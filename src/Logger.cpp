#include "Logger.hpp"

using namespace height_vision_pi;

auto Logger::getCurrentTime() -> std::tm
{
    const auto now = std::chrono::system_clock::now();
    const auto current_time = std::chrono::system_clock::to_time_t(now);
    const auto local_time = *std::localtime(&current_time);
    return local_time;
}

void Logger::formatMessage(std::ostringstream& oss, const std::string& format)
{
    oss << format;
}
