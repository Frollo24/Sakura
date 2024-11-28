#pragma once

#include "Sakura/Core/Base.h"
#include "Sakura/Render/RenderPass.h"
#include "Sakura/Render/Texture.h"

namespace Sakura
{
	struct FramebufferDescription
	{
		std::array<Ref<Texture>, MAX_TOTAL_ATTACHMENTS> RenderTargets = { nullptr };
		Ref<RenderPass> RenderPass = nullptr;
		uint32_t Width = 0;
		uint32_t Height = 0;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		inline const FramebufferDescription& GetDescription() const { return m_FramebufferDesc; }

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		static Ref<Framebuffer> Create(const FramebufferDescription& desc);

	protected:
		Framebuffer(const FramebufferDescription& desc) : m_FramebufferDesc(desc) {}
		FramebufferDescription m_FramebufferDesc;
	};
}

