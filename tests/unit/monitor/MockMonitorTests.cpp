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

TEST_F(MockMonitorTest, ShouldCallCheckCPUTemperatureOnce)
{
    // when: Setting up the mock to be called exactly once
    EXPECT_CALL(mock_monitor, checkCPUTemperature()).Times(1);

    // when: Calling checkCPUTemperature on the monitor once
    mock_monitor.checkCPUTemperature();

    // then: checkCPUTemperature was called exactly once
}

TEST_F(MockMonitorTest, ShouldNotCallCheckCPUTemperature)
{
    // when: Setting up the mock to not be called
    EXPECT_CALL(mock_monitor, checkCPUTemperature()).Times(0);

    // when: Do not calling checkCPUTemperature

    // then: checkCPUTemperature was not called
}

TEST_F(MockMonitorTest, ShouldCallCheckCPUTemperatureAtLeastOnce)
{
    // when: Setting up the mock to be called at least once
    EXPECT_CALL(mock_monitor, checkCPUTemperature()).Times(AtLeast(1));

    // when: Calling checkCPUTemperature on the monitor twice
    mock_monitor.checkCPUTemperature();
    mock_monitor.checkCPUTemperature();

    // then: checkCPUTemperature was called at least once
}