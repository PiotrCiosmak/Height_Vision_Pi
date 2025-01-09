#pragma once

#include <nlohmann/json.hpp>
#include <filesystem>

namespace height_vision_pi
{
    struct PupilsDistanceCalculatorConfig
    {
        std::filesystem::path model_path;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PupilsDistanceCalculatorConfig,
                                       model_path)
    };
} // namespace height_vision_pi
