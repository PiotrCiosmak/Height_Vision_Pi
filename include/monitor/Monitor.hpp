#pragma once

#include "monitor/DeviceMonitor.hpp"

namespace height_vision_pi
{
    class Monitor final : public DeviceMonitor
    {
    public:
        void checkCPUTemperature() override;

    private:
        [[nodiscard]] auto getCPUTemperature() -> float;
    };
} // namespace height_vision_pi