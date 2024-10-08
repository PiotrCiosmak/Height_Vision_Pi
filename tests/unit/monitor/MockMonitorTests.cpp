#include "mock/monitor/MockMonitor.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace height_vision_pi;

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::StrictMock;

class MockMonitorTest : public ::testing::Test
{
protected:
    StrictMock<MockMonitor> mock_monitor;
};

TEST_F(MockMonitorTest, ShouldCallCheckOnce)
{
    // when: Setting up the mock to be called exactly once
    EXPECT_CALL(mock_monitor, check()).Times(1);

    // when: Calling check on the monitor once
    mock_monitor.check();

    // then: Function check was called exactly once
}

TEST_F(MockMonitorTest, ShouldNotCallCheck)
{
    // when: Setting up the mock to not be called
    EXPECT_CALL(mock_monitor, check()).Times(0);

    // when: Do not calling check

    // then: Function check was not called
}

TEST_F(MockMonitorTest, ShouldCallCheckAtLeastOnce)
{
    // when: Setting up the mock to be called at least once
    EXPECT_CALL(mock_monitor, check()).Times(AtLeast(1));

    // when: Calling check on the monitor twice
    mock_monitor.check();
    mock_monitor.check();

    // then: Function check was called at least once
}