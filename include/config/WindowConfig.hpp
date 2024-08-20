#pragma once

#include <nlohmann/json.hpp>

#include <string>

namespace height_vision_pi
{
    struct WindowConfig
    {
        std::string name;
        Resolution resolution;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(WindowConfig, name, resolution)
    };
} // namespace height_vision_pi
