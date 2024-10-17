#include "skrpch.h"
#include "OpenGLContext.h"

#include "OpenGLInputLayout.h"
#include "OpenGLBuffer.h"
#include "OpenGLPipeline.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>

namespace Sakura
{
	namespace OpenGLStateFunctions
	{
		static GLenum DepthComparisonToGLDepthFunc(DepthComparison comparison)
		{
			switch (comparison)
			{
				using enum Sakura::DepthComparison;
				case None:           return GL_NEVER;
				case Less:           return GL_LESS;
				case Equal:          return GL_EQUAL;
				case LessOrEqual:    return GL_LEQUAL;
				case Greater:        return GL_GREATER;
				case NotEqual:       return GL_NOTEQUAL;
				case GreaterOrEqual: return GL_GEQUAL;
				case Always:         return GL_ALWAYS;
				default:
					return GL_NONE;
			}
		}

		static GLenum BlendFactorToGLBlendFactor(BlendFactor factor)
		{
			switch (factor)
			{
				using enum Sakura::BlendFactor;
				case Zero:                  return GL_ZERO;
				case One:                   return GL_ONE;
				case SrcColor:              return GL_SRC_COLOR;
				case OneMinusSrcColor:      return GL_ONE_MINUS_SRC_COLOR;
				case DstColor:              return GL_DST_COLOR;
				case OneMinusDstColor:      return GL_ONE_MINUS_DST_COLOR;
				case SrcAlpha:              return GL_SRC_ALPHA;
				case OneMinusSrcAlpha:      return GL_ONE_MINUS_SRC_ALPHA;
				case DstAlpha:              return GL_DST_ALPHA;
				case OneMinusDstAlpha:      return GL_ONE_MINUS_DST_ALPHA;
				case ConstantColor:         return GL_CONSTANT_COLOR;
				case OneMinusConstantColor: return GL_ONE_MINUS_CONSTANT_COLOR;
				case ConstantAlpha:         return GL_CONSTANT_ALPHA;
				case OneMinusConstantAlpha: return GL_ONE_MINUS_CONSTANT_ALPHA;
				default:
					return GL_NONE;
			}
		}

		static GLenum OperationToGLBlendEquation(BlendOperation operation)
		{
			switch (operation)
			{
				using enum Sakura::BlendOperation;
				case Add:             return GL_FUNC_ADD;
				case Subtract:        return GL_FUNC_SUBTRACT;
				case ReverseSubtract: return GL_FUNC_REVERSE_SUBTRACT;
				case Minimum:         return GL_MIN;
				case Maximum:         return GL_MAX;
				default:
					return GL_NONE;
			}
		}

		static GLenum PolygonRasterModeToGLPolygonMode(PolygonRasterMode polygonMode)
		{
			switch (polygonMode)
			{
				using enum Sakura::PolygonRasterMode;
				case Fill:  return GL_FILL;
				case Line:  return GL_LINE;
				case Point: return GL_POINT;
				default:
					return GL_NONE;
			}
		}

		static GLenum CullingModeToGLCullFace(CullingMode culling)
		{
			switch (culling)
			{
				using enum Sakura::CullingMode;
				case Front:        return GL_FRONT;
				case Back:         return GL_BACK;
				case FrontAndBack: return GL_FRONT_AND_BACK;
				default:
					return GL_NONE;
			}
		}

		static GLenum FrontFaceModeToGLFrontFace(FrontFaceMode frontFace)
		{
			switch (frontFace)
			{
				using enum Sakura::FrontFaceMode;
				case CounterClockwise: return GL_CCW;
				case Clockwise:        return GL_CW;
				default:
					return GL_NONE;
			}
		}

		static void SetDepthState(const PipelineDepthState& depthState)
		{
			if (!depthState.DepthTest)
			{
				glDisable(GL_DEPTH_TEST);
				return;
			}
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(DepthComparisonToGLDepthFunc(depthState.DepthFunc));
			glDepthRange(depthState.DepthRange.MinDepth, depthState.DepthRange.MaxDepth);
			glDepthMask(depthState.DepthWrite ? GL_TRUE : GL_FALSE);
		}

		static void SetBlendState(const PipelineBlendState& blendState)
		{
			if (!blendState.BlendEnable)
			{
				glDisable(GL_BLEND);
				return;
			}
			glEnable(GL_BLEND);
			glBlendFuncSeparate(
				BlendFactorToGLBlendFactor(blendState.ColorEquation.SrcFactor),
				BlendFactorToGLBlendFactor(blendState.ColorEquation.DstFactor),
				BlendFactorToGLBlendFactor(blendState.AlphaEquation.SrcFactor),
				BlendFactorToGLBlendFactor(blendState.AlphaEquation.DstFactor)
			);
			glBlendEquationSeparate(
				OperationToGLBlendEquation(blendState.ColorEquation.Operation),
				OperationToGLBlendEquation(blendState.AlphaEquation.Operation)
			);
		}

		static void SetPolygonState(const PipelinePolygonState& polygonState)
		{
			bool cullEnable = polygonState.CullMode != CullingMode::None;
			if (!cullEnable)
				glDisable(GL_CULL_FACE);
			else
				glEnable(GL_CULL_FACE);
			glFrontFace(FrontFaceModeToGLFrontFace(polygonState.FrontFace));
			glCullFace(CullingModeToGLCullFace(polygonState.CullMode));
			glPolygonMode(GL_FRONT_AND_BACK, PolygonRasterModeToGLPolygonMode(polygonState.PolygonMode));
		}
	}

	static void OpenGLDebugCallback(GLenum source, GLenum type, unsigned id, GLenum severity, int length, const char* message, const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         SKR_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       SKR_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_LOW:          SKR_CORE_INFO(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: SKR_CORE_TRACE(message); return;
			default:
				SKR_CORE_ASSERT(false, "Unknown severity level!");
				break;
		}
	}

	void OpenGLContext::Init()
	{
#ifdef SKR_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLDebugCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
#endif // SKR_DEBUG

		glEnable(GL_FRAMEBUFFER_SRGB);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

	void OpenGLContext::Shutdown()
	{
		// In OpenGL this does nothing
	}

	void OpenGLContext::BeginFrame()
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLContext::EndFrame()
	{
		// Reset buffer writing to true for any buffer
		glDepthMask(GL_TRUE);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}

	void OpenGLContext::BindPipeline(const Ref<Pipeline>& pipeline)
	{
		using namespace OpenGLStateFunctions;

		const PipelineState& state = pipeline->GetPipelineState();
		glUseProgram(dynamic_cast<OpenGLPipeline*>(pipeline.get())->GetRendererID());
		SetDepthState(state.PipelineDepthState);
		SetBlendState(state.PipelineBlendState);
		SetPolygonState(state.PipelinePolygonState);
	}

	void OpenGLContext::SetInputLayout(const Ref<InputLayout>& layout)
	{
		m_BoundVertexArray = dynamic_cast<OpenGLInputLayout*>(layout.get())->GetRendererID();
		glBindVertexArray(m_BoundVertexArray);
	}

	void OpenGLContext::BindVertexBuffer(const Ref<Buffer>& vertexBuffer, const InputBinding& binding)
	{
		GLintptr offset = 0;
		GLuint vertexBufferID = dynamic_cast<OpenGLBuffer*>(vertexBuffer.get())->GetRendererID();
		glVertexArrayVertexBuffer(m_BoundVertexArray, binding.GetBinding(), vertexBufferID, offset, binding.GetStride());
	}

	void OpenGLContext::BindIndexBuffer(const Ref<Buffer>& indexBuffer)
	{
		GLuint indexBufferID = dynamic_cast<OpenGLBuffer*>(indexBuffer.get())->GetRendererID();
		glVertexArrayElementBuffer(m_BoundVertexArray, indexBufferID);
	}

	void OpenGLContext::BindTexture(const Ref<Texture>& texture, uint32_t binding)
	{
		glBindTextureUnit(binding, dynamic_cast<OpenGLTexture*>(texture.get())->GetRendererID());
	}

	void OpenGLContext::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
	{
		if (instanceCount > 1 && firstInstance == 0)
			glDrawArraysInstanced(GL_TRIANGLES, firstVertex, vertexCount, instanceCount);
		else if (instanceCount > 1)
			glDrawArraysInstancedBaseInstance(GL_TRIANGLES, firstVertex, vertexCount, instanceCount, firstInstance);
		else
			glDrawArrays(GL_TRIANGLES, firstVertex, vertexCount);
	}
}