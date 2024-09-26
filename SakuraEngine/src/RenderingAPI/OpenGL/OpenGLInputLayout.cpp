#include "skrpch.h"
#include "OpenGLInputLayout.h"

#include <glad/glad.h>

namespace Sakura
{
	OpenGLInputLayout::OpenGLInputLayout(const std::vector<InputBinding>& bindings)
		: InputLayout(bindings)
	{
		glCreateVertexArrays(1, &m_RendererID);

		GLuint attribIndex = 0;
		GLuint bindingIndex = 0;
		for (const auto& binding : m_Bindings)
		{
			HandleAttributes(binding, bindingIndex, attribIndex);
			bindingIndex++;
		}
	}

	OpenGLInputLayout::~OpenGLInputLayout()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLInputLayout::HandleAttributes(const InputBinding& binding, const uint32_t& bindingIndex, uint32_t& currentAttribIndex) const
	{
		for (const auto& attribute : binding.GetAttributes())
		{
			switch (attribute.Type)
			{
				using enum Sakura::ShaderDataType;
				case None:
				{
					SKR_CORE_ASSERT(false, "ShaderDataType of Attribute must not be None!");
					break;
				}
				case Float:
				case Float2:
				case Float3:
				case Float4:
				{
					glEnableVertexArrayAttrib(m_RendererID, currentAttribIndex);
					glVertexArrayAttribBinding(m_RendererID, currentAttribIndex, bindingIndex);
					glVertexArrayAttribFormat(m_RendererID, currentAttribIndex, attribute.GetComponentCount(),
						GL_FLOAT, attribute.Normalized ? GL_TRUE : GL_FALSE, attribute.Offset);
					currentAttribIndex++;
					break;
				}
				case Bool:
				case Int:
				case Int2:
				case Int3:
				case Int4:
				{
					glEnableVertexArrayAttrib(m_RendererID, currentAttribIndex);
					glVertexArrayAttribBinding(m_RendererID, currentAttribIndex, bindingIndex);
					glVertexArrayAttribIFormat(m_RendererID, currentAttribIndex, attribute.GetComponentCount(),
						GL_INT, attribute.Offset);
					currentAttribIndex++;
					break;
				}
				case Mat3:
				case Mat4:
				{
					uint32_t count = attribute.GetComponentCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexArrayAttrib(m_RendererID, currentAttribIndex);
						glVertexArrayAttribBinding(m_RendererID, currentAttribIndex, bindingIndex);
						glVertexArrayAttribFormat(m_RendererID, currentAttribIndex, count, GL_FLOAT,
							attribute.Normalized ? GL_TRUE : GL_FALSE, attribute.Offset + sizeof(float) * count * i);
						currentAttribIndex++;
					}
					break;
				}
				default:
				{
					SKR_CORE_ASSERT(false, "Unknown Attribute ShaderDataType!");
					break;
				}
			}
		}

		using InputRate = InputBinding::InputRate;
		if (binding.GetInputRate() == InputRate::Instance)
			glVertexArrayBindingDivisor(m_RendererID, bindingIndex, 1);
	}
}