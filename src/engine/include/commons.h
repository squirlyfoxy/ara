#pragma once

#ifdef _WIN32
// If dll is used, then we need to export the symbols or import them
#ifdef DLL_EXPORT
#define ARA_API __declspec(dllexport)
#else
#define ARA_API __declspec(dllimport)
#endif

#define ARA_INCLUDE_OS #include <windows.h>

#else
// Linux or MacOS
#define ARA_API

#define ARA_INCLUDE_OS

#endif

// ******************************
// Error codes

#define ARA_GLAD_ERROR_EXIT_CODE -1
#define ARA_GL_SHADER_COMPILATION_ERROR -2
