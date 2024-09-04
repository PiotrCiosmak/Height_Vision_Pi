#include "monitor/utils/BashCommand.hpp"
#include "Logger.hpp"

#include <array>
#include <memory>

auto height_vision_pi::runBashCommand(std::string_view command)
    -> std::expected<std::string, std::string>
{
    using namespace std::string_literals;
    auto command_buffor = std::array<char, 128>{};
    using RailFile = std::unique_ptr<FILE, decltype([](FILE* f) { std::ignore = pclose(f); })>;
    auto result = std::string{};
    const RailFile pipe{popen(command.data(), "r")};
    if (!pipe)
    {
        Logger::error("Couldn't run bash command");
    }
    while (fgets(command_buffor.data(), command_buffor.size(), pipe.get()) != nullptr)
    {
        result += command_buffor.data();
    }
    return result;
}