#include "Window.h"

#include "GL/glew.h"

#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../UI/Canvas.h"
#include "../UI/Repository.h"

#include "../Graphics/PerspectiveCamera.h"
#include <chrono>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

namespace {
	Window* window;
	RootScene* repository;
	Canvas* canvas;

	std::chrono::time_point<std::chrono::system_clock> lastPressedTime;
	bool isLeftDown;
	bool isRightDown;

	Vector2df toScreenCoord(GLFWwindow* window, const double x, const double y) {
		int width,height;
		glfwGetWindowSize(window, &width, &height);
		const auto xx = x / (float)width;
		const auto yy = 1.0 - y / (float)height;
		return Vector2df(xx, yy);
	}

	void onMouse(GLFWwindow *window, int button, int action, int mods) {
		if (ImGui::IsMouseHoveringAnyWindow()) {
			return;
		}

		double x, y;
		glfwGetCursorPos(window, &x, &y);
		const auto& coord = toScreenCoord(window, x, y);
		auto now = std::chrono::system_clock::now();
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			/*
			if (lastPressedTime - now < std::chrono::microseconds(200)) {

			}
			*/
			if (action == GLFW_PRESS) {
				canvas->onLeftButtonDown(coord);
				isLeftDown = true;
			}
			else if (action == GLFW_RELEASE) {
				canvas->onLeftButtonUp(coord);
				isLeftDown = false;
			}
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			if (action == GLFW_PRESS) {
				canvas->onRightButtonDown(coord);
				isRightDown = true;
			}
			else if (action == GLFW_RELEASE) {
				canvas->onRightButtonUp(coord);
				isRightDown = false;
			}
		}
		lastPressedTime = now;
	}

	void onMouseMove(GLFWwindow* window, double xpos, double ypos)
	{
		const auto& coord = toScreenCoord(window, xpos, ypos);
		if (isLeftDown) {
			canvas->onLeftDragging(coord);
		}
		else if (isRightDown) {
			canvas->onRightDragging(coord);
		}
	}

	void onWheel(GLFWwindow *window, double offsetx, double offsety)
	{
		canvas->onWheel(offsety);
	}
}

Window::Window(RootScene* model, Canvas* canvas) :
	model(model),
	canvas(canvas)
{
	::window = this;
	::repository = model;
	::canvas = canvas;
}

bool Window::init()
{
	if (!glfwInit()) {
		return false;
	}


	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
	glfwMakeContextCurrent(window);
	//	gl3wInit();

	const auto e = glewInit();
	if (e != GLEW_OK) {
		return false;
	}


	// Setup ImGui binding
	//ImGui_ImplGlfwGL3_Init(window, true);

	const char* glsl_version = "#version 130";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);


	glfwSetScrollCallback(window, onWheel);
	glfwSetMouseButtonCallback(window, onMouse);
	glfwSetCursorPosCallback(window, onMouseMove);

	//canvas->addUICommand(new CameraUICtrl());

	repository->init();

	canvas->build(repository->getObjects(), repository->getObjectFactory());

	return true;
}

void Window::show()
{
	while (!glfwWindowShouldClose(window)) {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar()) {
			for (auto& m : menus) {
				m->show();
			}
			ImGui::EndMainMenuBar();
		}

		for (auto& p : panels) {
			p->show();
		}

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		canvas->render(width, height, repository->getObjects());

		glFlush();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	
	ImGui::DestroyContext();
	glfwTerminate();
}