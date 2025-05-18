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

auto AgeDetector::detect(
    const std::vector<cv::Mat>& detected_faces) -> std::vector<std::optional<int>>
{
    auto detected_ages = std::vector<std::optional<int>>{};
    for (const auto& face : detected_faces)
    {
        if (face.empty())
        {
            detected_ages.push_back(std::nullopt);
        }
        else
        {
            const auto blob = cv::dnn::blobFromImage(face,
                                                     age_detector_config.scale_factor,
                                                     cv::Size{age_detector_config.resolution.x,
                                                              age_detector_config.resolution.y},
                                                     cv::Scalar{
                                                         age_detector_config.mean.red,
                                                         age_detector_config.mean.green,
                                                         age_detector_config.mean.blue},
                                                     age_detector_config.swap_red_and_blue,
                                                     age_detector_config.crop);
            age_net.setInput(blob);
            const auto age_predictions = std::vector<float>{age_net.forward()};
            const auto age = findMostProbableAge(age_predictions);
            detected_ages.push_back(age);
        }
    }

    const auto detected_ages_count = std::ranges::count_if(detected_ages,
                                                           [](const auto& age)
                                                           {
                                                               return age.has_value();
                                                           });
    Logger::info("{} out of {} possible ages detected", detected_ages_count, detected_ages.size());
    return detected_ages;
}

auto AgeDetector::findMostProbableAge(std::vector<float> age_predictions) const -> int
{
    const auto most_probable_age_index = std::distance(age_predictions.begin(),
                                                       std::ranges::max_element(age_predictions));
    const auto age = ages[most_probable_age_index];
    return age;
}