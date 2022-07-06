#pragma once

#ifdef _WIN32
// If dll is used, then we need to export the symbols or import them
#ifdef DLL_EXPORT
#define ARA_API __declspec(dllexport)
#else
#define ARA_API __declspec(dllimport)
#endif

#define ARA_INCLUDE_OS \ #include <windows.h>

#elif defined __APPLE__
#define ARA_API

#define ARA_INCLUDE_OS \ #include <TargetConditionals.h>

// If emscripten is used, then we need to export the symbols or import them
#elif EMSCRIPTEN
#include "emscripten/emscripten.h"

#define ARA_API
#define ARA_API_EXPORT EMSCRIPTEN_KEEPALIVE
#define ARA_WEB
#define ARA_INCLUDE_OS

#else
// Linux or MacOS
#define ARA_API

#define ARA_INCLUDE_OS

#endif

// ******************************
// Error codes

#define ARA_GLAD_ERROR_EXIT_CODE -1
#define ARA_GL_SHADER_COMPILATION_ERROR -2

// ******************************
// Macros

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
