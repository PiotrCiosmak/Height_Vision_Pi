#pragma once

#include "config/utils/ResolutionConfig.hpp"

#include <filesystem>

namespace height_vision_pi
{
    struct HumanDetectorConfig
    {
        std::filesystem::path model_config_path;
        std::filesystem::path model_weights_path;
        ResolutionConfig resolution;
        double confidence_threshold;
        double nms_score_threshold;
        double nms_threshold;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(HumanDetectorConfig,
                                       model_config_path,
                                       model_weights_path,
                                       resolution,
                                       confidence_threshold,
                                       nms_score_threshold,
                                       nms_threshold)
    };
} // namespace height_vision_pi