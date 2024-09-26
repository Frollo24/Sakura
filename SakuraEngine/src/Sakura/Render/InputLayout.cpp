#include "skrpch.h"
#include "InputLayout.h"
#include "RenderContext.h"

#include "RenderingAPI/OpenGL/OpenGLInputLayout.h"

namespace Sakura
{
	void InputBinding::CalculateStrideAndOffset()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Attributes) {
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

	Ref<InputLayout> InputLayout::Create(const std::vector<InputBinding>& bindings)
	{
		switch (RenderContext::GetAPI())
		{
			case RenderAPI::None:      SKR_CORE_ASSERT(false, "RenderAPI::None is not supported!"); return nullptr;
			case RenderAPI::OpenGL:    return CreateRef<OpenGLInputLayout>(bindings);
		}

		SKR_CORE_ASSERT(false, "Unknown render API!"); return nullptr;
	}
	
}