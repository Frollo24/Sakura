#pragma once

#include <string>
#include <stdint.h>

struct GLFWwindow;

namespace Sakura
{
	struct WindowProps
	{
		std::string Title = "Sakura Window";
		uint32_t Width = 1600;
		uint32_t Height = 900;
	};

	class Window
	{
	public:
		Window(const WindowProps& props = WindowProps{});
		~Window();

		void OnUpdate();

		inline GLFWwindow* GetNativeWindow() const { return m_NativeWindow; }

		// HACK: This should be treated by the Event System
		bool ShouldClose();

	private:
		WindowProps m_WindowProps{};
		GLFWwindow* m_NativeWindow = nullptr;
	};
}

