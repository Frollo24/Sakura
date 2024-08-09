#pragma once
#include "SakuraEngine.h"
#include "Sakura/Events/Delegates/Delegate.h"
#include <iostream>

extern Sakura::Application* Sakura::CreateApplication(); // To be defined by client


int add(int a, int b) 
{
	return a + b;
}

namespace Sakura
{
	int Main(int argc, char** argv)
	{
		// Test delegates
		Delegate<int, int, int> subject;

		int x = 10;
		int y = 15;

		subject += add;

		int r = subject.Invoke<int, int>(x, y);

		std::cout << r << std::endl;


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
