#pragma once

#include "Sakura/Core/Base.h"

namespace Sakura
{
	enum class ShaderDataType {
		None = 0,
		Bool, Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Mat3, Mat4
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Bool:     return 1;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			default:
				SKR_CORE_ASSERT(false, "Unknown ShaderDataType!");
				return 0;
		}
	}

	struct InputAttribute
	{
		std::string Name;
		ShaderDataType Type = ShaderDataType::None;
		uint32_t Size = 0;
		uint32_t Offset = 0;
		bool Normalized = false;

		InputAttribute() = default;
		InputAttribute(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3; // 3 * float3
				case ShaderDataType::Mat4:    return 4; // 4 * float4
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
				default:
					return 0;
			}
		}
	};

	class InputBinding
	{
	public:
		enum class InputRate { Vertex, Instance };

		InputBinding(const std::initializer_list<InputAttribute>& attributes) : m_Attributes(attributes) { CalculateStrideAndOffset(); }
		InputBinding(const std::vector<InputAttribute>& attributes) : m_Attributes(attributes) { CalculateStrideAndOffset(); }

		inline const std::vector<InputAttribute>& GetAttributes() const { return m_Attributes; }
		inline InputRate GetInputRate() const { return m_InputRate; }
		inline uint32_t GetBinding() const { return m_Binding; }
		inline uint32_t GetStride() const { return m_Stride; }

		inline void SetInputRate(const InputRate& inputRate) { m_InputRate = inputRate; }

	private:
		void CalculateStrideAndOffset();
		friend class InputLayout;

	protected:
		std::vector<InputAttribute> m_Attributes;
		InputRate m_InputRate = InputRate::Vertex;
		uint32_t m_Binding = 0;
		uint32_t m_Stride = 0;
	};

	class InputLayout
	{
	public:
		virtual ~InputLayout() = default;

		inline const std::vector<InputBinding>& GetBindings() const { return m_Bindings; }

		static Ref<InputLayout> Create(const std::vector<InputBinding>& bindings);

	protected:
		InputLayout(const std::vector<InputBinding>& bindings) : m_Bindings(bindings)
		{
			int i = 0;
			for (InputBinding& binding : m_Bindings)
			{
				binding.m_Binding = i;
				i++;
			}
		}

	protected:
		std::vector<InputBinding> m_Bindings;
	};
}

