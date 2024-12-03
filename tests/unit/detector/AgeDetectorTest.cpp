#include "detector/AgeDetector.hpp"

#include <gtest/gtest.h>

using namespace height_vision_pi;

class AgeDetectorTest : public ::testing::Test
{
protected:
    AgeDetector detector{
        {"../../../models/age_net.caffemodel", "../../../models/age_deploy.prototxt", 1.0,
         {227, 227}, {78.4263377603, 87.7689143744, 114.895847746}, true, false}};
};

TEST_F(AgeDetectorTest, ShouldProcessEmptyFrames)
{
    // given: Empty frame
    const auto empty_frame = cv::Mat{};
    // given: Vector of empty frames
    const auto empty_frames = std::vector{empty_frame, empty_frame, empty_frame, empty_frame};

    // when: Processing frames
    const auto detected_ages = detector.detect(empty_frames);

    // then: Detected ages size is equal to processed number of empty frames
    EXPECT_TRUE(detected_ages.size() == empty_frames.size());
    // then: Ages aren't detected
    for (const auto& age : detected_ages)
    {
        EXPECT_TRUE(age == 0);
    }
}

TEST_F(AgeDetectorTest, ShouldDetectAgeInSetOfFacesFrames)
{
    // given: Path to directory that contains face frames
    const auto directory_path = std::string{"../../../resources/detected_face"};
    // given: Container to hold those frames
    auto faces_frames = std::vector<cv::Mat>{};

    // when: Loading frames to container
    for (const auto& entry : std::filesystem::directory_iterator(directory_path))
    {
        const auto img = cv::imread(entry.path().string());
        faces_frames.push_back(img);
    }
    // when: Processing the vector of face frames to detect age
    const auto detected_ages = detector.detect(faces_frames);
    // when: Count valid detections
    const auto valid_detections = std::ranges::count_if(detected_ages,
                                                        [](const auto& age)
                                                        {
                                                            return age != 0;
                                                        });
    // when: Calculate the detection rate
    const auto detection_rate = static_cast<double>(valid_detections) / faces_frames.size();

    // then: Age should be detected at least 83% of the frames
    ASSERT_GE(detection_rate, 0.83);
}