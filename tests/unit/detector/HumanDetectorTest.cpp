#include "detector/HumanDetector.hpp"
#include "config/Config.hpp"

#include <gtest/gtest.h>

using namespace height_vision_pi;

class HumanDetectorTest : public ::testing::Test
{
protected:
    HumanDetector detector{Config::get().human_detector};
};

TEST_F(HumanDetectorTest, ShouldProcessBlackFrame)
{
    // given: Black frame
    auto black_frame = cv::Mat{2048, 1537, CV_8UC3, cv::Scalar{0, 0, 0}};

    // when: Processing frame
    const auto detected_humans = detector.detect(black_frame);

    // then: Humans aren't detected
    EXPECT_TRUE(detected_humans.empty());
}

TEST_F(HumanDetectorTest, ShouldDetectHumanInVideoFrames)
{
    // given: Load video with moving human
    auto video = cv::VideoCapture{std::string{PROJECT_SOURCE_DIR} + "/resources/camera_video.mp4"};

    // then: Video should be opened
    ASSERT_TRUE(video.isOpened());

    // given: Placeholder for currently processed frame
    auto test_frame = cv::Mat{};
    // given: Counter to keep track of the total number of frames
    auto frame_count = 0;
    // given: Counter to keep track of the frames where human is detected
    auto detected_frame_count = 0;

    // when: Processing each frame of the video
    while (video.read(test_frame))
    {
        // when: Increment the frame count for each processed frame
        ++frame_count;

        // then: Frame isn't empty
        ASSERT_FALSE(test_frame.empty());

        // when: Detecting humans in the current frame
        const auto& detected_humans = detector.detect(test_frame);

        // when: Counting frames on which human was detected
        if (!detected_humans.empty())
        {
            ++detected_frame_count;
        }
    }

    // when: Calculate the detection rate
    const auto detection_rate = static_cast<double>(detected_frame_count) / frame_count;

    // then: Human should be detected in at least 27% of the frames
    ASSERT_GE(detection_rate, 0.27);

    // when: Cleaning up resources by releasing the video
    video.release();
}