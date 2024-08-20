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

    camera.resolution.x = data["camera"]["resolution"]["x"].get<int>();
    camera.resolution.y = data["camera"]["resolution"]["y"].get<int>();
    camera.fps = data["camera"]["fps"].get<double>();
    camera.capture_mode = data["camera"]["capture_mode"].get<bool>();
    camera.brightness = data["camera"]["brightness"].get<double>();
    camera.contrast = data["camera"]["contrast"].get<double>();
    camera.saturation = data["camera"]["saturation"].get<double>();
    camera.gain = data["camera"]["gain"].get<double>();
    camera.hue = data["camera"]["hue"].get<double>();
    camera.auto_focus = data["camera"]["auto_focus"].get<bool>();
    camera.auto_exposure = data["camera"]["auto_exposure"].get<bool>();

    data_source = data["data_source"].get<DataSourceConfig>();

    window.name = data["window"]["name"].get<std::string>();
    window.resolution.x = data["window"]["resolution"]["x"].get<int>();
    window.resolution.y = data["window"]["resolution"]["y"].get<int>();
}
