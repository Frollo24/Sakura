#pragma once

#include <memory>

namespace Sakura
{
	template <typename T>
	using Unique = std::unique_ptr<T>;
	template <typename T, typename... Args>
	constexpr Unique<T> CreateUnique(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Ref = std::shared_ptr<T>;
	template <typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	class RawPointer
	{
	public:
		RawPointer(T* ptr)
			: m_Ptr(ptr)
		{

		}

		~RawPointer()
		{
			m_Ptr = nullptr;
		}

	private:
		T* m_Ptr = nullptr;
	};
}
