#include "calculator/HeightCalculator.hpp"

double calculate(const std::vector<cv::Mat>& humans,
                 const std::vector<int>& ages,
                 const std::vector<double>& distance_between_pupils)
{
    auto heights = std::vector<double>{};

    for (int i = 0; i < humans.size(); i++)
    {
        const auto average_pupil_distance_cm = get_average_pupil_distance(ages[i]);
        const auto height_px = humans[i].rows;
        const auto height = height_px * (average_pupil_distance_cm / distance_between_pupils[i]);
        heights.push_back(height);
    }
    return
}

auto HeightCalculator::get_average_pupil_distance(const int& age) const -> double
{
    const auto iterator = average_pupil_distances.lower_bound(age);
    if (iterator == average_pupil_distances.end())
    {
        return average_pupil_distances.rbegin()->second;
    }
    return iterator->second;
}