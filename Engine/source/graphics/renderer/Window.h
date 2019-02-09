#pragma once
#include <GLFW/glfw3.h>
#include "maths/Vector.h"
#include "events/EventMessage.h"


namespace graphics 
{
	/*Window class creates a window using glfw. Also collects events from mouse
	and keyboard.*/
	class Window
	{
	public:
		Window();
		Window(const char* title, int width, int height);
		~Window()
		{
			HP_STATUS("INIT WINDOW");
		}
		void Terminate();
		void CreateWin(const char* title, int width, int height);
		void SetColour(const float r, const float g, const float b, const float a) const;
		void SetColour(const maths::vec4<float> colour) const;
		void SetEventCallBack(const std::function<void(EventMessage&)>& eventCall) { eventCallBack = eventCall;}
		void Update() const;
		bool isKeyPressed(const unsigned int keycode) const;
		bool IsWindowClosed() const;
		inline int GetWidth() const { return width; };
		inline int GetHeight() const { return height; };
		inline double GetMouseX() const { return mouseX; };
		inline double GetMouseY() const { return mouseY; };
		inline bool IsButtonClicked(const unsigned int keycode) const { return buttons[keycode]; };
		inline GLFWwindow* GetGLFWWinPointer() const { return window; };
		
	private:
		GLFWwindow* window;
		static int width, height;
		static double mouseX;
		static double mouseY;
		const char* title;
		static constexpr unsigned int MAX_KEYS = 256;
		static constexpr unsigned int MAX_BUTTONS = 32;
		static bool keys[MAX_KEYS];
		static bool buttons[MAX_BUTTONS];
		std::function<void(EventMessage&)> eventCallBack;

	};
}