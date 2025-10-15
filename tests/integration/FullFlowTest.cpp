#include "Injector.hpp"

#include <gtest/gtest.h>

using namespace height_vision_pi;

class FullFlowTest : public ::testing::Test
{
protected:
    std::unique_ptr<CameraController> camera_controller;
    std::unique_ptr<HumanDetector> human_detector;
    std::unique_ptr<FaceDetector> face_detector;
    std::unique_ptr<AgeDetector> age_detector;
    std::unique_ptr<PupilsDistanceCalculator> pupils_distance_calculator;
    std::unique_ptr<HeightCalculator> height_calculator;

    void SetUp() override
    {
        camera_controller = cameraControllerInjector().create<std::unique_ptr<CameraController>>();
        human_detector = humanDetectorInjector().create<std::unique_ptr<HumanDetector>>();
        face_detector = faceDetectorInjector().create<std::unique_ptr<FaceDetector>>();
        age_detector = ageDetectorInjector().create<std::unique_ptr<AgeDetector>>();
        pupils_distance_calculator = pupilsDistanceCalculatorInjector().create<std::unique_ptr<
            PupilsDistanceCalculator>>();
        height_calculator = heightCalculatorInjector().create<std::unique_ptr<HeightCalculator>>();
    }
};

TEST_F(FullFlowTest, FullFlowTest)
{
    // given: Path to a frame that has human
    const auto frame_path = std::string{PROJECT_SOURCE_DIR} + "/resources/detected_human/0035.jpg";

    // when: Loading frame
     auto frame = cv::imread(frame_path);

    // then: Frame isn't empty
    ASSERT_FALSE(frame.empty());

    // when: Detecting humans
    const auto& detected_humans = human_detector->detect(frame);

    // then: One human should be detected
    ASSERT_TRUE(detected_humans.size() == 1);

    // when: Detecting faces
    const auto& detected_faces = face_detector->detect(detected_humans);

    // then: One face should be detected
    ASSERT_TRUE(detected_faces.size() == 1);

    // when: Detecting ages
    const auto& detected_ages = age_detector->detect(detected_faces);

    // then: Ages should be detected
    ASSERT_TRUE(detected_ages.size() == 1);

    // when: Calculating pupils
    const auto& pupils_distances = pupils_distance_calculator->calculate(detected_faces);

    // then: Pupils distance should be calculated
    ASSERT_TRUE(pupils_distances.size() == 1);

    // when: Calculating height
    const auto& heights = height_calculator->calculate(detected_humans,
                                                       detected_faces,
                                                       detected_ages,
                                                       pupils_distances);

    // then: Height should be calculated correctly
    ASSERT_TRUE(heights.size() == 1);
}