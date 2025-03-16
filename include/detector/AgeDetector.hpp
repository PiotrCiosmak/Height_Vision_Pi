#pragma once

#include "config/AgeDetectorConfig.hpp"

#include <opencv2/opencv.hpp>

namespace height_vision_pi
{
    class AgeDetector
    {
    public:
        explicit AgeDetector(const AgeDetectorConfig& new_age_detector_config);
        [[nodiscard]] auto detect(
            const std::vector<std::optional<cv::Mat>>& detected_faces) -> std::vector<std::optional<int>>;

    private:
        [[nodiscard]] auto findMostProbableAge(std::vector<float> age_predictions) -> int;

        AgeDetectorConfig age_detector_config;
        cv::dnn::Net age_net;
        std::vector<int> ages;
    };
} // namespace height_vision_pi