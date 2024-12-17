#pragma once

#include <nlohmann/json.hpp>
#include <filesystem>

namespace height_vision_pi
{
    struct DiskMonitorConfig
    {
        std::filesystem::path path;
        double warning_usage;
        double error_usage;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(DiskMonitorConfig, path, warning_usage, error_usage)
    };
} // namespace height_vision_pi
