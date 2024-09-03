#pragma once

#include "Sakura/Core/Base.h"
#include "Sakura/Core/Log.h"

#ifdef SKR_DEBUG
#define SKR_ENABLE_ASSERTS
#define SKR_DEBUGBREAK() __debugbreak()
#else
#define SKR_DEBUGBREAK()
#endif // SKR_DEBUG

#ifdef SKR_ENABLE_ASSERTS
#define SKR_CLIENT_VERIFY(x)    ::Sakura::Assertions::Verify<::Sakura::AssertionCaller::ClientAssertion>((x), __FILE__, __LINE__)
#define SKR_CORE_VERIFY(x)      ::Sakura::Assertions::Verify<::Sakura::AssertionCaller::CoreAssertion>((x), __FILE__, __LINE__)
#define SKR_ASSERT(x, ...)      ::Sakura::Assertions::Assert<::Sakura::AssertionCaller::ClientAssertion>((x), __VA_ARGS__)
#define SKR_CORE_ASSERT(x, ...) ::Sakura::Assertions::Assert<::Sakura::AssertionCaller::CoreAssertion>((x), __VA_ARGS__)
#else
#define SKR_VERIFY(x)
#define SKR_CORE_VERIFY(x)
#define SKR_ASSERT(x, ...)
#define SKR_CORE_ASSERT(x, ...)
#endif

namespace Sakura
{
	enum class AssertionCaller
	{
		CoreAssertion,
		ClientAssertion
	};

	class Assertions
	{
	public:
		template<AssertionCaller caller>
		static void Verify(bool condition, const char* file, int32_t line)
		{
			if (!condition)
			{
				switch (caller)
				{
				case AssertionCaller::CoreAssertion:
					SKR_CORE_ERROR("Verification Failed at File: {0}; Line: {1}", file, line);
					break;
				case AssertionCaller::ClientAssertion:
					SKR_CLIENT_ERROR("Verification Failed at File: {0}; Line: {1}", file, line);
					break;
				}
				SKR_DEBUGBREAK();
			}
		}

		template<AssertionCaller caller, typename... Args>
		static void Assert(bool condition, Args&&... args)
		{
			if (!condition)
			{
				switch (caller)
				{
				case AssertionCaller::CoreAssertion:
					SKR_CORE_ERROR("Assertion Failed: {0}", std::forward<Args>(args)...);
					break;
				case AssertionCaller::ClientAssertion:
					SKR_CLIENT_ERROR("Assertion Failed: {0}", std::forward<Args>(args)...);
					break;
				}
				SKR_DEBUGBREAK();
			}
		}
	};
}