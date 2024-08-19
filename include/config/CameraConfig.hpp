#pragma once

#include "config/utils/Resolution.hpp"

namespace height_vision_pi
{
    struct CameraConfig
    {
        Resolution resolution;
        double fps;
        bool capture_mode;
        double brightness;
        double contrast;
        double saturation;
        double gain;
        double hue;
        bool auto_focus;
        bool auto_exposure;
    };
}
