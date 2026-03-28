
#include <iostream>
#include <string>

#include <common/enums.hpp>
#include <math/delta.hpp>

#include <backend/gl.hpp>
#include <utils/resource_manager.hpp>
#include <renderer/renderer.hpp>
#include <backend/backend.hpp>
#include <editor/editor.hpp>
#include <utils/log.hpp>

#include <utils/input.hpp>
#include <application.hpp>

#define SHADER_PATH "../../core/res/shaders/"

namespace backend
{
    
    shader main_shader;
    
    void force_window_close(void)
    {
	gl::force_window_close();
    }
    void destroy_application(void)
    {
	utils::log::info("backend.cpp::destroy_application() : Destroying application...");

	editor::destroy();
	gl::destroy();
	return;
    }
    
    bool is_window_open(void)
    { 
	return gl::is_window_open();
    }
    
    int init(const window_mode& _window_mode)
    {
	if (gl::init(_window_mode) == -1) return -1;
	
	utils::resource_manager::load_shader(&main_shader, "main_shader", SHADER_PATH"object.vert", SHADER_PATH"object.frag");

	renderer::init();
	utils::input_manager::init(gl::get_current_window());
	application::ready();
	
	editor::init(gl::get_current_window());
	utils::log::info("backend.cpp::init() : backend initialized successfully.");
	utils::log::note("Hello, World!\n");
	return 0;
    }
    
    void begin_frame(void)
    {
	gl::begin_frame();
    }
    void end_frame(void)
    {
	gl::end_frame();
    }

    void loop(void)
    {
	begin_frame();
	if (utils::input_manager::is_key_pressed(KEY_ESC))
	    force_window_close();
	
	math::delta::calculate_delta();
	while (math::delta::is_frametiming())
	{
	    application::process(math::delta::get_delta_time());
	    math::delta::update();
	}
	render();

	end_frame();
    }
    void render(void)
    {
	utils::resource_manager::render_objects();
	utils::resource_manager::play_animations();
	editor::render();
	return;
    }
    
}
