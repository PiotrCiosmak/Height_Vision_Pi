/*
#include "detector/FaceDetector.hpp"

FaceDetector::FaceDetector(const FaceDetectorConfig& new_face_detector_config) :
    face_detector_config{new_face_detector_config}, face_classifier{face_detector_config.classifier_path}
{
}

auto FaceDetector::detectFace(const cv::Mat& frame) -> std::vector<cv::Rect>
{
    std::vector<cv::Rect> faces;
    cv::Mat gray_frame;
    cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
    face_classifier.detectMultiScale(gray_frame, faces, face_detector_config.scale_factor,
                                     face_detector_config.min_neighbors, face_detector_config.flags,
                                     cv::Size(face_detector_config.min_width, face_detector_config.min_height));
    return faces;
}
*/
