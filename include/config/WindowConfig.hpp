#pragma once

#include "utils/ResolutionConfig.hpp"

#include <nlohmann/json.hpp>

#include <string>

namespace height_vision_pi
{
    struct WindowConfig
    {
        std::string name;
        ResolutionConfig resolution;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(WindowConfig, name, resolution)
    };
} // namespace height_vision_pi