#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Apate {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init(spdlog::level::level_enum level)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("APATE");
		s_CoreLogger->set_level(level);

		s_ClientLogger = spdlog::stdout_color_mt("APP++");
		s_ClientLogger->set_level(level);
	}

}
