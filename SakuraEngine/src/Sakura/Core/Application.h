#pragma once

namespace Sakura
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined by client
	Application* CreateApplication();
}