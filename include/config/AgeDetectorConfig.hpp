#pragma once

#include <nlohmann/json.hpp>

namespace height_vision_pi
{
    struct AgeDetectorConfig
    {
        std::string model_path;
        std::string proto_path;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(AgeDetectorConfig,
                                       model_path,
                                       proto_path)
    };
} // namespace height_vision_pi
