#pragma once

#include "Sakura/Core/Base.h"

namespace Sakura
{
	enum class BufferType
	{
		Vertex, Index
	};

	struct BufferDescription
	{
		BufferType Type;
		uint32_t Size = 0;
		void* Data = nullptr;
	};

	class Buffer
	{
	public:
		virtual ~Buffer() = default;

		inline const BufferDescription& GetDescription() const { return m_BufferDesc; }

		virtual void SetData(uint32_t offset, uint32_t size, const void* data) = 0;

		static Ref<Buffer> Create(const BufferDescription& desc);

	protected:
		Buffer(const BufferDescription& desc) : m_BufferDesc(desc) {}
		BufferDescription m_BufferDesc;
	};
}

