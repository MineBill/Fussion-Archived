#pragma once
#include "Fussion/Log.h"

#ifdef FSN_USE_ASSERTIONS
#define FSN_ASSERT(expr, ...) { if(!(expr)) { FSN_CLIENT_ERR("Assertion hit: {}", __VA_ARGS__); __debugbreak(); }}
#define FSN_CORE_ASSERT(expr, ...) { if(!(expr)) { FSN_CORE_ERR("Assertion hit: {}", __VA_ARGS__); __debugbreak(); }}
#else
#define FSN_ASSERT(expr, ...)
#define FSN_CORE_ASSERT(expr, ...)
#endif
