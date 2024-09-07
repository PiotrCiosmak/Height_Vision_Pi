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
        Logger::error("CPU temperature is {} °C, which exceeds the critical threshold of {} °C. "
                      "The application will now shut down.",
                      temperature,
                      error_temperature);
    }
    else if (temperature >= warning_temperature)
    {
        Logger::warn("CPU temperature is {} °C, which exceeds the warning threshold of {} °C.",
                     temperature,
                     warning_temperature);
    }
    else
    {
        Logger::info("CPU temperature is {} °C, which is within the normal operating range.",
                     temperature);
    }
}

auto Monitor::getCPUTemperature() const -> float
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
    const auto usage = getCPUUsage();
    const auto warning_usage = monitor_config.cpu_monitor.warning_usage;
    const auto error_usage = monitor_config.cpu_monitor.error_usage;

    if (usage >= error_usage)
    {
        Logger::error(
            "CPU usage is equal to {} %, which exceeds the critical threshold of {} %. The "
            "application will now shut down.",
            usage,
            error_usage);
    }
    else if (usage >= warning_usage)
    {
        Logger::warn("CPU usage is equal to {} %, which exceeds the warning threshold of {} %.",
                     usage,
                     warning_usage);
    }
}

auto Monitor::getCPUUsage() const -> int
{
    const auto cores_number = stoi(runBashCommand("nproc").value());
    auto file = std::ifstream{monitor_config.cpu_monitor.usage_path};
    if (!file.is_open())
    {
        Logger::error("Unable to open CPU usage file");
    }

    auto line = std::string{};
    std::getline(file, line);

    auto stream = std::istringstream{line};
    auto usage = 0.0;
    if (stream >> usage)
    {
        return static_cast<int>(usage * 100 / cores_number);
    }
    Logger::error("Unable to read CPU usage");
    return 0;
}

void Monitor::checkDiskUsage()
{
    const auto usage = getDiskUsage();
    const auto warning_usage = monitor_config.disk_monitor.warning_usage;
    const auto error_usage = monitor_config.disk_monitor.error_usage;

    if (usage >= error_usage)
    {
        Logger::error(
            "Disk usage is equal to {} %, which exceeds the critical threshold of {} %. The "
            "application will now shut down.",
            usage,
            error_usage);
    }
    else if (usage >= warning_usage)
    {
        Logger::warn("Disk usage is equal to {} %, which exceeds the warning threshold of {} %.",
                     usage,
                     warning_usage);
    }
}

auto Monitor::getDiskUsage() const -> int
{
    const auto all_disk_statistics = runBashCommand("df").value();
    const auto disk_statistics = getDiskStatistics(all_disk_statistics);
    return getDiskUsagePercent(disk_statistics);
}

auto Monitor::getDiskStatistics(const std::string& all_disk_statistics) const -> std::string
{
    auto stream = std::istringstream{all_disk_statistics};
    auto line = std::string{};

    while (std::getline(stream, line))
    {
        if (line.find(monitor_config.disk_monitor.path) != std::string::npos)
        {
            return line;
        }
    }

    Logger::error("Disk {} not found", monitor_config.disk_monitor.path);
    return "";
}

auto Monitor::getDiskUsagePercent(const std::string& disk_statistics) const -> int
{
    const auto percent_position = disk_statistics.find('%');

    if (percent_position != std::string::npos)
    {
        const auto space_position = disk_statistics.rfind(' ', percent_position);

        if (space_position != std::string::npos)
        {
            const auto number_str =
                disk_statistics.substr(space_position + 1, percent_position - space_position - 1);
            return std::stoi(number_str);
        }
    }

    Logger::error("Disk {} usage not found", disk_statistics);
    return 0;
}

void Monitor::checkRAMUsage()
{
    const auto usages = getRAMsUsage();
    const auto warning_usage = monitor_config.ram_monitor.warning_usage;
    const auto error_usage = monitor_config.ram_monitor.error_usage;

    for (const auto& usage : usages)
    {
        if (usage >= error_usage)
        {
            Logger::error(
                "RAM usage is equal to {} %, which exceeds the critical threshold of {} %. The "
                "application will now shut down.",
                usage,
                error_usage);
        }
        else if (usage >= warning_usage)
        {
            Logger::warn("RAM usage is equal to {} %, which exceeds the warning threshold of {} %.",
                         usage,
                         warning_usage);
        }
    }
}

auto Monitor::getRAMsUsage() const -> std::vector<int>
{
    const auto all_ram_statistics = runBashCommand("free").value();
    const auto ram_statistics = getRAMsStatistics(all_ram_statistics);
    return getRAMsUsagePercent(ram_statistics);
}

auto Monitor::getRAMsStatistics(const std::string& all_ram_statistics) const
    -> std::vector<std::string>
{
    auto stream = std::istringstream{all_ram_statistics};
    auto line = std::string{};
    auto ram_statistics = std::vector<std::string>{};

    while (std::getline(stream, line))
    {
        if (line.find("Mem:") != std::string::npos)
        {
            ram_statistics.push_back(line);
        }
    }

    if (ram_statistics.empty())
    {
        Logger::error("RAM statistics not found");
    }

    return ram_statistics;
}

auto Monitor::getRAMsUsagePercent(const std::vector<std::string>& rams_statistics) const
    -> std::vector<int>
{
    auto rams_usage_percent = std::vector<int>{};

    for (const auto& ram_statistics : rams_statistics)
    {
        auto stream = std::istringstream{ram_statistics};
        auto numbers = std::vector<int>{};
        auto word = std::string{};

        while (stream >> word)
        {
            try
            {
                numbers.emplace_back(std::stoi(word));
            }
            catch (const std::invalid_argument&)
            {
                continue;
            }
        }

        if (numbers.size() >= 2)
        {
            const auto total = numbers[0];
            const auto used = numbers[1];
            rams_usage_percent.push_back(static_cast<int>(std::round(1.0 * total / used)));
        }
    }

    if (rams_usage_percent.empty())
    {
        Logger::error("Unable to parse RAM statistics");
    }

    return rams_usage_percent;
}

void Monitor::checkGPUUsage()
{
    const auto usage = getGPUUsage();
    const auto warning_usage = monitor_config.gpu_monitor.warning_usage;
    const auto error_usage = monitor_config.gpu_monitor.error_usage;

    if (usage >= error_usage)
    {
        Logger::error(
            "GPU usage is equal to {} %, which exceeds the critical threshold of {} %. The "
            "application will now shut down.",
            usage,
            error_usage);
    }
    else if (usage >= warning_usage)
    {
        Logger::warn("GPU usage is equal to {} %, which exceeds the warning threshold of {} %.",
                     usage,
                     warning_usage);
    }
}

auto Monitor::getGPUUsage() const -> int
{
    return 0;
    // TODO
}
