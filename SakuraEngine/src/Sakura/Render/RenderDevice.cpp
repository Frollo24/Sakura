#include "skrpch.h"
#include "RenderDevice.h"
#include "RenderContext.h"

#include "RenderingAPI/OpenGL/OpenGLDevice.h"

namespace Sakura
{
	Ref<RenderDevice> RenderDevice::Create(const RawPointer<RenderInstance>& instance)
	{
		switch (RenderContext::GetAPI())
		{
			case RenderAPI::None:      SKR_CORE_ASSERT(false, "RenderAPI::None is not supported!"); return nullptr;
			case RenderAPI::OpenGL:    return CreateRef<OpenGLDevice>(instance);
		}

		SKR_CORE_ASSERT(false, "Unknown render API!"); return nullptr;
	}

	Ref<Buffer> RenderDevice::CreateBuffer(const BufferDescription& bufferDescription) const
	{
		return Buffer::Create(bufferDescription);
	}

	void RenderDevice::DestroyBuffer(Ref<Buffer>& buffer) const
	{
		buffer = nullptr;
	}
}