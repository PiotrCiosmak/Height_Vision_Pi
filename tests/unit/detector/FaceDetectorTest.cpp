#include "detector/FaceDetector.hpp"

#include <gtest/gtest.h>

using namespace height_vision_pi;

class FaceDetectorTest : public ::testing::Test
{
protected:
    FaceDetector detector{{"../../../models/haarcascade_frontalface_default.xml", 1.3, 5}};
};

TEST_F(FaceDetectorTest, ShouldProcessEmptyFrames)
{
    // given: Empty frames
    auto empty_frame = cv::Mat(2048, 1537, CV_8UC3, cv::Scalar(0, 0, 0));
    // given: Vector of empty frames
    auto empty_frames = std::vector{empty_frame, empty_frame, empty_frame, empty_frame};

    // when: Processing frame
    const auto detected_faces = detector.detect(empty_frames);

    // then: Detected faces size is equal to processed number of empty frames
    EXPECT_TRUE(detected_faces.size() == empty_frames.size());
    // then: Faces aren't detected
    for (const auto& face : detected_faces)
    {
        EXPECT_TRUE(face.area() == 0);
    }
}

TEST_F(FaceDetectorTest, ShouldDetectFacesInSetOfHumansFrames)
{
    // given: Path to directory that contains human frames
    const auto directory_path = std::string{"../../../resources/detected_human"};
    // given: Container to hold those frames
    auto human_frames = std::vector<cv::Mat>{};

    // when: Loading frames to container
    for (const auto& entry : std::filesystem::directory_iterator(directory_path))
    {
        const auto img = cv::imread(entry.path().string());
        if (!img.empty())
        {
            human_frames.push_back(img);
        }
    }
    // when: Processing the vector of human frames to detect faces
    const auto detected_faces = detector.detect(human_frames);
    // when: Count valid detections
    const auto valid_detections = std::ranges::count_if(detected_faces,
                                                        [](const cv::Rect& rect)
                                                        {
                                                            return rect.area() > 0;
                                                        });
    // when: Calculate the detection rate
    const auto detection_rate = static_cast<double>(valid_detections) / human_frames.size();

    // then: Human should be detected in at least 50% of the frames
    ASSERT_GE(detection_rate, 0.50);
}