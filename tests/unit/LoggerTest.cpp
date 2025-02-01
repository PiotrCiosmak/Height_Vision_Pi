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
    // given: An info message with one argument
    const auto message = std::string{"Hello, {}!"};
    const auto argument = std::string{"world"};

    // when: Logging the info message
    Logger::info(message, argument);

    // when: Saving output to variable
    const auto output = oss_cout.str();

    // then: The output should match the expected format
    ASSERT_TRUE(output.find("[INFO]") != std::string::npos);
    ASSERT_TRUE(output.find("Hello, world!") != std::string::npos);
}

TEST_F(TestLogger, ShouldLogWarnMessageWithOneArgument)
{
    // given: A warning message with one argument
    const auto message = std::string{"Warning: {} detected"};
    const auto argument = std::string{"Issue"};

    // when: Logging the warning message
    Logger::warn(message, argument);

    // when: Saving output to variable
    const auto output = oss_cout.str();

    // then: The output should match the expected format
    ASSERT_TRUE(output.find("[WARN]") != std::string::npos);
    ASSERT_TRUE(output.find("Warning: Issue detected") != std::string::npos);
}

TEST_F(TestLogger, ShouldLogErrorMessageWithOneArgument)
{
    // given: An error message with one argument
    const auto message = std::string{"Error: {} occurred"};
    const auto argument = std::string{"Critical failure"};

    // when: Logging the error message (which should terminate the application)
    ASSERT_DEATH({ Logger::error(message, argument); }, "");

    // then: The application should terminate
}

TEST_F(TestLogger, ShouldLogInfoMessageWithoutArguments)
{
    // given: An info message without arguments
    const auto message = std::string{"Test message"};

    // when: Logging the info message
    Logger::info(message);

    // when: Saving output to variable
    const auto output = oss_cout.str();

    // then: The output should match the expected format
    ASSERT_TRUE(output.find("[INFO]") != std::string::npos);
    ASSERT_TRUE(output.find("Test message") != std::string::npos);
}

TEST_F(TestLogger, ShouldLogWarnMessageWithoutArguments)
{
    // given: A warning message without arguments
    const auto message = std::string{"Test warning"};

    // when: Logging the warning message
    Logger::warn(message);

    // when: Saving output to variable
    const auto output = oss_cout.str();

    // then: The output should match the expected format
    ASSERT_TRUE(output.find("[WARN]") != std::string::npos);
    ASSERT_TRUE(output.find("Test warning") != std::string::npos);
}

TEST_F(TestLogger, ShouldLogErrorMessageWithoutArguments)
{
    // given: An error message without arguments
    const auto message = std::string{"Test error"};

    // when: Logging the error message (which should terminate the application)
    ASSERT_DEATH({ Logger::error(message); }, "");

    // then: The application should terminate
}

TEST_F(TestLogger, ShouldTerminateApplication)
{
    // given: A fatal error message
    const auto message = std::string{"Fatal error, exiting"};

    // when: Logging the fatal error message (which should terminate the application)
    ASSERT_DEATH({ Logger::error(message); }, "");

    // then: The application should terminate
}

TEST_F(TestLogger, ShouldLogInfoMessageWithWultipleArguments)
{
    // given: An info message with multiple arguments and result
    const auto message = std::string{"{} + {} = {}"};
    constexpr auto arguments = std::array{2, 3};
    constexpr auto result = 5;

    // when: Logging the info message with multiple arguments
    Logger::info(message, arguments[0], arguments[1], result);

    // when: Saving output to variable
    const auto output = oss_cout.str();

    // then: The output should match the expected format
    ASSERT_TRUE(output.find("[INFO]") != std::string::npos);
    ASSERT_TRUE(output.find("2 + 3 = 5") != std::string::npos);
}

TEST_F(TestLogger, ShouldLogWarnMessageWithWultipleArguments)
{
    // given: A warning message with multiple arguments
    const auto message = std::string{"{} is greater than {}"};
    constexpr auto arguments = std::array{5, 3};

    // when: Logging the warning message with multiple arguments
    Logger::warn(message, arguments[0], arguments[1]);

    // when: Saving output to variable
    const auto output = oss_cout.str();

    // then: The output should match the expected format
    ASSERT_TRUE(output.find("[WARN]") != std::string::npos);
    ASSERT_TRUE(output.find("5 is greater than 3") != std::string::npos);
}

TEST_F(TestLogger, ShouldLogErrorMessageWithWultipleArguments)
{
    // given: An error message with multiple arguments
    const auto message = std::string{"Fatal: {} occurred at {}"};
    constexpr auto arguments = std::array{"Segmentation fault", "memory address"};

    // when: Logging the error message with multiple arguments
    ASSERT_DEATH({ Logger::error(message, arguments[0], arguments[1]); }, "");

    // then: The application should terminate
}