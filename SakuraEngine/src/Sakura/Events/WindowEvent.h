#pragma once

#include "Event.h"

namespace Sakura
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW)

	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};


	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(const std::string& title)
			: m_Title(title) {}

		const std::string& GetTitle() const { return m_Title; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent: " << m_Title;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW)

	private:
		std::string m_Title;
	};
}