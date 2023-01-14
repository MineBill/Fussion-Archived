#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Fussion
{
    Ref<spdlog::logger> Log::s_coreLogger;
    Ref<spdlog::logger> Log::s_clientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%H:%M:%S] [%l] [%!:%#]: %v%$");
        s_coreLogger = spdlog::stdout_color_mt("Core");
        s_clientLogger = spdlog::stdout_color_mt("Client");
    }
} // namespace Fussion
