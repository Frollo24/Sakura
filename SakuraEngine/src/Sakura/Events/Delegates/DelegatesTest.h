#pragma once

#include "Sakura/Events/Delegates/Delegate.h"

namespace Sakura
{

	int add(int a, int b)
	{
		std::cout << "Se me ha llamado, soy una funcion de add" << std::endl;
		return a + b;
	}

	char addChar(char a, char b)
	{
		std::cout << "Se me ha llamado, soy una funcion de addChar" << std::endl;
		return a + b;
	}

	void DelegateTest()
	{
		Delegate<void(int, int)> subject;

		int x = 10;
		int y = 12;

		subject += add;
		subject += addChar;
		subject += add;

		subject -= add;
		subject -= add;
		subject -= add;

		subject.Invoke(x, y);

		//std::cout << r << std::endl;


	}

}

