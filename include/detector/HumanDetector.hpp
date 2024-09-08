#pragma once

#include "opencv2/opencv.hpp"

namespace height_vision_pi
{
    class HumanDetector
    {
    public:
        HumanDetector();

        [[nodiscard]] auto detect(cv::Mat& frame) const -> cv::Mat&;

    private:
        cv::HOGDescriptor hog;
    };
} // namespace height_vision_pi