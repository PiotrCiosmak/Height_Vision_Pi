#pragma once

namespace height_vision_pi
{
    class CPUTemperatureMonitor
    {
    public:
        static void checkTemperature();

    private:
        [[nodiscard]] static auto getTemperature() -> float;
    };
} // namespace height_vision_pi