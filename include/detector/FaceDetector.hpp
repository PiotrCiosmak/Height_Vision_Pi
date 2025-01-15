#pragma once

#include "config/FaceDetectorConfig.hpp"

#include <opencv2/opencv.hpp>

namespace height_vision_pi
{
    class FaceDetector
    {
    public:
        explicit FaceDetector(const FaceDetectorConfig& new_face_detector_config);

        [[nodiscard]] auto detect(const std::vector<cv::Mat>& humans) -> std::vector<cv::Mat>;

    private:
        [[nodiscard]] auto findMostProbableFace(const std::vector<cv::Rect>& faces) -> cv::Rect;

        cv::CascadeClassifier face_detector;
        FaceDetectorConfig face_detector_config;
    };
} // namespace height_vision_pi