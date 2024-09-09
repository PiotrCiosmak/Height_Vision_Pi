#include "detector//HumanDetector.hpp"

#include <thread>

using namespace height_vision_pi;

HumanDetector::HumanDetector()
{
    // TODO path to config file
    net = cv::dnn::readNetFromDarknet("../models/yolov4.cfg", "../models/yolov4.weights");
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_OPENCL);
}

auto HumanDetector::detect(cv::Mat& frame) -> cv::Mat&
{
    // TODO poprawić to ale jest potencjał! :)
    auto blob = cv::Mat{};
    cv::dnn::blobFromImage(
        frame, blob, 1.0 / 255.0, cv::Size(256, 256), cv::Scalar(0, 0, 0), true, false);
    net.setInput(blob);
    auto detections = std::vector<cv::Mat>{};
    std::thread detectionThread([&]() {
        net.forward(detections, net.getUnconnectedOutLayersNames());
    });
    detectionThread.join();

    auto indices = std::vector<int>{};
    auto boxes = std::vector<cv::Rect>{};
    auto confidences = std::vector<float>{};

    for (const auto& detection : detections)
    {
        for (int i = 0; i < detection.rows; ++i)
        {
            const auto* data = detection.ptr<float>(i);
            auto confidence = data[4];
            if (confidence > 0.8) // próg pewności
            {
                auto center_x = static_cast<int>(data[0] * frame.cols);
                auto center_y = static_cast<int>(data[1] * frame.rows);
                auto width = static_cast<int>(data[2] * frame.cols);
                auto height = static_cast<int>(data[3] * frame.rows);

                auto left = center_x - width / 2;
                auto top = center_y - height / 2;

                boxes.push_back(cv::Rect(left, top, width, height));
                confidences.push_back(confidence);
            }
        }
    }

    cv::dnn::NMSBoxes(boxes, confidences, 0.5, 0.5, indices);

    for (int idx : indices)
    {
        cv::rectangle(frame, boxes[idx], cv::Scalar(0, 255, 0), 2);
    }

    return frame;
}