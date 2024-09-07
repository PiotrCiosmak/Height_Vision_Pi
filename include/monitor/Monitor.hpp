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
        void checkRAMsUsage() override;
        void checkGPUTemperature() override;
        void checkGPUUsage() override;

    private:
        [[nodiscard]] auto getCPUTemperature() const -> double;
        [[nodiscard]] auto getCPUUsage() const -> int;
        [[nodiscard]] auto getDiskUsage() const -> int;
        [[nodiscard]] auto getDiskStatistics(const std::string& all_disk_statistics) const
            -> std::string;
        [[nodiscard]] auto getDiskUsagePercent(const std::string& disk_statistics) const -> int;
        [[nodiscard]] auto getRAMsUsage() const -> std::vector<int>;
        [[nodiscard]] auto getRAMsStatistics(const std::string& all_ram_statistics) const
            -> std::vector<std::string>;
        [[nodiscard]] auto getRAMsUsagePercent(
            const std::vector<std::string>& rams_statistics) const -> std::vector<int>;
        [[nodiscard]] auto getGPUTemperature() const -> double;
        [[nodiscard]] auto getGPUUsage() const -> int;
    };
} // namespace height_vision_pi