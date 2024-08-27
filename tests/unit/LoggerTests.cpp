#include "Logger.hpp"

#include <gtest/gtest.h>

using namespace height_vision_pi;

class TestLogger : public ::testing::Test
{
protected:
    std::ostringstream oss_cout;
    std::ostringstream oss_cerr;
    std::streambuf* old_cout;
    std::streambuf* old_cerr;

    void SetUp() override
    {
        old_cout = std::cout.rdbuf(oss_cout.rdbuf());
        old_cerr = std::cerr.rdbuf(oss_cerr.rdbuf());
    }

    void TearDown() override
    {
        std::cout.rdbuf(old_cout);
        std::cerr.rdbuf(old_cerr);
    }
};

TEST_F(TestLogger, ShouldLogInfoMessageWithOneArgument)
{
    height_vision_pi::Logger::info("Hello, {}!", "world");
    ASSERT_EQ(oss_cout.str(), "[INFO] Hello, world!\n");
}

TEST_F(TestLogger, ShouldLogWarnMessageWithOneArgument)
{
    height_vision_pi::Logger::warn("Warning: {} detected", "Issue");
    ASSERT_EQ(oss_cout.str(), "[WARN] Warning: Issue detected\n");
}

TEST_F(TestLogger, ShouldLogErrorMessageWithOneArgument)
{
    ASSERT_DEATH(
        { height_vision_pi::Logger::error("Error: {} occurred", "Critical failure"); }, "");
}

TEST_F(TestLogger, ShouldLogInfoMessageWithoutArguments)
{
    height_vision_pi::Logger::info("Test message");
    ASSERT_EQ(oss_cout.str(), "[INFO] Test message\n");
}

TEST_F(TestLogger, ShouldLogWarnMessageWithoutArguments)
{
    height_vision_pi::Logger::warn("Test warning");
    ASSERT_EQ(oss_cout.str(), "[WARN] Test warning\n");
}

TEST_F(TestLogger, ShouldLogErrorMessageWithoutArguments)
{
    ASSERT_DEATH({ height_vision_pi::Logger::error("Test error"); }, "");
}

TEST_F(TestLogger, ShouldTerminateApplication)
{
    ASSERT_DEATH(
        { height_vision_pi::Logger::error("Fatal error, exiting"); }, "");
}

TEST_F(TestLogger, ShouldLogInfoMessageWithWultipleArguments)
{
    height_vision_pi::Logger::info("{} + {} = {}", 2, 3, 5);
    ASSERT_EQ(oss_cout.str(), "[INFO] 2 + 3 = 5\n");
}

TEST_F(TestLogger, ShouldLogWarnMessageWithWultipleArguments)
{
    height_vision_pi::Logger::warn("{} is greater than {}", 5, 3);
    ASSERT_EQ(oss_cout.str(), "[WARN] 5 is greater than 3\n");
}

TEST_F(TestLogger, ShouldLogErrorMessageWithWultipleArguments)
{
    ASSERT_DEATH(
        {
            height_vision_pi::Logger::error(
                "Fatal: {} occurred at {}", "Segmentation fault", "memory address");
        },
        "");
}