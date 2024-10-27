#pragma once

#include "Sakura/Core/Base.h"

namespace Sakura
{
	// HACK: Should be in a common file
	struct Color
	{
		float r, g, b, a;

		Color(float value): r(value), g(value), b(value), a(value) {}
		Color(float r, float g, float b): r(r), g(g), b(b), a(1.0f) {}
		Color(float r, float g, float b, float a): r(r), g(g), b(b), a(a) {}
	};

	enum class AttachmentFormat
	{
		None,
		R8,
		RGBA8,
		RGBA16F,
		D24S8,
		D32
	};

	enum class ClearFlags
	{
		None = 0,
		Color = SKR_BIT(0),
		DepthStencil = SKR_BIT(1),
		All = Color | DepthStencil
	};

	SKR_DEFINE_ENUM_FLAG_OPERATORS(ClearFlags);

	struct ClearValues
	{
		Color Color = Sakura::Color(1.0f);
		float Depth = 1.0f;
		uint32_t Stencil = 0;
		ClearFlags ClearFlags = ClearFlags::None;
	};

	constexpr int MAX_COLOR_ATTACHMENTS = 8;
	constexpr int MAX_TOTAL_ATTACHMENTS = MAX_COLOR_ATTACHMENTS + 1;

	struct RenderPassDescription
	{
		std::array<AttachmentFormat, MAX_TOTAL_ATTACHMENTS> Attachments{};
		ClearValues ClearValues{};
		uint32_t Samples = 1;
		bool IsSwapchainTarget = false;
	};

	class RenderPass
	{
	public:
		virtual ~RenderPass() = default;

		inline const RenderPassDescription& GetDescription() const { return m_RenderPassDesc; }

		static Ref<RenderPass> Create(const RenderPassDescription& desc);

	protected:
		RenderPass(const RenderPassDescription& desc) : m_RenderPassDesc(desc) {}
		RenderPassDescription m_RenderPassDesc;
	};
}

