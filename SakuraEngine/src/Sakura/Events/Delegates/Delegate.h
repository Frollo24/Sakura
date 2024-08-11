#pragma once

#include <vector>
#include <utility>

namespace Sakura
{
	/**/
	template <typename Signature>
	class Delegate;
	template <typename ... Args>
	class Delegate<void(Args ... args)>	// Son voids aunque se pueda hacer con valores porque no hay caso en el que quieras valores y dan algún problema
	{
	private:

		struct Base
		{
			virtual ~Base() {}
			virtual bool IsThisType(Base* other) = 0;
			virtual void DoCall(Args ... args) = 0;
		};

		template <typename funcPointer>
		struct Call : Base
		{
			funcPointer callBack;
			template <typename C>
			Call(C&& callBack) : callBack(std::forward<C>(callBack)) {}	// le damos al constructor el puntero a función tal cual este

			bool IsThisType(Base* other) 
			{
				Call<funcPointer>* temp = dynamic_cast<Call<funcPointer>*>(other);
				return (temp && this->callBack == temp->callBack);	// Devuelve true si los dos callbacks son iguales, en caso contrario false
			}

			void DoCall(Args ... args)
			{
				this->callBack(std::forward<Args>(args)...);
			}

		};

		std::vector<Base*> m_functionPointers;

		Delegate(const Delegate&) = delete;
		void operator=(const Delegate&) = delete;
		// Se borran para evitar problemas con copuias de delegates porque para empezar no tienen sentido

	public:

		Delegate() = default;

		template <typename funcPointer>
		Delegate& operator+=(funcPointer&& func)
		{
			m_functionPointers.push_back(new Call<funcPointer>(std::forward<funcPointer>(func)));
			return *this;
		}

		template <typename funcPointer>
		Delegate& operator-=(funcPointer&& func)
		{
			bool stop = false;
			Call<funcPointer> temp(std::forward<funcPointer>(func));
			for (int i = 0; i < m_functionPointers.size() && !stop; i++)
			{
				if (temp.IsThisType(m_functionPointers[i]))
				{
					m_functionPointers.erase(m_functionPointers.begin() + i);
					stop = true;
				}
			}
			return *this;
		}

		void Invoke(Args ... args)
		{
			for (auto& func : m_functionPointers)
			{
				func->DoCall(args...);
			}
		}

	};


	template <typename RC, typename Class, typename ... Args>
	class MemberCall
	{
	private:
		Class* m_objectInstance;
		RC(Class::* m_memberFuncPointer)(Args ...);

	public:
		MemberCall(Class* object, RC(Class::* memberFunc)(Args ...)) : m_objectInstance(object), m_memberFuncPointer(memberFunc) {}

		RC operator()(Args ... args)
		{
			return (this->m_objectInstance->*this->m_memberFuncPointer)(std::forward<Args>(args)...);
		}

		bool operator==(const MemberCall& other)
		{
			return (this->m_objectInstance == other.m_objectInstance &&
				this->m_memberFuncPointer == other.m_memberFuncPointer);
		}

		bool operator!=(const MemberCall& other)
		{
			return !(*this == other);
		}
	};


	// Azucar sintactico para no tener que escribir en las subscripciones el <> con sus valores
	template <typename RC, typename Class, typename ... Args>
	MemberCall<RC, Class, Args ...> MethodCall(Class& object, RC(Class::* memberFunc)(Args ...))
	{
		return MemberCall<RC, Class, Args ...>(&object, memberFunc);
	}


	//*/


}