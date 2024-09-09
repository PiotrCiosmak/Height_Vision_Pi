#include "detector//HumanDetector.hpp"

using namespace height_vision_pi;

HumanDetector::HumanDetector()
{
    // TODO path to config file
    net = cv::dnn::readNetFromDarknet("../models/yolov4.cfg", "../models/yolov4.weights");
}

auto HumanDetector::detect(cv::Mat& frame) -> cv::Mat&
{
    auto outputLayerNames = net.getUnconnectedOutLayersNames();
    auto blob = cv::Mat{};
    cv::dnn::blobFromImage(
        frame, blob, 1.0 / 255.0, cv::Size(96, 96), cv::Scalar(0, 0, 0), true, false); // Zmiana rozmiaru obrazu na 96x96
    net.setInput(blob);

    auto detections = std::vector<cv::Mat>{};
    net.forward(detections, outputLayerNames); // Użycie wstępnie zapisanych nazw warstw wyjściowych

    auto indices = std::vector<int>{};
    auto boxes = std::vector<cv::Rect>{};
    auto confidences = std::vector<float>{};

#pragma omp parallel for // Równoległe przetwarzanie detekcji
    for (const auto& detection : detections)
    {
        for (int i = 0; i < detection.rows; ++i)
        {
            const auto* data = detection.ptr<float>(i);
            auto confidence = data[4];
            if (confidence > 0.9) // próg pewności
            {
                auto center_x = static_cast<int>(data[0] * frame.cols);
                auto center_y = static_cast<int>(data[1] * frame.rows);
                auto width = static_cast<int>(data[2] * frame.cols);
                auto height = static_cast<int>(data[3] * frame.rows);

                auto left = center_x - width / 2;
                auto top = center_y - height / 2;

#pragma omp critical // Synchronizacja dla dostępu do wektorów
                {
                    boxes.push_back(cv::Rect(left, top, width, height));
                    confidences.push_back(confidence);
                }
            }
        }
    }

    cv::dnn::NMSBoxes(boxes, confidences, 0.9, 0.4, indices); // Optymalizacja NMS

    for (int idx : indices)
    {
        cv::rectangle(frame, boxes[idx], cv::Scalar(0, 255, 0), 2);
    }

    return frame;
}