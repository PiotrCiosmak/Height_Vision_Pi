#include "detector//HumanDetector.hpp"

using namespace height_vision_pi;

HumanDetector::HumanDetector()
{
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}

auto HumanDetector::detect(cv::Mat& frame) const -> cv::Mat&
{
    std::vector<cv::Rect> humans;

    hog.detectMultiScale(frame, humans);

    for (const auto& human : humans)
    {
        cv::rectangle(frame, human, cv::Scalar(0, 255, 0), 3);
    }

    return frame;
}