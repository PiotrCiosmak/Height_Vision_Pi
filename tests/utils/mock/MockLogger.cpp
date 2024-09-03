#include "MockLogger.hpp"

using namespace height_vision_pi;

void MockLogger::formatMessage(std::ostringstream& oss, const std::string& format)
{
    oss << format;
}

std::vector<std::string> MockLogger::logs;
bool MockLogger::errorOccurred = false;