#pragma once

#include "monitor/MonitorDevice.hpp"

namespace height_vision_pi
{
    class Monitor final : public MonitorDevice
    {
    public:
        explicit Monitor(const MonitorConfig& new_monitor_config);
        void checkCPUTemperature() override;
        void checkCPUUsage() override;
        void checkDiskUsage() override;
        void checkRAMUsage() override;
        void checkGPUUsage() override;

    private:
        [[nodiscard]] auto getCPUTemperature() -> float;
        [[nodiscard]] auto getCPUUsage() -> float;
        [[nodiscard]] auto getDiskUsage() -> int;
        [[nodiscard]] auto getDiskStatistics(const std::string& all_disk_statistics) -> std::string;
        [[nodiscard]] auto getDiskPercentageUsage(const std::string& disk_statistics) -> int;
        [[nodiscard]] auto getRAMUsage() -> int;
        [[nodiscard]] auto getRAMStatistics(const std::string& all_ram_statistics) -> std::string;
        [[nodiscard]] auto getRAMPercentageUsage(const std::string& ram_statistics) -> int;
        [[nodiscard]] auto getGPUUsage() -> float;
    };
} // namespace height_vision_pi