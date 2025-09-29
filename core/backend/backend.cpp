
#include <iostream>
#include <string>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <backend/glfw_integration.hpp>
#include <renderer/renderer.hpp>
#include <backend/backend.hpp>
#include <common/enums.hpp>
#include <math/delta.hpp>

namespace backEnd
{
    
    void force_window_close( ) { glfwIntegration::force_window_close(); }
    void destroy_application() { glfwIntegration::destroy(); }
    
    bool is_window_open() { return glfwIntegration::is_window_open(); }
    
    Gfx::Object quad, quad2;
    int init(const WindowMode& window_mode) {
	if (glfwIntegration::init(window_mode) == -1) return -1;
	Gfx::Renderer::init();
	
	// NOTE: this whole logic will be re-placed in the future. It's here for now just for test purposes.
	Gfx::Renderer::init_rect(&quad, "", false, "Quad");
	quad.colour = glm::vec4(0.0f, 255.0f, 0.0f, 255.0f);
	quad.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	quad.position = glm::vec2(0.0f, 0.0f);
	quad.scale = glm::vec2(5.0f, 5.0f);
	quad.z_index = 5;
	
	Gfx::Renderer::init_rect(&quad2, "../../game/res/sprites/m.png", true, "Quad2");
	quad2.colour = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
	quad2.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	quad2.position = glm::vec2(-2.0f, -2.0f);
	quad2.scale = glm::vec2(3.0f, 5.0f);
	quad2.z_index = 0;
	return 0;
    }
    
    void begin_frame() {
	glfwIntegration::begin_frame();
    }
    void end_frame() {
	glfwIntegration::end_frame();
    }
    
    void update(float delta) {
	quad2.rotation.z = (float)glfwGetTime() * 50.0f;
	return;
    }
    void render() {
	Gfx::Renderer::render_object(&quad);
	Gfx::Renderer::render_object(&quad2);
    }
    void ready() {
	std::cout << "[INFO] : backend.cpp::ready() : Hello, Gl Project!\n" << std::endl;
    }
    
    void loop() {
	begin_frame();
	
	math::delta::calculate_delta();
	while (math::delta::is_frametiming()) {
	    update(math::delta::get_delta_time());
	    math::delta::update();
	}
	render();
	
	end_frame();
    }
    
}
