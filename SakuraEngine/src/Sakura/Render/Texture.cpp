#include "skrpch.h"
#include "Texture.h"
#include "RenderContext.h"

#include "RenderingAPI/OpenGL/OpenGLTexture.h"

namespace Sakura
{
	Ref<Texture> Texture::Create(const TextureDescription& desc)
	{
		switch (RenderContext::GetAPI())
		{
			case RenderAPI::None:      SKR_CORE_ASSERT(false, "RenderAPI::None is not supported!"); return nullptr;
			case RenderAPI::OpenGL:    return CreateRef<OpenGLTexture>(desc);
		}

		SKR_CORE_ASSERT(false, "Unknown render API!"); return nullptr;
	}
}