#include "detector//HumanDetector.hpp"

using namespace height_vision_pi;

HumanDetector::HumanDetector()
{
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}

auto HumanDetector::detect(cv::Mat& frame) const -> cv::Mat&
{
    std::vector<cv::Rect> humans;

    hog.detectMultiScale(frame, humans, 0, cv::Size(8, 8), cv::Size(32, 32), 1.05, 2);

    for (const auto& human : humans)
    {
        // Filtrowanie detekcji
        if (human.height > 100 && human.width > 50 && human.height < 400)
        {
            // Rysowanie ramki tylko dla spełnionych kryteriów
            cv::rectangle(frame, human, cv::Scalar(0, 255, 0), 3);
        }
    }

    return frame;
}