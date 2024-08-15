#pragma once

#include "Sakura/Core/Base.h"
#include "Sakura/Events/Event.h"
#include "Sakura/Render/RenderInstance.h"

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
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const WindowProps& props = WindowProps{});
		~Window();

		void OnUpdate();

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		inline void SetMinimized(bool minimized) { m_Data.Minimized = minimized; }
		inline bool IsMinimized() const { return m_Data.Minimized; }
		void SetVSync(bool enabled);
		inline bool IsVSync() const { return m_Data.VSync; }

		inline GLFWwindow* GetNativeWindow() const { return m_NativeWindow; }

	private:
		struct WindowData
		{
			std::string Title = "";
			uint32_t Width = 0;
			uint32_t Height = 0;
			bool Minimized = false;
			bool VSync = false;

			WindowData(const WindowProps& props)
				: Title(props.Title), Width(props.Width), Height(props.Height) {}

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;

		GLFWwindow* m_NativeWindow = nullptr;

		RenderInstance* m_RenderInstance = nullptr;
	};
}

