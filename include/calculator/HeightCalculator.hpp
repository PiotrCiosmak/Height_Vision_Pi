#pragma once

#include <optional>

#include <opencv2/opencv.hpp>

namespace height_vision_pi
{
    class HeightCalculator
    {
    public:
        explicit HeightCalculator() = default;
        [[nodiscard]] auto calculate(const std::vector<cv::Mat>& humans,
                                     const std::vector<cv::Mat>& faces,
                                     const std::vector<std::optional<int>>& ages,
                                     const std::vector<std::optional<double>>&
                                     distance_between_pupils) const
            -> std::vector<std::optional<double>>;

    private:
        [[nodiscard]] auto getRealPupilDistanceForAge(double age) const -> double;
    };
} // namespace height_vision_pi