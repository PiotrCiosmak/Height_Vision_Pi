#include "monitor/Monitor.hpp"
#include "Logger.hpp"

#include <fstream>

using namespace height_vision_pi;

Monitor::Monitor(const MonitorConfig& new_monitor_config) : DeviceMonitor{new_monitor_config} {}

void Monitor::checkCPUTemperature()
{
    const auto temperature = getCPUTemperature();
    const auto warning_temperature = monitor_config.cpu_monitor.warning_temperature;
    const auto error_temperature = monitor_config.cpu_monitor.error_temperature;

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
    auto file = std::ifstream{monitor_config.cpu_monitor.thermal_zone_path};
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