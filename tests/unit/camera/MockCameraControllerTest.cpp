#include "mock/camera/MockCameraController.hpp"
#include "config/Config.hpp"

#include <gtest/gtest.h>

using namespace height_vision_pi;

using ::testing::Return;

TEST(MockCameraControllerTest, ShouldGetFrame)
{
    // given: Camera config
    const auto camera_config = Config::get().camera;
    // given: Mocked camera controller
    const auto camera_controller = std::make_unique<MockCameraController>();
    // given: Camera resolution
    const auto camera_resolution = camera_config.resolution;

    // when: Preparing the expected frame
    const auto expected_frame = cv::Mat::zeros(camera_resolution.x, camera_resolution.y, CV_8UC3);
    // when: Setting up the mock to return the expected frame
    EXPECT_CALL(*camera_controller, getFrame()).WillOnce(Return(expected_frame));
    // when: Calling getFrame on the camera controller
    const auto actual_frame = camera_controller->getFrame();

    // then: The returned frame size should match the expected frame size
    EXPECT_EQ(expected_frame.size(), actual_frame.size());
    // then: The returned frame type should match the expected frame type
    EXPECT_EQ(expected_frame.type(), actual_frame.type());
}
