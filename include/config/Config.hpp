#pragma once

#include "config/CameraConfig.hpp"
#include "config/DataSourceConfig.hpp"
#include "config/WindowConfig.hpp"

#include <string>

namespace height_vision_pi
{
    class Config
    {
    public:
        [[nodiscard]] static auto get() -> Config&;
        void load(const std::string& file_path);

        CameraConfig camera;
        DataSourceConfig data_source;
        WindowConfig window;

    private:
        Config() = default;
    };
}
