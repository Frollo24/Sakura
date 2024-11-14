#pragma once

#include "Sakura/Core/Base.h"

#include "Sakura/Render/Texture.h"

namespace Sakura
{
	class RenderDevice;
	class RenderContext;

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static const Ref<RenderDevice>& GetDevice();
		static const Ref<RenderContext>& GetContext();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginFrame();
		static void EndFrame();

		static void SetScreenTexture(const Ref<Texture>& screenTexture);
		static void DrawToScreen();
	};
}

