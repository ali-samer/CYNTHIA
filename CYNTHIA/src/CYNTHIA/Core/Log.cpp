//
// Created by Samer Ali on 8/15/23.
//

#include "CYNTHIA/Core/Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Cynthia
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init ( )
	{
		//! refer to https://github.com/gabime/spdlog/wiki/3.-Custom-formatting for pattern formatting
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("CYNTHIA");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APPLICATION");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

} // Cynthia