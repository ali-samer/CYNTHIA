

#include "CYNTHIA/GUI/ImGuiLayer.h"
#include "GLFW/glfw3.h"
#include "CYNTHIA/Core/Application.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
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
#if 0
	void ImGuiLayer::onUpdate ( )
	{

		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2( Application::Get( ).getWindowObj( ).getWidth(), Application::Get( ).getWindowObj( ).getHeight());

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
//		glfwGetFramebufferSize(Application::Get().getWindow().getWindowObj(), &display_w, &display_h);
//		glViewport(0, 0, display_w, display_h);
//		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
#endif
	void ImGuiLayer::onAttach ( )
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext(); // creating "imgui" context data structure to store current state of user interface
		ImGui::StyleColorsDark(); // setting default dark color scheme for imgui
//		ImGui::StyleColorsClassic();
		ImGuiIO& io = ImGui::GetIO(); // important to access user events customize imgui behavior
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors; // allows imgui to change the mouse cursor shape based on the current
															  // widget or interaction
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos; // allows imgui to manipulate mouse pos. important for drag and drop
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		#if CY_PLATFORM_WINDOWS
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		#endif


		// sets up important callbacks
		// and necessary hooks for use with opengl3
		ImGui_ImplGlfw_InitForOpenGL( Application::Get( ).getWindowObj( ).getWindow() , true);
		ImGui_ImplOpenGL3_Init("#version 410"); // initialize imgui with opengl 3 renderer -v 4.1


	}
	void ImGuiLayer::onDetach ( )
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void ImGuiLayer::begin ( )
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiLayer::end ( )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(Application::Get().getWindowObj().getWidth(), Application::Get().getWindowObj().getHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if(io.ConfigFlags  & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(current_context);
		}
	}
	void ImGuiLayer::onImGuiRender ( )
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}


}