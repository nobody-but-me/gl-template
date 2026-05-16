
#pragma once
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <memory>

#include <common/animation.hpp>
#include <common/object.hpp>
#include <libs/molson.h>

namespace utils
{
    namespace resource_manager
    {
	// std::unordered_map<std::string,std::shared_ptr<texture>> g_textures;
	// std::unordered_map<std::string,std::shared_ptr<object>> g_objects;
	
	void init_texture(std::string _texture_name, std::string _texture_path, bool _alpha=true,bool _verbose=true);
	texture*get_texture(std::string _texture_name);
	void delete_texture(std::string _texture_name,bool _verbose=false);
	
	void init_generic(std::string _object_name,texture*_texture,object_type _object_type,bool _verbose=true);
	void init_quad(std::string _object_name,texture*_texture,bool _verbose=true);
	
	animation*get_animation(std::string _name,bool _verbose=false);
	void init_animation(std::string _name,animation_type _type,int _delay,std::vector<unsigned int> _frames,bool _verbose=false);
	void delete_animation(std::string _animation_name,bool _verbose=false);
	
	object*get_object(std::string _object_name);
	void delete_object(std::string _object_name,bool _verbose=false);
	
	void render_objects(void);
	
	void load_shader(shader *_shader, const char *_shader_name, const char *_vertex_shader_path, const char *_fragment_shader_path,bool _verbose=true);
	shader *get_shader(std::string _shader_program_name,bool _verbose=false);
	
	// animation *get_animation(std::string _animation_name,bool _verbose=false);
	// texture *get_texture(std::string _texture_name,bool _verbose=false);
	// object *get_object(std::string _object_name,bool _verbose=false);
	
	// void init_animation(animation *_animation, std::string _animation_name, animation_type _animation_type, unsigned int _delay, unsigned int _init_frame, bool _autoplay,bool _verbose=true);
	// void load_texture(texture *_texture, std::string _texture_name, std::string _texture_path, bool _alpha,bool _verbose=true);
	
	// // NOTE : these verbose parameters are appendages for now.
	// void init_generic(object *_object,texture*_texture,object_type _type, std::string _name);
	// void init_rectangle(object *_rect, texture *_texture, std::string _name,bool _verbose=true);
	// void init_circle(object*_rect,texture*_texture,std::string _name,bool _verbose=true);
	
	// void remove_animation(animation*_animation,bool _verbose=true);
	// void remove_texture(texture*_texture,bool _verbose=true);
	// void remove_object(object*_object,bool _verbose=true);
	// void remove_shader(shader*_shader,bool _verbose=true);
	
	// void play_animations(void);
	// void render_objects(void);
	
    }
}

#endif//RESOURCE_MANAGER_HPP
