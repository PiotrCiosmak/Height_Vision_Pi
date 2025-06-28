#include "calculator/PupilsDistanceCalculator.hpp"
#include "config/Config.hpp"

#include <gtest/gtest.h>

using namespace height_vision_pi;

class PupilsDistanceCalculatorTest : public ::testing::Test
{
protected:
    PupilsDistanceCalculator calculator{};
};

TEST_F(PupilsDistanceCalculatorTest, ShouldProcessEmptyFrames)
{
    // given: Empty frame
    const auto empty_frame = cv::Mat{};
    // given: Vector of empty frames
    const auto empty_frames = std::vector{empty_frame, empty_frame, empty_frame, empty_frame};

    // when: Processing frames
    const auto calculated_pupils_distances = calculator.calculate(empty_frames);

    // then: Calculated pupils distances size is equal to the processed number of empty frames
    EXPECT_TRUE(calculated_pupils_distances.size() == empty_frames.size());
    // then: Pupils distances don't have a value
    for (const auto& calculated_pupils_distance : calculated_pupils_distances)
    {
        EXPECT_FALSE(calculated_pupils_distance.has_value());
    }
}

TEST_F(PupilsDistanceCalculatorTest, ShouldCalculateDistanceInSetOfFacesFrames)
{
    // given: Path to a directory that contains face frames
    const auto directory_path = std::string{
        std::string{PROJECT_SOURCE_DIR} + "/resources/detected_face"};
    // given: Container to hold those frames
    auto faces_frames = std::vector<cv::Mat>{};

    // when: Loading frames to container
    for (const auto& entry : std::filesystem::directory_iterator(directory_path))
    {
        const auto img = cv::imread(entry.path().string());
        faces_frames.push_back(img);
    }
    // when: Processing the vector of face frames to calculate pupil distances
    const auto calculated_pupils_distance = calculator.calculate(faces_frames);
    // when: Count valid calculations
    const auto valid_calculated_pupils_distances = std::ranges::count_if(calculated_pupils_distance,
        [](const auto& distance)
        {
            return distance.has_value();
        });
    // when: Calculate the ratio
    const auto ratio = static_cast<double>(valid_calculated_pupils_distances) / faces_frames.size();

    // then: Pupils distance should be calculated correctly in at least 83% of the frames
    ASSERT_GE(ratio, 0.83);
}