#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Sakura
{
	class Event;

	enum class LogLevel
	{
		Trace,
		Info,
		Debug,
		Warn,
		Error,
		Critical,
		Off
	};

	class Log
	{
	public:
		static void Init(LogLevel logLevel = LogLevel::Trace);
		static void SetLogLevel(LogLevel logLevel);

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}
template <> struct fmt::formatter<Sakura::Event> : fmt::ostream_formatter {};  // Necessary since fmt::v10

// --- CORE LOG MACROS ---
#define SKR_CORE_TRACE(...)     ::Sakura::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SKR_CORE_DEBUG(...)     ::Sakura::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define SKR_CORE_INFO(...)      ::Sakura::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SKR_CORE_WARN(...)      ::Sakura::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SKR_CORE_ERROR(...)     ::Sakura::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SKR_CORE_CRITICAL(...)  ::Sakura::Log::GetCoreLogger()->critical(__VA_ARGS__)

// --- CLIENT LOG MACROS ---
#define SKR_CLIENT_TRACE(...)     ::Sakura::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SKR_CLIENT_DEBUG(...)     ::Sakura::Log::GetClientLogger()->debug(__VA_ARGS__)
#define SKR_CLIENT_INFO(...)      ::Sakura::Log::GetClientLogger()->info(__VA_ARGS__)
#define SKR_CLIENT_WARN(...)      ::Sakura::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SKR_CLIENT_ERROR(...)     ::Sakura::Log::GetClientLogger()->error(__VA_ARGS__)
#define SKR_CLIENT_CRITICAL(...)  ::Sakura::Log::GetClientLogger()->critical(__VA_ARGS__)
