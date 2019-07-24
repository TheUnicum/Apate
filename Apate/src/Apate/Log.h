#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Apate {

	class APATE_API Log
	{
	public:
		static void Init(spdlog::level::level_enum level=spdlog::level::trace);

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		inline static void SetCoreLoggerLevel(spdlog::level::level_enum level) { s_CoreLogger->set_level(level); }
		inline static void SetClientLoggerLevel(spdlog::level::level_enum level) { s_ClientLogger->set_level(level); }
		inline static void SetLoggerLevel(spdlog::level::level_enum level) { s_CoreLogger->set_level(level); s_ClientLogger->set_level(level); }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

/*
#define SPDLOG_LEVEL_TRACE 0
#define SPDLOG_LEVEL_DEBUG 1
#define SPDLOG_LEVEL_INFO 2
#define SPDLOG_LEVEL_WARN 3
#define SPDLOG_LEVEL_ERROR 4
#define SPDLOG_LEVEL_CRITICAL 5
#define SPDLOG_LEVEL_OFF 6
*/

#ifndef AP_DIST
	#define AP_CORE_TRACE(...)    ::Apate::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define AP_CORE_DEBUG(...)    ::Apate::Log::GetCoreLogger()->debug(__VA_ARGS__)
	#define AP_CORE_INFO(...)     ::Apate::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define AP_CORE_WARN(...)     ::Apate::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define AP_CORE_ERROR(...)    ::Apate::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define AP_CORE_CRITICAL(...) ::Apate::Log::GetCoreLogger()->critical(__VA_ARGS__)

	#define AP_TRACE(...)         ::Apate::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define AP_DEBUG(...)         ::Apate::Log::GetClientLogger()->debug(__VA_ARGS__)
	#define AP_INFO(...)          ::Apate::Log::GetClientLogger()->info(__VA_ARGS__)
	#define AP_WARN(...)          ::Apate::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define AP_ERROR(...)         ::Apate::Log::GetClientLogger()->error(__VA_ARGS__)
	#define AP_CRITICAL(...)      ::Apate::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
	#define AP_CORE_TRACE(...)
	#define AP_CORE_DEBUG(...)
	#define AP_CORE_INFO(...)
	#define AP_CORE_WARN(...)
	#define AP_CORE_ERROR(...)
	#define AP_CORE_CRITICAL(...)

	#define AP_TRACE(...)
	#define AP_DEBUG(...)
	#define AP_INFO(...)
	#define AP_WARN(...)
	#define AP_ERROR(...)
	#define AP_CRITICAL(...)
#endif // !AP_DEBUG