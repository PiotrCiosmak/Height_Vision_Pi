#pragma once

#include "config/utils/ResolutionConfig.hpp"

namespace height_vision_pi
{
    struct CameraConfig
    {
        ResolutionConfig resolution;
        double fps;
        bool capture_mode;
        double brightness;
        double contrast;
        double saturation;
        double gain;
        double hue;
        bool auto_focus;
        bool auto_exposure;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CameraConfig,
                                       resolution,
                                       fps,
                                       capture_mode,
                                       brightness,
                                       contrast,
                                       saturation,
                                       gain,
                                       hue,
                                       auto_focus,
                                       auto_exposure)
    };
} // namespace height_vision_pi