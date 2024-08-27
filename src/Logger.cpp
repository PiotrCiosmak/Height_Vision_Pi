#include "Logger.hpp"

using namespace height_vision_pi;

void Logger::formatMessage(std::ostringstream& oss, const std::string& format)
{
    oss << format;
}
