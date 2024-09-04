#include "monitor/Monitor.hpp"
#include "Logger.hpp"
#include "monitor/utils/BashCommand.hpp"

#include <fstream>

using namespace height_vision_pi;

Monitor::Monitor(const MonitorConfig& new_monitor_config) : MonitorDevice{new_monitor_config} {}

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

    auto temperature = std::string{};
    std::getline(file, temperature);
    file.close();

    constexpr auto millicelsius_to_celsius = 1000.0F;
    return std::stof(temperature) / millicelsius_to_celsius;
}

void Monitor::checkCPUUsage()
{
    // TODO
}

auto Monitor::getCPUUsage() -> float
{
    // TODO
}

void Monitor::checkDiskUsage()
{
    const auto usage = getDiskUsage();
    const auto warning_usage = monitor_config.disk_monitor.warning_usage_percentage;
    const auto error_usage = monitor_config.disk_monitor.error_usage_percentage;

    if (usage >= error_usage)
    {
        Logger::error("Disk usage is {} % , which exceeds the critical threshold of {} %. The "
                      "application will now shut down.",
                      usage,
                      error_usage);
    }
    else if (usage >= warning_usage)
    {
        Logger::warn("Disk usage is {} % , which exceeds the warning threshold of {} %.",
                     usage,
                     error_usage);
    }
}

auto Monitor::getDiskUsage() -> int
{
    const auto all_disk_statistics = runBashCommand("df").value();
    const auto disk_statistics = getDiskStatistics(all_disk_statistics);
    const auto disk_usage = getDiskPercentageUsage(disk_statistics);
    return disk_usage;
}

auto Monitor::getDiskStatistics(const std::string& all_disk_statistics) -> std::string
{
    auto stream = std::istringstream{all_disk_statistics};
    auto line = std::string{};

    while (std::getline(stream, line))
    {
        if (line.find(monitor_config.disk_monitor.path))
        {
            return line;
        }
    }

    Logger::error("Disk {} not found", monitor_config.disk_monitor.path);
}

auto Monitor::getDiskPercentageUsage(const std::string& disk_statistics) -> int
{
    std::cout<<"disk_statistics"<<disk_statistics<<"\n";
    const auto percent_position = disk_statistics.find('%');

    if (percent_position != std::string::npos)
    {
        const auto space_position = disk_statistics.rfind(' ', percent_position);

        if (space_position != std::string::npos)
        {
            const auto number_str =
                disk_statistics.substr(space_position + 1, percent_position - space_position - 1);
            std::cout<<"nuU"<<number_str<<std::endl;
            return std::stoi(number_str);
        }
    }

    Logger::error("Disk {} percentage usage not found", disk_statistics);
    return 0;
}

void Monitor::checkRAMUsage()
{
    // TODO
}

auto Monitor::getRAMUsage() -> float
{
    // TODO
}

void Monitor::checkGPUUsage()
{
    // TODO
}

auto Monitor::getGPUUsage() -> float
{
    // TODO
}
