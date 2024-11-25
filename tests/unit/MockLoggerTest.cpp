#include "mock/MockLogger.hpp"

#include <gtest/gtest.h>

using namespace height_vision_pi;

class MockLoggerTest : public ::testing::Test
{
protected:
    void SetUp() override { MockLogger::clearLogs(); }
};

TEST_F(MockLoggerTest, ShouldLogInfoMessage)
{
    // given: A fresh instance of MockLogger

    // when: Logging an info message
    MockLogger::info("This is an info message.");

    // then: The log should contain the info message
    const auto& logs = MockLogger::getLogs();
    ASSERT_EQ(logs.size(), 1);
    EXPECT_EQ(logs[0], "[INFO] This is an info message.");
    // then: No error should have occurred
    EXPECT_FALSE(MockLogger::hasErrorOccurred());
}

TEST_F(MockLoggerTest, ShouldLogWarnMessage)
{
    // given: A fresh instance of MockLogger

    // when: Logging a warning message
    MockLogger::warn("This is a warning message.");

    // then: The log should contain the warning message
    const auto& logs = MockLogger::getLogs();
    ASSERT_EQ(logs.size(), 1);
    EXPECT_EQ(logs[0], "[WARN] This is a warning message.");
    // then: No error should have occurred
    EXPECT_FALSE(MockLogger::hasErrorOccurred());
}

TEST_F(MockLoggerTest, ShouldLogErrorMessage)
{
    // given: A fresh instance of MockLogger

    // when: Logging an error message
    MockLogger::error("This is an error message.");

    // then: The log should contain the error message
    const auto& logs = MockLogger::getLogs();
    ASSERT_EQ(logs.size(), 1);
    EXPECT_EQ(logs[0], "[ERROR] This is an error message.");
    // then: An error should have occurred
    EXPECT_TRUE(MockLogger::hasErrorOccurred());
}

TEST_F(MockLoggerTest, ShouldLogMultipleMessagesInOrder)
{
    // given: A fresh instance of MockLogger

    // when: Logging multiple messages of different levels
    MockLogger::info("Info message 1");
    MockLogger::warn("Warning message 1");
    MockLogger::error("Error message 1");
    MockLogger::info("Info message 2");

    // then: The logs should contain all messages in the correct order
    const auto& logs = MockLogger::getLogs();
    ASSERT_EQ(logs.size(), 4);
    EXPECT_EQ(logs[0], "[INFO] Info message 1");
    EXPECT_EQ(logs[1], "[WARN] Warning message 1");
    EXPECT_EQ(logs[2], "[ERROR] Error message 1");
    EXPECT_EQ(logs[3], "[INFO] Info message 2");
    // then: An error should have occurred
    EXPECT_TRUE(MockLogger::hasErrorOccurred());
}

TEST_F(MockLoggerTest, ShouldFormatMessageWithArguments)
{
    // given: A fresh instance of MockLogger

    // when: Logging a formatted message with placeholders
    MockLogger::info("Formatted message: {}, {}", "value1", 123);

    // then: The log should contain the formatted message with arguments replaced
    const auto& logs = MockLogger::getLogs();
    ASSERT_EQ(logs.size(), 1);
    EXPECT_EQ(logs[0], "[INFO] Formatted message: value1, 123");
    // then: No error should have occurred
    EXPECT_FALSE(MockLogger::hasErrorOccurred());
}

TEST_F(MockLoggerTest, ShouldClearAllLogs)
{
    // given: A fresh instance of MockLogger with some logs
    MockLogger::info("This is an info message.");
    MockLogger::error("This is an error message.");

    // when: Clearing all logs
    MockLogger::clearLogs();

    // then: Logs should be empty
    const auto& logs = MockLogger::getLogs();
    EXPECT_TRUE(logs.empty());
    // then: No error should have occurred
    EXPECT_FALSE(MockLogger::hasErrorOccurred());
}
