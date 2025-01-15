#pragma once

#include <nlohmann/json.hpp>

namespace height_vision_pi
{
    struct ResolutionConfig
    {
        int x;
        int y;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ResolutionConfig, x, y)
    };
} // namespace height_vision_pi