#include "config/Config.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

using namespace height_vision_pi;

auto Config::get() -> Config&
{
    static Config config;
    return config;
}

void Config::load(const std::string& file_path)
{
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open config file: " << file_path << std::endl;
        exit(1);
    }

    nlohmann::json json_data;
    file >> json_data;

    camera.resolution.x = json_data["camera"]["resolution"]["x"];
    camera.resolution.y = json_data["camera"]["resolution"]["y"];
    camera.fps = json_data["camera"]["fps"];
    camera.capture_mode = json_data["camera"]["capture_mode"];
    camera.brightness = json_data["camera"]["brightness"];
    camera.contrast = json_data["camera"]["contrast"];
    camera.saturation = json_data["camera"]["saturation"];
    camera.gain = json_data["camera"]["gain"];
    camera.hue = json_data["camera"]["hue"];
    camera.auto_focus = json_data["camera"]["auto_focus"];
    camera.auto_exposure = json_data["camera"]["auto_exposure"];

    window.name = json_data["window"]["name"];
    window.resolution.x = json_data["window"]["resolution"]["x"];
    window.resolution.y = json_data["window"]["resolution"]["y"];

    data_source = json_data["data_source"];
}
