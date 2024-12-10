#pragma once

#include <nlohmann/json.hpp>

namespace height_vision_pi
{
    struct ColorConfig
    {
        double red;
        double green;
        double blue;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ColorConfig, red, green, blue)
    };
} // namespace height_vision_pi
