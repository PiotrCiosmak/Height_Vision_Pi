#include "detector/HumanDetector.hpp"

#include <gtest/gtest.h>

using namespace height_vision_pi;

class HumanDetectorTest : public ::testing::Test
{
protected:
    HumanDetector detector{
        {"../../../models/yolov4.cfg", "../../../models/yolov4.weights", {128, 96}, 0.6, 0.6, 0.1}};
};

TEST_F(HumanDetectorTest, ShouldProcessEmptyFrame)
{
    // given: Empty frame
    auto empty_frame = cv::Mat(2048, 1537, CV_8UC3, cv::Scalar(0, 0, 0));

    // when: Processing frame
    const auto& result_frame = detector.detect(empty_frame);

    // then: Empty frame proceed find
    EXPECT_EQ(empty_frame.rows, result_frame.rows);
    EXPECT_EQ(empty_frame.cols, result_frame.cols);
}

TEST_F(HumanDetectorTest, ShouldDetectPersonIn90PercentOfVideoFrames)
{
    // given: Load video with person
    auto video = cv::VideoCapture{"../../../resources/camera_video.mp4"};

    // then: Video should be opened
    ASSERT_TRUE(video.isOpened());

    // given: Placeholder for currently processed frame
    auto test_frame = cv::Mat{};
    // given: Counter to keep track of the total number of frames
    auto frame_count = 0;
    // given: Counter to keep track of the frames where person is detected
    auto detected_frame_count = 0;

    // when: Processing each frame of the video
    while (video.read(test_frame))
    {
        // when: Increment the frame count for each processed frame
        ++frame_count;

        // then: Frame isn't empty
        ASSERT_FALSE(test_frame.empty());

        // when: Detecting person in the current frame
        const auto& result_frame = detector.detect(test_frame);

        // given: Variable to track if a rectangle is detected in the current frame
        auto rectangle_detected = false;

        // when: Checking if a rectangle is present in the frame by looking for color changes
        const auto rectangle_color = cv::Scalar(0, 255, 0);
        for (int y = 0; y < result_frame.rows; ++y)
        {
            for (int x = 0; x < result_frame.cols; ++x)
            {
                const auto pixel = result_frame.at<cv::Vec3b>(x, y);
                if (pixel[0] == rectangle_color[0] && pixel[1] == rectangle_color[1]
                    && pixel[2] == rectangle_color[2])
                {
                    rectangle_detected = true;
                    break;
                }
            }

            if (rectangle_detected)
            {
                ++detected_frame_count;
                break;
            }
        }
    }

    // when: Calculate the detection rate
    const auto detection_rate = static_cast<double>(detected_frame_count) / frame_count;

    // then: On at least 90% of frames person should be detected
    ASSERT_GE(detection_rate, 0.90);

    // when: Cleaning up resources by releasing the video
    video.release();
}