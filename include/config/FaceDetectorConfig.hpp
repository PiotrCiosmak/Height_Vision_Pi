#pragma once

#include "config/utils/ResolutionConfig.hpp"

namespace height_vision_pi
{
    struct FaceDetectorConfig
    {
        std::string model_path;
        double scale_factor;
        int min_neighbors;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(FaceDetectorConfig,
                                       model_path,
                                       scale_factor,
                                       min_neighbors)
    };
} // namespace height_vision_pi