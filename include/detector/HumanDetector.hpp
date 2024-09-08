#pragma once

#include "opencv2/opencv.hpp"

namespace height_vision_pi
{
    class HumanDetector
    {
    public:
        HumanDetector();

        [[nodiscard]] auto detect(cv::Mat& frame) -> cv::Mat&;

    private:
        cv::dnn::Net net;
    };
} // namespace height_vision_pi