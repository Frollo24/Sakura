#pragma once

#include "Sakura/Core/Base.h"

namespace Sakura
{
	enum class EventType
	{
		None = 0,
		AppRender, AppUpdate,
		WindowClose, WindowResize,
		KeyPressed, KeyReleased,
		MouseMoved, MouseScrolled,
		MouseButtonPressed, MouseButtonReleased,
	};

	enum EventCategory : uint16_t
	{
		EVENT_CATEGORY_NONE = 0,
		EVENT_CATEGORY_APPLICATION = SKR_BIT(0),
		EVENT_CATEGORY_WINDOW = SKR_BIT(1),
		EVENT_CATEGORY_INPUT = SKR_BIT(2),
		EVENT_CATEGORY_KEYBOARD = SKR_BIT(3),
		EVENT_CATEGORY_MOUSE = SKR_BIT(4),
		EVENT_CATEGORY_MOUSE_BUTTON = SKR_BIT(5)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetEventTypeStatic() { return EventType::type; }\
                               virtual EventType GetEventType() const override { return EventType::type; }\
                               virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual EventCategory GetCategoryFlags() const override { return (EventCategory)(category); }\
                                       virtual int GetCategoryFlagsAsInt() const override { return (int)(category); }

	class Event
	{
	public:
		virtual ~Event() = default;

		inline bool& Handled() { return m_Handled; }

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual EventCategory GetCategoryFlags() const = 0;
		virtual int GetCategoryFlagsAsInt() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

	private:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template <typename T>
		using EventFunc = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template <typename T>
		bool Dispatch(EventFunc<T> func)
		{
			if (m_Event.GetEventType() == T::GetEventTypeStatic())
			{
				m_Event.Handled() = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}

