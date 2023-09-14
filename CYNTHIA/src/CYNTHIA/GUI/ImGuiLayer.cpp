#include "CYNTHIA/GUI/ImGuiLayer.h"
#include "GLFW/glfw3.h"
#include "CYNTHIA/Core/Application.h"
#include "backends/imgui_impl_glfw.h"
#include "CYNTHIA/Core/Log.h"
#include "backends/imgui_impl_opengl3_loader.h"


namespace Cynthia
{

	ImGuiLayer::ImGuiLayer ( )
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer ( )
	{

	}

	void ImGuiLayer::onUpdate ( )
	{

		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(Application::Get().getWindow().getWidth(), Application::Get().getWindow().getHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool show = true;


		ImGui::ShowDemoWindow(&show);
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::Render();
//		int display_w, display_h;
//		glfwGetFramebufferSize(Application::Get().getWindow().getWindow(), &display_w, &display_h);
//		glViewport(0, 0, display_w, display_h);
//		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::onAttach ( )
	{
		ImGui::CreateContext(); // creating "imgui" context data structure to store current state of user interface
		ImGui::StyleColorsDark(); // setting default dark color scheme for imgui
//		ImGui::StyleColorsClassic();
		ImGuiIO& io = ImGui::GetIO(); // important to access user events customize imgui behavior
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors; // allows imgui to change the mouse cursor shape based on the current
															  // widget or interaction
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos; // allows imgui to manipulate mouse pos. important for drag and drop
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		// TODO: set up keymap (keyboard mapping) to allow key events

		// sets up important callbacks
		// and necessary hooks for use with opengl3
		ImGui_ImplGlfw_InitForOpenGL( Application::Get( ).getWindow( ).getWindow() , true);
		ImGui_ImplOpenGL3_Init("#version 410"); // initialize imgui with opengl 3 renderer -v 4.1


	}
	void ImGuiLayer::onDetach ( )
	{
		Layer::onDetach( );
	}
	void ImGuiLayer::onEvent ( Event & event )
	{
//		EventDispatcher dispatcher(event);
//		dispatcher.dispatch<MouseButtonPressedEvent>(CY_BIND_EVENT_FN(ImGuiLayer::onMouseButtonPressedEvent));
//		dispatcher.dispatch<MouseButtonReleasedEvent>(CY_BIND_EVENT_FN(ImGuiLayer::onMouseButtonReleasedEvent));
//		dispatcher.dispatch<MouseScrolledEvent>(CY_BIND_EVENT_FN(ImGuiLayer::onMouseScrolledEvent));
//		dispatcher.dispatch<KeyPressEvent>(CY_BIND_EVENT_FN(ImGuiLayer::onKeyPressedEvent));
//		dispatcher.dispatch<KeyTypedEvent>(CY_BIND_EVENT_FN(ImGuiLayer::onKeyTypedEvent));
//		dispatcher.dispatch<KeyReleasedEvent>(CY_BIND_EVENT_FN(ImGuiLayer::onKeyReleasedEvent));
//		dispatcher.dispatch<WindowResizeEvent>(CY_BIND_EVENT_FN(ImGuiLayer::onWindowResizeEvent));
	}
//	bool ImGuiLayer::onMouseButtonPressedEvent ( MouseButtonPressedEvent & event )
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.MouseDown[event.getMouseButton()] = true;
//		return false;
//	}
//	bool ImGuiLayer::onMouseButtonReleasedEvent ( MouseButtonReleasedEvent & event )
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.MousePos[event.getMouseButton()] = false;
//		return false;
//	}
//	bool ImGuiLayer::onMouseMovedEvent ( MouseMovedEvent & event )
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.MousePos = ImVec2(event.getX(), event.getY());
//		return false;
//	}
//	bool ImGuiLayer::onMouseScrolledEvent ( MouseScrolledEvent & event )
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.MouseWheelH += event.getXOffset();
//		io.MouseWheel += event.getYOffset();
//		return false;
//	}
//	bool ImGuiLayer::onKeyTypedEvent ( KeyTypedEvent& event )
//	{
//		ImGuiIO& io = ImGui::GetIO();
//
//		return false;
//	}
//	bool ImGuiLayer::onKeyPressedEvent ( KeyPressEvent & event )
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.KeysDown[event.getKeyCode()] = true;
//
//		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
//		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
//		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
//		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
//		return false;
//	}
//	bool ImGuiLayer::onKeyReleasedEvent ( KeyReleasedEvent & event )
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.KeysDown[event.getKeyCode()] = false;
//		return false;
//	}
//	bool ImGuiLayer::onWindowResizeEvent ( WindowResizeEvent & event )
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.DisplaySize = ImVec2(event.getWidth(), event.getHeight());
//		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
//		glViewport(0,0,event.getWidth(), event.getHeight());
//		return false;
//	}

}