#include "monitor/Monitor.hpp"
#include "Logger.hpp"

#include <fstream>

using namespace height_vision_pi;

void Monitor::checkCPUTemperature()
{
    const auto temperature = getCPUTemperature();
    //TODO values from config
    constexpr auto warning_temperature = 80.0F;
    constexpr auto error_temperature = 85.0F;

    if (temperature >= error_temperature)
    {
        Logger::error("CPU temperature is {} °C , which exceeds the critical threshold of {} °C. "
                      "The application will now shut down.",
                      temperature,
                      error_temperature);
    }
    else if (temperature >= warning_temperature)
    {
        Logger::warn("CPU temperature is {} °C , which exceeds the warning threshold of {} °C.",
                     temperature,
                     warning_temperature);
    }
    else
    {
        Logger::info("CPU temperature is {} °C, which is within the normal operating range.",
                     temperature);
    }
}

auto Monitor::getCPUTemperature() -> float
{
    //TODO path from config
    auto file = std::ifstream{"/sys/class/thermal/thermal_zone0/temp"};
    if (!file.is_open())
    {
        Logger::error("Unable to open temperature file");
        return 0;
    }

    std::string line;
    std::getline(file, line);
    file.close();

    constexpr auto millicelsius_to_celsius = 1000.0F;
    return std::stof(line) / millicelsius_to_celsius;
}