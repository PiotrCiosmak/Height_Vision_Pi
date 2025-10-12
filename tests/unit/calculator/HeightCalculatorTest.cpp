#include "calculator/HeightCalculator.hpp"

#include <gtest/gtest.h>

using namespace height_vision_pi;

class HeightCalculatorParamTest : public ::testing::TestWithParam<
        std::tuple<
            std::vector<cv::Mat>,
            std::vector<cv::Mat>,
            std::vector<std::optional<int>>,
            std::vector<std::optional<double>>
        >>
{
protected:
    HeightCalculator calculator;
};

INSTANTIATE_TEST_SUITE_P(
    EmptyVectorsCombinations,
    HeightCalculatorParamTest,
    ::testing::Values(
        std::make_tuple(
            std::vector<cv::Mat>{},
            std::vector<cv::Mat>{cv::Mat(10, 10, CV_8UC3)},
            std::vector<std::optional<int>>{3},
            std::vector<std::optional<double>>{5.0}
        ),
        std::make_tuple(
            std::vector<cv::Mat>{cv::Mat(10, 10, CV_8UC3)},
            std::vector<cv::Mat>{},
            std::vector<std::optional<int>>{3},
            std::vector<std::optional<double>>{5.0}
        ),
        std::make_tuple(
            std::vector<cv::Mat>{cv::Mat(10, 10, CV_8UC3)},
            std::vector<cv::Mat>{cv::Mat(10, 10, CV_8UC3)},
            std::vector<std::optional<int>>{},
            std::vector<std::optional<double>>{5.0}
        ),
        std::make_tuple(
            std::vector<cv::Mat>{cv::Mat(10, 10, CV_8UC3)},
            std::vector<cv::Mat>{cv::Mat(10, 10, CV_8UC3)},
            std::vector<std::optional<int>>{3},
            std::vector<std::optional<double>>{}
        ),
        std::make_tuple(
            std::vector<cv::Mat>{},
            std::vector<cv::Mat>{},
            std::vector<std::optional<int>>{3},
            std::vector<std::optional<double>>{5.0}
        ),
        std::make_tuple(
            std::vector<cv::Mat>{},
            std::vector<cv::Mat>{cv::Mat(10, 10, CV_8UC3)},
            std::vector<std::optional<int>>{},
            std::vector<std::optional<double>>{5.0}
        ),
        std::make_tuple(
            std::vector<cv::Mat>{cv::Mat(10, 10, CV_8UC3)},
            std::vector<cv::Mat>{},
            std::vector<std::optional<int>>{3},
            std::vector<std::optional<double>>{}
        ),
        std::make_tuple(
            std::vector<cv::Mat>{cv::Mat(10, 10, CV_8UC3)},
            std::vector<cv::Mat>{},
            std::vector<std::optional<int>>{3},
            std::vector<std::optional<double>>{}
        ),
        std::make_tuple(
            std::vector<cv::Mat>{},
            std::vector<cv::Mat>{},
            std::vector<std::optional<int>>{},
            std::vector<std::optional<double>>{5.0}
        ),
        std::make_tuple(
            std::vector<cv::Mat>{},
            std::vector<cv::Mat>{},
            std::vector<std::optional<int>>{3},
            std::vector<std::optional<double>>{}
        ),
        std::make_tuple(
            std::vector<cv::Mat>{cv::Mat(10, 10, CV_8UC3)},
            std::vector<cv::Mat>{},
            std::vector<std::optional<int>>{},
            std::vector<std::optional<double>>{}
        )
    )
    );

TEST_P(HeightCalculatorParamTest, ShouldThrowErrorOnMismatchedVectors)
{
    // given: Parameters
    const auto& parameters = GetParam();
    // given: Vector of humans
    const auto& humans = std::get<0>(parameters);
    // given: Vector of faces
    const auto& faces = std::get<1>(parameters);
    // given: Vector of ages
    const auto& ages = std::get<2>(parameters);
    // given: Vector of distance between pupils
    const auto& distance_between_pupils = std::get<3>(parameters);

    // then: Verify that the function logs an error and exits with EXIT_FAILURE
    ASSERT_EXIT(
        {const auto height = calculator.calculate(humans, faces, ages,distance_between_pupils);},
        ::testing::ExitedWithCode(EXIT_FAILURE),
        "");
}

class HeightCalculatorTest : public ::testing::Test
{
protected:
    HeightCalculator calculator{};
};

TEST_F(HeightCalculatorTest, ShouldReturnNulloptWhenDataInVectorsAreEmpty)
{
    // given: Vectors of empty frames
    const auto& humans = std::vector<cv::Mat>{};
    const auto& faces = std::vector<cv::Mat>{};
    const auto& ages = std::vector<std::optional<int>>{};
    const auto& distance_between_pupils = std::vector<std::optional<double>>{};

    // when: Calculating height
    const auto height = calculator.calculate(humans, faces, ages, distance_between_pupils);

    // then: Calculated height should be empty
    ASSERT_TRUE(height.empty());
}

TEST_F(HeightCalculatorTest, ShouldCalculateHeightForFakeData)
{
    // given: Vector of fake humans
    const auto humans = {cv::Mat(100, 100, CV_8UC3, cv::Scalar(0, 0, 0))};
    // given: Vector of fake faces
    const auto faces = {cv::Mat(20, 30, CV_8UC3, cv::Scalar(0, 0, 0))};
    // given: Vector of fake ages
    const auto ages = {std::optional{15}};
    // given: Vector of fake distances
    const auto distances = {std::optional{15.0}};

    // when: Calculating height
    const auto heights = calculator.calculate(humans, faces, ages, distances);

    // then: Calculated height should be non-empty and have a value
    ASSERT_EQ(heights.size(), 1);
    ASSERT_TRUE(heights[0].has_value());
}