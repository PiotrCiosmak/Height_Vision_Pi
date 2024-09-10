#include "config/Config.hpp"
#include "Logger.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

using namespace height_vision_pi;

std::once_flag Config::init_flag;

auto Config::get() -> Config&
{
    static Config config;
    // TODO path to config file
    std::call_once(init_flag, [] { config.load("../config/config.json"); });
    return config;
}

void Config::load(const std::string& file_path)
{
    auto file = std::ifstream{file_path};
    if (!file.is_open())
    {
        Logger::error("Could not open config file: {}", file_path);
    }

    auto data = nlohmann::json::parse(file);

    camera = data["camera"].get<CameraConfig>();
    data_source = data["data_source"].get<DataSourceConfig>();
    window = data["window"].get<WindowConfig>();
    monitor = data["monitor"].get<MonitorConfig>();
}