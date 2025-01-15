#pragma once

#include "utils/ResolutionConfig.hpp"
#include "utils/ColorConfig.hpp"

#include <filesystem>

namespace height_vision_pi
{
    struct AgeDetectorConfig
    {
        std::filesystem::path model_path;
        std::filesystem::path proto_path;
        double scale_factor;
        ResolutionConfig resolution;
        ColorConfig mean;
        bool swap_red_and_blue;
        bool crop;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(AgeDetectorConfig,
                                       model_path,
                                       proto_path,
                                       scale_factor,
                                       resolution,
                                       mean,
                                       swap_red_and_blue,
                                       crop)
    };
} // namespace height_vision_pi