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

	void PrintFunc(int b)
	{
		std::cout << "Me has llamado soy funcion: b" << b << std::endl;
	}

	class SubjectTest
	{
	public:
		SubjectTest(int a) : a(a) {}

		Delegate<void(int)> del;

		void Call()
		{
			del.Invoke(a);
		}


	private:
		int a;

	};

	class ObserverTest
	{
	public:
		ObserverTest(Delegate<void(int)>& subj, int b) : b(b)
		{
			subj += MethodCall(*this, &ObserverTest::Print);
		}

		void Subscribe(Delegate<void(int)>& subj)
		{
			subj += MethodCall(*this, &ObserverTest::Print);
		}

		void DeSubscribe(Delegate<void(int)>& subj)
		{
			subj -= MethodCall(*this, &ObserverTest::Print);
		}

	private:
		int b;

		void Print(int a)
		{
			std::cout << "Me has llamado soy miembro funcion: a, b: " << a << ", " << b << std::endl;
		}
	};

	void DelegateTest()
	{
		/**
		// solo funciones prueba

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
		//*/

		SubjectTest subject = SubjectTest(1);
		ObserverTest observer1 = ObserverTest(subject.del, 2);
		ObserverTest observer2 = ObserverTest(subject.del, 3);

		observer2.Subscribe(subject.del);
		observer1.Subscribe(subject.del);
		//observer1.DeSubscribe(subject.del);

		subject.Call();
		

		//std::cout << r << std::endl;


	}

}

