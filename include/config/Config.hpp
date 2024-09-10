#pragma once

#include "config/CameraConfig.hpp"
#include "config/DataSourceConfig.hpp"
#include "config/HumanDetectorConfig.hpp"
#include "config/MonitorConfig.hpp"
#include "config/WindowConfig.hpp"

#include <mutex>
#include <string>

namespace height_vision_pi
{
    class Config
    {
    public:
        [[nodiscard]] static auto get() -> Config&;

        CameraConfig camera;
        DataSourceConfig data_source;
        WindowConfig window;
        MonitorConfig monitor;
        HumanDetectorConfig human_detector;

    private:
        Config() = default;
        Config(const Config&) = delete;
        Config& operator=(const Config&) = delete;
        void load(const std::string& file_path);

        static std::once_flag init_flag;
    };
} // namespace height_vision_pi
