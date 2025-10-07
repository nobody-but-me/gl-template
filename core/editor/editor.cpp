

#include <iostream>
#include <string>

#include <libs/glad.h>
#include <GLFW/glfw3.h>

#include "libs/imgui/imgui.h"
#include "libs/imgui/imgui_impl_glfw.h"
#include "libs/imgui/imgui_impl_opengl3.h"

#include <utils/resource_manager.hpp>
#include <editor/editor.hpp>
#include <common/object.hpp>
#include <utils/log.hpp>

#define GUI_SCALE ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor())

namespace Editor
{
    
    GLFWwindow *g_main_window;
    
    Object *quad;
    
    static float quad_colour[3];
    
    void destroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	return;
    }
    
    void render() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	ImGui::Begin("DearImGui window example");
	
	// ImGui::SliderFloat("Float slider", &f, 0.0f, 1.0f);
	
	if (ImGui::ColorEdit3("  Quad Colour", (float *)&quad_colour)) {
	    quad->colour.x = quad_colour[0] * 255.0f;
	    quad->colour.y = quad_colour[1] * 255.0f;
	    quad->colour.z = quad_colour[2] * 255.0f;
	}
	
	ImGuiIO &io = ImGui::GetIO(); (void)io;
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	
	ImGui::End();
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return;
    }
    
    void init(GLFWwindow *window) {
	g_main_window = window;
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGuiIO &io = ImGui::GetIO(); (void)io;
	
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	
	ImGui::StyleColorsDark();
	
	ImGuiStyle &style = ImGui::GetStyle();
	style.ScaleAllSizes(GUI_SCALE);
	style.FontScaleDpi = GUI_SCALE;
	
	ImGui_ImplGlfw_InitForOpenGL(g_main_window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core"); // TODO: add support for more glsl versions.
	
	// having fun.
	quad = ResourceManager::get_object("Quad");
	if (quad != NULL) {
	    quad_colour[0] = quad->colour.x / 255.0f;
	    quad_colour[1] = quad->colour.y / 255.0f;
	    quad_colour[2] = quad->colour.z / 255.0f;
	}
    }
    
}
