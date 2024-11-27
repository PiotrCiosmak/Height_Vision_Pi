#include "detector/FaceDetector.hpp"
#include "Logger.hpp"

using namespace height_vision_pi;

FaceDetector::FaceDetector(const FaceDetectorConfig& new_face_detector_config) :
    face_detector_config{new_face_detector_config}
{
    face_detector.load(face_detector_config.model_path);
}

auto FaceDetector::detect(const std::vector<cv::Mat>& humans) -> std::vector<cv::Rect>
{
    auto detected_faces = std::vector<cv::Rect>{};
    for (const auto& human : humans)
    {
        auto currently_detected_faces = std::vector<cv::Rect>{};
        face_detector.detectMultiScale(human,
                                       currently_detected_faces,
                                       face_detector_config.scale_factor,
                                       face_detector_config.min_neighbors);

        const auto detected_faces_count = currently_detected_faces.size();
        if (detected_faces_count > 0)
        {
            if (detected_faces_count > 1)
            {
                detected_faces.push_back(findMostProbableFace(detected_faces));
            }
            else
            {
                detected_faces.push_back(currently_detected_faces.front());
            }
        }
        else
        {
            detected_faces.push_back(cv::Rect{});
        }
    }

    const auto detected_faces_count = std::ranges::count_if(detected_faces,
                                                            [](const cv::Rect& rect)
                                                            {
                                                                return rect.area() > 0;
                                                            });

    Logger::info("{} out of {} possible faces detected", detected_faces_count, humans.size());
    return detected_faces;
}

auto FaceDetector::findMostProbableFace(const std::vector<cv::Rect>& faces) -> cv::Rect
{
    auto most_probable_face = faces[0];
    for (const auto& face : faces)
    {
        if (face.width * face.height > most_probable_face.width * most_probable_face.height)
        {
            most_probable_face = face;
        }
    }
    return most_probable_face;
}