#pragma once

#include <list>

namespace Sakura
{
	template <typename R, typename ... args>
	class Delegate
	{
	private:
		

		// subclasses for have *functions and *memberFunctions/Mehtods

		template <typename R, typename ... args>
		class FuncCall
		{
		public:
			FuncCall() = default;
			~FuncCall() = default;

			virtual R Call(args...) = 0;
		};
		

		class FuncPointer : FuncCall<R, args...>
		{
		public:
			FuncPointer() = default;
			~FuncPointer() = default;

			R Call(args...) override
			{
				m_funcPointer(args);
			}
		private:
			R(*m_funcPointer) (args...);
		};

		template <typename C>
		class MethodPointer : FuncCall<R, args...>
		{
		public:
			MethodPointer() = default;
			~MethodPointer() = default;

			R Call(args...) override
			{
				m_methodPointer(args...);
			}
		private:
			R(C::* m_methodPointer) (args...);

			C* m_obj;
		};

		std::list<FuncCall<R, args...>> m_observers;

	public:
		Delegate() 
		{
			m_observers = new std::list<FuncCall<R, args...>>();
		}

		~Delegate() = default;

		template <typename R, typename ... args>
		R Invoke(args...)
		{
			for (FuncCall call : m_observers)
			{
				call->Call(args...);
			}
		}

		void operator += (FuncCall<R, args...> func)
		{
			m_observers.push_back(func);
		}
		void operator -= (FuncCall<R, args...> func)
		{
			for (int i = 0; i < m_observers.size; i++)
			{
				if (m_observers[i] == func)
				{
					m_observers.erase(i);
					return;
				}
			}
		}

	


	};
}