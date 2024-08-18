#pragma once

#include "config/utils/Resolution.hpp"

namespace height_vision_pi
{
    struct CameraConfig
    {
        Resolution resolution{2048, 1537};
        int fps = 10;
        bool capture_mode = true;
        double brightness = 0.5;
        double contrast = 0.5;
        double saturation = 0.5;
        double gain = 0.5;
        double hue = 0.5;
        bool auto_focus = true;
        bool auto_exposure = true;
    };
}
