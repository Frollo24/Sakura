#pragma once
#include "Sakura/Render/InputLayout.h"

namespace Sakura
{
	class OpenGLInputLayout : public InputLayout
	{
	public:
		OpenGLInputLayout(const std::vector<InputBinding>& bindings);
		virtual ~OpenGLInputLayout();

		inline uint32_t GetRendererID() const { return m_RendererID; }

	private:
		void HandleAttributes(const InputBinding& binding, const uint32_t& bindingIndex, uint32_t& currentAttribIndex) const;

	private:
		uint32_t m_RendererID;
	};
}

