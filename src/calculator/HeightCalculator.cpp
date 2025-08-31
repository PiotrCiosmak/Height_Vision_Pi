#include "calculator/HeightCalculator.hpp"

#include "Logger.hpp"

using namespace height_vision_pi;

auto HeightCalculator::calculate(
    const std::vector<cv::Mat>& humans,
    const std::vector<cv::Mat>& faces,
    const std::vector<std::optional<int>>& ages,
    const std::vector<std::optional<double>>& distance_between_pupils) const
    -> std::vector<std::optional<double>>
{
    const auto size = humans.size();

    if (faces.size() != size || ages.size() != size || distance_between_pupils.size() != size)
    {
        Logger::error(
            "Data mismatch detected: the number of detected humans, faces, age estimates, "
            "and pupil distances must be the same.\n"
            "Details — humans: {}, faces: {}, ages: {}, pupil distances: {}.",
            size,
            faces.size(),
            ages.size(),
            distance_between_pupils.size());
    }

    std::vector<std::optional<double>> heights;

    for (auto i = 0; i < size; ++i)
    {
        const auto& human = humans[i];
        const auto& face = faces[i];
        const auto& age = ages[i];
        const auto& distance_between_pupil = distance_between_pupils[i];

        if (human.empty() || face.empty() || !age.has_value() || !distance_between_pupil.
            has_value())
        {
            heights.emplace_back(std::nullopt);
            continue;
        }

        const auto face_to_human_ratio = static_cast<double>(face.rows) / human.rows;

        const auto scaled_distance_between_pupils =
            distance_between_pupil.value() * face_to_human_ratio;

        const auto real_pupils_distance_cm = getRealPupilDistanceForAge(age.value());

        const auto cm_per_px = real_pupils_distance_cm / scaled_distance_between_pupils;

        const auto height = human.rows * cm_per_px;

        heights.emplace_back(height);
    }

    return heights;
}

auto HeightCalculator::getRealPupilDistanceForAge(const double age) const -> double
{
    static const std::vector<std::pair<double, double>> age_to_distance = {
        {5, 5.9},
        {8, 6.3},
        {12, 6.5},
        {15, 6.7},
        {18, 6.8},
        {25, 6.9}
    };

    if (age <= age_to_distance.front().first)
    {
        return age_to_distance.front().second;
    }

    if (age >= age_to_distance.back().first)
    {
        return age_to_distance.back().second;
    }

    for (auto i = 1; i < age_to_distance.size(); ++i)
    {
        if (age < age_to_distance[i].first)
        {
            const auto age_low = age_to_distance[i - 1].first;
            const auto distance_low = age_to_distance[i - 1].second;
            const auto age_high = age_to_distance[i].first;
            const auto distance_high = age_to_distance[i].second;

            const auto ratio = (age - age_low) / (age_high - age_low);
            return distance_low + ratio * (distance_high - distance_low);
        }
    }

    return age_to_distance.back().second;
}