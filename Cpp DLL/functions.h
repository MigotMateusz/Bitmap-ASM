#pragma once

#ifdef CppDll_API_EXPORTS
	#define CppDll_API __declspec(dllexport)
#else
	#define CppDll_API __declspec(dllimport)
#endif
#include <string>

extern "C" std::string CppDll_API test();
