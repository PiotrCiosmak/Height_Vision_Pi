#include "detector//HumanDetector.hpp"

using namespace height_vision_pi;

HumanDetector::HumanDetector(const HumanDetectorConfig& new_human_detector_config) :
    human_detector_config{new_human_detector_config}
{
    net = cv::dnn::readNetFromDarknet(human_detector_config.model_config_path,
                                      human_detector_config.model_weights_path);
}

auto HumanDetector::detect(cv::Mat& frame) -> cv::Mat&
{
    auto blob = cv::Mat{};
    cv::dnn::blobFromImage(
        frame,
        blob,
        1.0 / 255.0,
        cv::Size(human_detector_config.resolution.x, human_detector_config.resolution.y),
        cv::Scalar(0, 0, 0),
        true,
        false);
    net.setInput(blob);
    auto detections = std::vector<cv::Mat>{};
    net.forward(detections, net.getUnconnectedOutLayersNames());

    auto indexes = std::vector<int>{};
    auto boxes = std::vector<cv::Rect>{};
    auto confidences = std::vector<float>{};

    for (const auto& detection : detections)
    {
        for (int i = 0; i < detection.rows; ++i)
        {
            const auto* data = detection.ptr<float>(i);
            const auto confidence = data[4];
            if (confidence > human_detector_config.confidence_threshold)
            {
                auto center_x = static_cast<int>(data[0] * frame.cols);
                auto center_y = static_cast<int>(data[1] * frame.rows);
                auto width = static_cast<int>(data[2] * frame.cols);
                auto height = static_cast<int>(data[3] * frame.rows);

                auto left = center_x - width / 2;
                auto top = center_y - height / 2;

                boxes.emplace_back(left, top, width, height);
                confidences.push_back(confidence);
            }
        }
    }

    cv::dnn::NMSBoxes(boxes,
                      confidences,
                      human_detector_config.nms_score_threshold,
                      human_detector_config.nms_threshold,
                      indexes);

    for (const auto& index : indexes)
    {
        cv::rectangle(frame, boxes[index], cv::Scalar(0, 255, 0), 2);
    }

    return frame;
}