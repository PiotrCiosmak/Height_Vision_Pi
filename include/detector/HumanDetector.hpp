#pragma once

#include "config/HumanDetectorConfig.hpp"

#include <opencv2/opencv.hpp>

namespace height_vision_pi
{
    class HumanDetector
    {
    public:
        explicit HumanDetector(const HumanDetectorConfig& new_human_detector_config);

        [[nodiscard]] auto detect(cv::Mat& frame) -> std::vector<cv::Mat>;

    private:
        HumanDetectorConfig human_detector_config;
        cv::dnn::Net net;
    };
} // namespace height_vision_pi