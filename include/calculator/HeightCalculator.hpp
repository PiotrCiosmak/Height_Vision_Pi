#include <map>
#include <vector>

#include <opencv2/opencv.hpp>

class HeightCalculator
{
public:
    double calculate(const std::vector<cv::Mat>& humans, const std::vector<int>& ages,
                     const std::vector<double>& distance_between_pupils);

private:
    [[nodiscard]] auto get_average_pupil_distance(const int& age) const -> double;

    constexpr std::map<int, double> average_pupil_distances = {
        {5, 4.5}, {10, 5.2}, {15, 5.8}, {20, 6.2}, {30, 6.3}, {40, 6.3}, {50, 6.2}, {60, 6.1}
    };
};