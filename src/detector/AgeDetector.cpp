#include "detector/AgeDetector.hpp"
#include "Logger.hpp"

using namespace height_vision_pi;

AgeDetector::AgeDetector(const AgeDetectorConfig& new_age_detector_config) :
    age_detector_config{new_age_detector_config},
    ages{1, 6, 12, 17, 28, 40, 50, 60}
{
    age_net = cv::dnn::readNet(age_detector_config.model_path, age_detector_config.proto_path);
    if (age_net.empty())
    {
        Logger::error("Failed to load age prediction model.");
    }
}

auto AgeDetector::detect(const std::vector<cv::Mat>& detected_faces) -> std::vector<int>
{
    auto detected_ages = std::vector<int>{};
    for (const auto& face : detected_faces)
    {
        age_net.setInput(face);
        const auto age_predictions = std::vector<float>{age_net.forward()};
        const auto age = findMostProbableAge(age_predictions);
        detected_ages.push_back(age);
    }
    return detected_ages;
}

auto AgeDetector::findMostProbableAge(std::vector<float> age_predictions) -> int
{
    const auto most_probable_age_index = std::distance(age_predictions.begin(),
                                                       std::ranges::max_element(age_predictions));
    const auto age = ages[most_probable_age_index];
    return age;
}