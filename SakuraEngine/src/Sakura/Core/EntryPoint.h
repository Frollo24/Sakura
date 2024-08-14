#pragma once
#include "SakuraEngine.h"

extern Sakura::Application* Sakura::CreateApplication(); // To be defined by client

namespace Sakura
{
	int Main(int argc, char** argv)
	{
		Log::Init();
		SKR_CORE_DEBUG("{}", 42);
		SKR_CORE_WARN("{}", 42);
		SKR_CORE_CRITICAL("{}", 42);
		SKR_CORE_ERROR("{}", 42);
		SKR_CORE_TRACE("{}", 42);
		SKR_CLIENT_INFO("{}", 42);

		auto app = Sakura::CreateApplication();
		app->Run();
		delete app;

		return 0;
	}
}

int main(int argc, char** argv)
{
	return Sakura::Main(argc, argv);
}
