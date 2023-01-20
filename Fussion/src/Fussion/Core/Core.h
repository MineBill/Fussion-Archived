#pragma once
#include "Fussion/Core/Log.h"

#if defined(_MSC_VER)
    #define BUILTIN_TRAP_FUNCTION __debugbreak
#elif defined(__clang__) || defined(__GNUC__)
    #define BUILTIN_TRAP_FUNCTION __builtin_trap
#endif

#ifdef FSN_USE_ASSERTIONS
    #define FSN_ASSERT(expr, ...)                                                                    \
        {                                                                                            \
            if (!(expr)) {                                                                           \
                FSN_ERR("ASSERTION HIT: ");                                                   \
                if constexpr (std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value != 0) { \
                    FSN_ERR("    " __VA_ARGS__);                                              \
                } else {                                                                             \
                    FSN_ERR("   No additional information provided");                         \
                }                                                                                    \
                BUILTIN_TRAP_FUNCTION();                                                             \
            }                                                                                        \
        }
    #define FSN_CORE_ASSERT(expr, ...)                                                               \
        {                                                                                            \
            if (!(expr)) {                                                                           \
                FSN_CORE_ERR("ASSERTION HIT: ");                                                     \
                if constexpr (std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value != 0) { \
                    FSN_CORE_ERR("    " __VA_ARGS__);                                                \
                } else {                                                                             \
                    FSN_CORE_ERR("   No additional information provided");                           \
                }                                                                                    \
                BUILTIN_TRAP_FUNCTION();                                                             \
            }                                                                                        \
        }
#else
    #define FSN_ASSERT(expr, ...)
    #define FSN_CORE_ASSERT(expr, ...)
#endif
