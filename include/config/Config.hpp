#pragma once

#include "config/CameraConfig.hpp"
#include "config/DataSourceConfig.hpp"
#include "config/FaceDetectorConfig.hpp"
#include "config/HumanDetectorConfig.hpp"
#include "config/MonitorConfig.hpp"
#include "config/WindowConfig.hpp"
#include "config/AgeDetectorConfig.hpp"
#include "config/PupilsDistanceCalculatorConfig.hpp"

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
        FaceDetectorConfig face_detector;
        AgeDetectorConfig age_detector;
        PupilsDistanceCalculatorConfig pupils_distance_calculator;

    private:
        Config() = default;
        Config(const Config&) = delete;
        Config& operator=(const Config&) = delete;
        void load(const std::string& file_path);

        static std::once_flag init_flag;
    };
} // namespace height_vision_pi