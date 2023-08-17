//
// Created by Samer Ali on 8/17/23.
//

#ifndef CYNTHIA_CORE_ASSERT_H
#define CYNTHIA_CORE_ASSERT_H


#include "Includes.h"


#ifdef CY_ENABLE_ASSERTS
	#ifdef CY_ENABLE_ASSERTS_WIN32
		#define CY_ASSERT(x, ...) { if(!(x)) {CY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
		#define CY_CORE_ASSERT(x, ...) { if(!(x)) { CY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#elif CY_ENABLE_ASSERTS_DARWIN
		#define CY_ASSERT(x, ...) { if(!(x)) {CY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __builtin_debugtrap(); } }
		#define CY_CORE_ASSERT(x, ...) { if(!(x)) { CY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __builtin_debugtrap(); } }
	#else
		#define CY_ASSERT(x, ...)
		#define CY_CORE_ASSERT(x, ...)
	#endif // CY_ENABLE_ASSERTS_WIN32
#endif //CY_ENABLE_ASSERTS

#endif //CYNTHIA_CORE_ASSERT_H
