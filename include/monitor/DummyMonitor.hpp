#pragma once

#include "monitor/MonitorDevice.hpp"

namespace height_vision_pi
{
    class DummyMonitor final : public MonitorDevice
    {
    public:
        DummyMonitor();
        void checkCPUTemperature() override{};
        void checkCPUUsage() override{};
        void checkDiskUsage() override{};
        void checkRAMsUsage() override{};
        void checkGPUTemperature() override{};
        void checkGPUUsage() override{};
    };
} // namespace height_vision_pi