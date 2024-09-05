#pragma once

#include "Sakura/Core/Base.h"

namespace Sakura
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginFrame();
		static void EndFrame();
	};
}

