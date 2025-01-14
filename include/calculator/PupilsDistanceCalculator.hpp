#pragma once

#include "config/PupilsDistanceCalculatorConfig.hpp"

#include <opencv2/opencv.hpp>

namespace height_vision_pi
{
    class PupilsDistanceCalculator
    {
    public:
        explicit PupilsDistanceCalculator(const PupilsDistanceCalculatorConfig& new_pupils_distance_calculator_config);
        [[nodiscard]] auto calculate(const std::vector<cv::Mat>& detected_faces) -> std::vector<double>;

    private:
        [[nodiscard]] auto detectPupils(const cv::Mat& face) -> std::pair<cv::Point, cv::Point>;
        [[nodiscard]] auto calculateDistanceBetweenPupils(
            const std::pair<cv::Point, cv::Point>& pupil_positions) -> double;

        PupilsDistanceCalculatorConfig pupils_distance_calculator_config;
        cv::CascadeClassifier pupil_detector;
    };
} // namespace height_vision_pi