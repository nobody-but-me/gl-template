
#pragma once
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <common/animation.hpp>
#include <common/object.hpp>
#include <libs/molson.h>

namespace utils
{
    namespace resource_manager
    {
	
	animation *get_animation(std::string _animation_name);
	shader *get_shader(std::string _shader_program_name);
	texture *get_texture(std::string _texture_name);
	object *get_object(std::string _object_name);
	
	void init_animation(animation *_animation, std::string _animation_name, animation_type _animation_type, unsigned int _delay, unsigned int _init_frame, bool _autoplay);
	void load_shader(shader *_shader, const char *_shader_name, const char *_vertex_shader_path, const char *_fragment_shader_path);
	void load_texture(texture *_texture, std::string _texture_name, std::string _texture_path, bool _alpha);
	void init_rectangle(object *_rectangle, std::string _object_name, texture *_texture);
	
	void play_animations(void);
	void render_objects(void);
	
    }
}

#endif//RESOURCE_MANAGER_HPP
