#pragma once

namespace height_vision_pi
{
    struct HumanDetectorConfig
    {
        std::string model_config_path;
        std::string model_weights_path;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(HumanDetectorConfig, model_config_path, model_weights_path)
    };
} // namespace height_vision_pi
