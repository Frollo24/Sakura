#include "skrpch.h"
#include "Buffer.h"
#include "RenderContext.h"

#include "RenderingAPI/OpenGL/OpenGLBuffer.h"

namespace Sakura
{
	Ref<Buffer> Buffer::Create(const BufferDescription& desc)
	{
		switch (RenderContext::GetAPI())
		{
			case RenderAPI::None:      SKR_CORE_ASSERT(false, "RenderAPI::None is not supported!"); return nullptr;
			case RenderAPI::OpenGL:    return CreateRef<OpenGLBuffer>(desc);
		}

		SKR_CORE_ASSERT(false, "Unknown render API!"); return nullptr;
	}
}
