#pragma once
#include "Fussion/Log.h"

#if defined(_MSC_VER)
    #define BUILTIN_TRAP_FUNCTION __debugbreak
#elif defined(__clang__) || defined(__GNUC__)
    #define BUILTIN_TRAP_FUNCTION __builtin_trap
#endif

#ifdef FSN_USE_ASSERTIONS
    #define FSN_ASSERT(expr, ...)                                 \
        {                                                         \
            if (!(expr)) {                                        \
                FSN_CLIENT_ERR("Assertion hit: {}", __VA_ARGS__); \
                BUILTIN_TRAP_FUNCTION();                          \
            }                                                     \
        }
    #define FSN_CORE_ASSERT(expr, ...)                          \
        {                                                       \
            if (!(expr)) {                                      \
                FSN_CORE_ERR("Assertion hit: {}", __VA_ARGS__); \
                BUILTIN_TRAP_FUNCTION();                        \
            }                                                   \
        }
#else
    #define FSN_ASSERT(expr, ...)
    #define FSN_CORE_ASSERT(expr, ...)
#endif
