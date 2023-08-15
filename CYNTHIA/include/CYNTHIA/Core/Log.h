//
// Created by Samer Ali on 8/15/23.
//
#ifndef CYNTHIA_CYNTHIA_SRC_CYNTHIA_CORE_LOG_H
#define CYNTHIA_CYNTHIA_SRC_CYNTHIA_CORE_LOG_H

#include "CYNTHIA/Cynthia.h"
#include "spdlog/spdlog.h"
#include <memory>

namespace Cynthia
{

	class Log
	{
	public:
	  static void Init();

	  inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	  inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
	  static std::shared_ptr<spdlog::logger> s_CoreLogger;
	  static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

} // Cynthia

#define CY_CORE_ERROR( ... )        ::Cynthia::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CY_CORE_INFO( ... )         ::Cynthia::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CY_CORE_WARN( ... )         ::Cynthia::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CY_CORE_CRITICAL( ... )     ::Cynthia::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define CY_CORE_TRACE( ... )        ::Cynthia::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CY_CORE_DEBUG( ... )        ::Cynthia::Log::GetCoreLogger()->debug(__VA_ARGS__)



#define CY_ERROR( ... )             ::Cynthia::Log::GetClientLogger()->error(__VA_ARGS__)
#define CY_INFO( ... )              ::Cynthia::Log::GetClientLogger()->info(__VA_ARGS__)
#define CY_WARN( ... )              ::Cynthia::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CY_CRITICAL( ... )          ::Cynthia::Log::GetClientLogger()->critical(__VA_ARGS__)
#define CY_TRACE( ... )             ::Cynthia::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CY_DEBUG( ... )             ::Cynthia::Log::GetClientLogger()->debug(__VA_ARGS__)

#endif //CYNTHIA_CYNTHIA_SRC_CYNTHIA_CORE_LOG_H
