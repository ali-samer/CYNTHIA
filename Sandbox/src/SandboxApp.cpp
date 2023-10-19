#include "CYNTHIA/Core/EntryPoint.h"
#include "CYNTHIA/Cynthia.h"
#include <regex>

ImVec2 resize_ui(int &x, int &y, int max_side_size=300)
{
	if (x > max_side_size && y > max_side_size) {
		float d = (float)(x > y ? x : y) / max_side_size;
		return ImVec2(x/d, y/d);
	}
	return ImVec2(x, y);
}


ImVec2 resize_ui(int &x, int &y, int windowWidth, int windowHeight, int maxSideSize = 300)
{
	if (x > maxSideSize || y > maxSideSize) {
		float aspectRatio = static_cast<float>(x) / static_cast<float>(y);
		if (x > y) {
			x = maxSideSize;
			y = static_cast<int>(maxSideSize / aspectRatio);
		} else {
			y = maxSideSize;
			x = static_cast<int>(maxSideSize * aspectRatio);
		}
	} else if (windowWidth < x || windowHeight < y) {
		// If the image is larger than the window, resize it to fit within the window
		float aspectRatio = static_cast<float>(x) / static_cast<float>(y);
		if (x > y) {
			x = windowWidth;
			y = static_cast<int>(windowWidth / aspectRatio);
		} else {
			y = windowHeight;
			x = static_cast<int>(windowHeight * aspectRatio);
		}
	}
	return ImVec2(static_cast<float>(x), static_cast<float>(y));
}


class ExampleLayer : public Cynthia::Layer
{
public:
	ExampleLayer()
		: Layer("Example---")
		{
			std::string image_path = CY_WORKSPACE_DIR_PATH "assets/images/";
			const char* tweet = (image_path + "tweet.jpeg").c_str();
//			const char* woof = (image_path + "woof.jpef").c_str();
			std::string woof = image_path + "woof.jpeg";
			const char* prrr = (image_path + "purrr.png").c_str();
			woofImg = new Cynthia::Image< unsigned char>( woof, Cynthia::Channel::RGB);
//			tweetImg.loadFromFile(tweet, 3);
//
//			tweetImg.loadFromFile((image_path + "tweet.jpeg"), 3);
//			woofImg.loadFromFile((image_path + "woof.jpeg"), 3);
//			prrrImg.loadFromFile((image_path + "prrr.jpg"), 3);
		}
		~ExampleLayer()
		{
			delete woofImg;
		}

	void onUpdate() override
	{
//		CY_INFO("ExampleLayer::Update");

		if(Cynthia::Input::IsKeyPressed(CY_KEY_TAB))
			CY_INFO("Tab key is pressed");
	}

	void onImGuiRender() override //main render function to render UI
	{
		ImGui::Begin("Test");
		ImGui::SeparatorText("Inputs");
		ImGui::Text("Hello, World!");
		ImGui::Text("< w, h > :  %d, %d", woofImg->getWidth(), woofImg->getHeight());
		static float f1 = 100.0f, f2 = 1.0f;
		ImGui::SliderFloat("slider float", &f1, 100.0f, 300.0f, "ratio = %.3f");
		ImGui::SliderFloat("slider float (log)", &f2, 1.0f, 2.2f, "%.6f", ImGuiSliderFlags_Logarithmic);
		ImGuiIO& io = ImGui::GetIO();
		io.FontGlobalScale = f2;
//			ImGui::ColorEdit4("", new float[4]);
		ImVec2 windowSize = ImGui::GetContentRegionAvail();

// You can access the width and height like this:
		float windowWidth = windowSize.x;
		float windowHeight = windowSize.y;


		ImGui::Image((void*)woofImg->getTextureID(), resize_ui(woofImg->getWidth(), woofImg->getHeight(), f1));

		ImGui::End();


	}

	void onEvent(Cynthia::Event& event) override
	{
		CY_TRACE("{0}", event);
	}
	Cynthia::Image<unsigned char> tweetImg;
	Cynthia::Image<unsigned char>* woofImg;
	Cynthia::Image<unsigned char> prrrImg;


};
class Sandbox : public Cynthia::Application
{
public:
  Sandbox()
  {
	  PushLayer(new ExampleLayer());
  }

  ~Sandbox()
  {

  }
};

Sandbox::Application* Cynthia::CreateApplication ( )
{
	return new Sandbox();
}