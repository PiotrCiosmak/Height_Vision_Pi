#pragma once

#include "monitor/MonitorDevice.hpp"

namespace height_vision_pi
{
    class DummyMonitor final : public MonitorDevice
    {
    public:
        explicit DummyMonitor(const MonitorConfig& new_monitor_config);
        void checkCPUTemperature() override;
    };
} // namespace height_vision_pi