#pragma once

#include <expected>
#include <string>

namespace height_vision_pi
{
    static auto runBashCommand(std::string_view command) -> std::expected<std::string, std::string>;
}