#pragma once
#include "SakuraEngine.h"

extern Sakura::Application* Sakura::CreateApplication(); // To be defined by client

namespace Sakura
{
	int Main(int argc, char** argv)
	{
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
