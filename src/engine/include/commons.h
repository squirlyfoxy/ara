#pragma once

#ifdef _WIN32
// If dll is used, then we need to export the symbols or import them
#ifdef DLL_EXPORT
#define ARA_API __declspec(dllexport)
#else
#define ARA_API __declspec(dllimport)
#endif
#else
#define ARA_API
#endif
