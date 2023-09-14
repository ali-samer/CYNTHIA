//
// Created by Samer Ali on 8/15/23.
//

#ifndef CYNTHIA_CORE_INCLUDES_H
#define CYNTHIA_CORE_INCLUDES_H


#include <memory>
#include <string>
#include <functional>
#include <utility>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string_view>


#ifdef CY_ENABLE_USEFUL_MACROS
	#define CY_SHIFT( X ) (1 << X)

	#define CY_EXPAND_MACRO(X) X
	#define CY_STRINGIFY_MACRO(X) #X
	#define CY_CONCAT_MACRO(X, Y) X##Y
#endif // CY_ENABLE_USEFUL_MACROS


#define CY_BIND_EVENT_FN(X) std::bind(&X, this, std::placeholders::_1)
#endif //CYNTHIA_CORE_INCLUDES_H
