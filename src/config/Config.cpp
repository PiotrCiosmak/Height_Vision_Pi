#include "config/Config.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

using namespace height_vision_pi;

std::once_flag Config::init_flag;

auto Config::get() -> Config&
{
    static Config config;
    std::call_once(init_flag, []()
    {
        config.load("../config/config.json");
    });
    return config;
}

void Config::load(const std::string& file_path)
{
    auto file = std::ifstream{file_path};
    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open config file: " << file_path << std::endl;
        exit(1);
    }

    auto data = nlohmann::json::parse(file);

    camera = data["camera"].get<CameraConfig>();
    data_source = data["data_source"].get<DataSourceConfig>();
    window = data["window"].get<WindowConfig>();
}
