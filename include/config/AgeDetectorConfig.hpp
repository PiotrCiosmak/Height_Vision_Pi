#pragma once

#include "utils/ResolutionConfig.hpp"
#include "utils/ColorConfig.hpp"

#include <nlohmann/json.hpp>

namespace height_vision_pi
{
    struct AgeDetectorConfig
    {
        std::string model_path;
        std::string proto_path;
        double scale_factor;
        ResolutionConfig resolution;
        ColorConfig color;
        bool swap_red_and_blue;
        bool crop;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(AgeDetectorConfig,
                                       model_path,
                                       proto_path,
                                       scale_factor,
                                       resolution,
                                       color,
                                       swap_red_and_blue,
                                       crop)
    };
} // namespace height_vision_pi
