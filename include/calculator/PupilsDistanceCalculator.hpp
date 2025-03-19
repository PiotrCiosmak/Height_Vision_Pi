#pragma once

#include <opencv2/opencv.hpp>

namespace height_vision_pi
{
    class PupilsDistanceCalculator
    {
    public:
        explicit PupilsDistanceCalculator() = default;
        [[nodiscard]] auto calculate(const std::vector<cv::Mat>& detected_faces) -> std::vector<double>;

    private:
        [[nodiscard]] auto preprocessFace(const cv::Mat& face) -> cv::Mat;
        [[nodiscard]] auto getEyeRect(const cv::Mat& face_roi, double ratio_x, double ratio_y, int eye_width,
                                      int eye_height) -> cv::Rect;
        [[nodiscard]] auto findEyeCenterInROI(const cv::Mat& eye_ror) -> cv::Point;
        [[nodiscard]] auto computeMatXGradient(const cv::Mat& src) -> cv::Mat;
        [[nodiscard]] auto adjustPupilPosition(const cv::Point& pupil_position, const cv::Rect& eye_rect) -> cv::Point;
        [[nodiscard]] auto calculateDistanceBetweenPupils(const cv::Point& right_pupil_position,
                                                          const cv::Point& left_pupil_position) -> double;
    };
} // namespace height_vision_pi