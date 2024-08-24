#pragma once

#include <nlohmann/json.hpp>

namespace height_vision_pi
{
    struct Resolution
    {
        int x;
        int y;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Resolution, x, y)
    };
} // namespace height_vision_pi
