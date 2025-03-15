#include "calculator/PupilsDistanceCalculator.hpp"
#include "Logger.hpp"

using namespace height_vision_pi;

PupilsDistanceCalculator::PupilsDistanceCalculator(
    const PupilsDistanceCalculatorConfig& new_pupils_distance_calculator_config) :
    pupils_distance_calculator_config{new_pupils_distance_calculator_config}
{
    pupil_detector.load(pupils_distance_calculator_config.model_path);
    if (pupil_detector.empty())
    {
        Logger::error("Failed to load age prediction model.");
    }
}

auto PupilsDistanceCalculator::calculate(
    const std::vector<cv::Mat>& detected_faces) -> std::vector<double>
{
    auto distances = std::vector<double>{};

    for (const auto& face : detected_faces)
    {
        auto pupil_positions = detectPupils(face);

        auto distance = calculateDistanceBetweenPupils(pupil_positions);

        distances.push_back(distance);
    }

    const auto calculated_pupils_distance_count = std::ranges::count_if(distances,
        [](const auto& distance)
        {
            return distance != 0;
        });

    Logger::info("{} out of {} possible pupils distance calculated",
                 calculated_pupils_distance_count,
                 distances.size());

    return distances;
}

auto PupilsDistanceCalculator::detectPupils(const cv::Mat& face) -> std::pair<cv::Point, cv::Point>
{
    auto eyes = std::vector<cv::Rect>{};
    auto pupil_positions = std::pair<cv::Point, cv::Point>{{0, 0}, {0, 0}};

    pupil_detector.detectMultiScale(face, eyes);

    if (eyes.size() >= 2)
    {
        pupil_positions.first = cv::Point{eyes[0].x + eyes[0].width / 2,
                                          eyes[0].y + eyes[0].height / 2};

        pupil_positions.second = cv::Point{eyes[1].x + eyes[1].width / 2,
                                          eyes[1].y + eyes[1].height / 2};
    }

    return pupil_positions;
}

auto PupilsDistanceCalculator::calculateDistanceBetweenPupils(
    const std::pair<cv::Point, cv::Point>& pupil_positions) -> double
{
    return std::sqrt(
        std::pow(pupil_positions.first.x - pupil_positions.second.x, 2) + std::pow(
            pupil_positions.second.y - pupil_positions.first.y,
            2));
}