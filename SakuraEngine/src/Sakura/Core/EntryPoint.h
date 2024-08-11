#pragma once
#include "SakuraEngine.h"
#include <iostream>
#include "Sakura/Events/Delegates/DelegatesTest.h"

extern Sakura::Application* Sakura::CreateApplication(); // To be defined by client

namespace Sakura
{
	int Main(int argc, char** argv)
	{
		// Test delegates
		DelegateTest();

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
