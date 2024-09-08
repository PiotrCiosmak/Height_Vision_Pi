#include "detector//HumanDetector.hpp"

using namespace height_vision_pi;

HumanDetector::HumanDetector()
{
    //TODO path to config file
    net = cv::dnn::readNetFromDarknet("../models/yolov4.cfg", "../models/yolov4.weights");
}

auto HumanDetector::detect(cv::Mat& frame) -> cv::Mat&
{
    cv::Mat blob;
    cv::dnn::blobFromImage(frame, blob, 1.0 / 255.0, cv::Size(416, 416), cv::Scalar(0, 0, 0), true, false);
    net.setInput(blob);  // Ensure that `net` is not const
    std::vector<cv::Mat> outs;
    net.forward(outs, net.getUnconnectedOutLayersNames());

    for (const auto& out : outs)
    {
        for (int i = 0; i < out.rows; ++i)
        {
            const auto* data = out.ptr<float>(i);
            float confidence = data[4];
            if (confidence > 0.5)
            {
                int centerX = static_cast<int>(data[0] * frame.cols);
                int centerY = static_cast<int>(data[1] * frame.rows);
                int width = static_cast<int>(data[2] * frame.cols);
                int height = static_cast<int>(data[3] * frame.rows);

                cv::Rect bbox(centerX - width / 2, centerY - height / 2, width, height);
                cv::rectangle(frame, bbox, cv::Scalar(0, 255, 0), 2);
            }
        }
    }

    return frame;
}