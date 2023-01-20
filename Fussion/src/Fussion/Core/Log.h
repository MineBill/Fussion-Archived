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

        static inline Ref<spdlog::logger> &GetCoreLogger()
        {
            return s_coreLogger;
        }
        static inline Ref<spdlog::logger> &GetClientLogger()
        {
            return s_clientLogger;
        }
    };

} // namespace Fussion

#define FSN_CORE_DEBUG(...) SPDLOG_LOGGER_DEBUG(::Fussion::Log::GetCoreLogger(), __VA_ARGS__)
#define FSN_CORE_TRACE(...) SPDLOG_LOGGER_TRACE(::Fussion::Log::GetCoreLogger(), __VA_ARGS__)
#define FSN_CORE_LOG(...) SPDLOG_LOGGER_INFO(::Fussion::Log::GetCoreLogger(), __VA_ARGS__)
#define FSN_CORE_WARN(...) SPDLOG_LOGGER_WARN(::Fussion::Log::GetCoreLogger(), __VA_ARGS__)
#define FSN_CORE_ERR(...) SPDLOG_LOGGER_ERROR(::Fussion::Log::GetCoreLogger(), __VA_ARGS__)

#define FSN_DEBUG(...) SPDLOG_LOGGER_DEBUG(::Fussion::Log::GetClientLogger(), __VA_ARGS__)
#define FSN_TRACE(...) SPDLOG_LOGGER_TRACE(::Fussion::Log::GetClientLogger(), __VA_ARGS__)
#define FSN_LOG(...) SPDLOG_LOGGER_INFO(::Fussion::Log::GetClientLogger(), __VA_ARGS__)
#define FSN_WARN(...) SPDLOG_LOGGER_WARN(::Fussion::Log::GetClientLogger(), __VA_ARGS__)
#define FSN_ERR(...) SPDLOG_LOGGER_ERROR(::Fussion::Log::GetClientLogger(), __VA_ARGS__)
