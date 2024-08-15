#include "skrpch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Sakura
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init(LogLevel logLevel)
	{
		using level_enum = spdlog::level::level_enum;

		spdlog::set_pattern("%^[%T] %-6n [%-8l]: %v%$");
		spdlog::level::level_enum spdlog_level = (level_enum)logLevel;

		s_CoreLogger = spdlog::stdout_color_mt("SAKURA");
		s_CoreLogger->set_level(spdlog_level);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog_level);
	}

	void Log::SetLogLevel(LogLevel logLevel)
	{
		using level_enum = spdlog::level::level_enum;
		spdlog::level::level_enum spdlog_level = (level_enum)logLevel;

		s_CoreLogger->set_level(spdlog_level);
		s_ClientLogger->set_level(spdlog_level);
	}
}
