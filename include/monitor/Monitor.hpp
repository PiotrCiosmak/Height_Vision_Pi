#pragma once

#include "monitor/DeviceMonitor.hpp"

namespace height_vision_pi
{
    class Monitor final : public DeviceMonitor
    {
    public:
        explicit Monitor(const MonitorConfig& new_monitor_config);
        void checkCPUTemperature() override;

    private:
        [[nodiscard]] auto getCPUTemperature() -> float;
    };
} // namespace height_vision_pi