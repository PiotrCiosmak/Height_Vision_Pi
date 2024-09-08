#pragma once

#include <nlohmann/json.hpp>

namespace height_vision_pi
{
    enum DataSourceConfig
    {
        stream,
        file
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(DataSourceConfig,
                                 {{DataSourceConfig::stream, "stream"},
                                  {DataSourceConfig::file, "file"}})
} // namespace height_vision_pi
