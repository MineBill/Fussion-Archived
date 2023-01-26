#pragma once
#include "Fussion/Core/Types.h"
#include <spdlog/spdlog.h>

namespace Fussion
{

    class Log final
    {
        static Ref<spdlog::logger> s_coreLogger;
        static Ref<spdlog::logger> s_clientLogger;

    public:
        static void Init();

        static inline Ref<spdlog::logger> &core_logger()
        {
            return s_coreLogger;
        }
        static inline Ref<spdlog::logger> &client_logger()
        {
            return s_clientLogger;
        }
    };

} // namespace Fussion

#define FSN_CORE_DEBUG(...) SPDLOG_LOGGER_DEBUG(::Fussion::Log::core_logger(), __VA_ARGS__)
#define FSN_CORE_TRACE(...) SPDLOG_LOGGER_TRACE(::Fussion::Log::core_logger(), __VA_ARGS__)
#define FSN_CORE_LOG(...) SPDLOG_LOGGER_INFO(::Fussion::Log::core_logger(), __VA_ARGS__)
#define FSN_CORE_WARN(...) SPDLOG_LOGGER_WARN(::Fussion::Log::core_logger(), __VA_ARGS__)
#define FSN_CORE_ERR(...) SPDLOG_LOGGER_ERROR(::Fussion::Log::core_logger(), __VA_ARGS__)

#define FSN_DEBUG(...) SPDLOG_LOGGER_DEBUG(::Fussion::Log::client_logger(), __VA_ARGS__)
#define FSN_TRACE(...) SPDLOG_LOGGER_TRACE(::Fussion::Log::client_logger(), __VA_ARGS__)
#define FSN_LOG(...) SPDLOG_LOGGER_INFO(::Fussion::Log::client_logger(), __VA_ARGS__)
#define FSN_WARN(...) SPDLOG_LOGGER_WARN(::Fussion::Log::client_logger(), __VA_ARGS__)
#define FSN_ERR(...) SPDLOG_LOGGER_ERROR(::Fussion::Log::client_logger(), __VA_ARGS__)
