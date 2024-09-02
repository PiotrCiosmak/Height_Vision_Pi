#pragma once

namespace height_vision_pi
{
    class DeviceMonitor
    {
    public:
        DeviceMonitor() = default;
        virtual void checkCPUTemperature() = 0;
        virtual ~DeviceMonitor() = default;
    };
} // namespace height_vision_pi