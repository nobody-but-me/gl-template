
#include <iostream>
#include <string>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <common/object.hpp>
#include <common/enums.hpp>
#include <math/delta.hpp>

#include <backend/glfw_integration.hpp>
#include <utils/resource_manager.hpp>
#include <renderer/renderer.hpp>
#include <backend/backend.hpp>
#include <editor/editor.hpp>
#include <utils/input.hpp>

namespace BackEnd
{
    
    void force_window_close( ) { GlfwIntegration::force_window_close(); }
    void destroy_application() {
	Editor::destroy();
	GlfwIntegration::destroy();
	return;
    }
    
    bool is_window_open() { return GlfwIntegration::is_window_open(); }
    
    Object quad, quad2;
    Texture texture;
    int init(const WindowMode& window_mode) {
	if (GlfwIntegration::init(window_mode) == -1) return -1;
	
	Gfx::Renderer::init();
	
	InputManager::init(GlfwIntegration::get_current_window());
	Editor::init(GlfwIntegration::get_current_window());
	
	// NOTE: this whole logic will be re-placed in the future. It's here for now just for test purposes.
	ResourceManager::load_texture(&texture, "mir", "../../game/res/sprites/m.png", true);
	
	ResourceManager::init_rectangle(&quad, "Quad", nullptr);
	ResourceManager::init_rectangle(&quad2, "Quad2", &texture);
	
	quad.colour = glm::vec4(0.0f, 255.0f, 0.0f, 255.0f);
	quad.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	quad.position = glm::vec2(0.0f, 0.0f);
	quad.scale = glm::vec2(5.0f, 5.0f);
	quad.z_index = 5;
	
	quad2.colour = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
	quad2.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	quad2.position = glm::vec2(-2.0f, -2.0f);
	quad2.scale = glm::vec2(3.0f, 5.0f);
	quad2.z_index = 0;
	return 0;
    }
    
    void begin_frame() {
	GlfwIntegration::begin_frame();
    }
    void end_frame() {
	GlfwIntegration::end_frame();
    }
    
    void update(float delta) {
	quad2.rotation.z = ((float)glfwGetTime() * 50.0f) * -1.0f;
	
	if (InputManager::is_key_pressed(BUG_LEFT)) quad.position.x -= 5.0f * delta;
	if (InputManager::is_key_pressed(BUG_RIGHT)) quad.position.x += 5.0f * delta;
	if (InputManager::is_key_pressed(BUG_UP)) quad.position.y += 5.0f * delta;
	if (InputManager::is_key_pressed(BUG_DOWN)) quad.position.y -= 5.0f * delta;
	return;
    }
    void render() {
	ResourceManager::render_objects();
	
	Editor::render();
	return;
    }
    void ready() {
	std::cout << "[INFO] : backend.cpp::ready() : Hello, Future GLProject!\n" << std::endl;
    }
    
    void loop() {
	begin_frame();
	if (InputManager::is_key_pressed(BUG_ESC)) force_window_close();
	
	Math::Delta::calculate_delta();
	while (Math::Delta::is_frametiming()) {
	    update(Math::Delta::get_delta_time());
	    Math::Delta::update();
	}
	render();
	
	end_frame();
    }
    
}
