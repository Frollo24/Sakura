#pragma once

#include "Sakura/Core/Base.h"

namespace Sakura
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginFrame();
		static void EndFrame();

		// TODO: temp
		static void DrawTriangle();
	};
}

