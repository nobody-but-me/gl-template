
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include <libs/glad.h>
#include <GLFW/glfw3.h>

#include <utils/resource_manager.hpp>
#include <renderer/renderer.hpp>
#include <common/animation.hpp>
#include <common/object.hpp>
#include <libs/molson.h>
#include <utils/log.hpp>

namespace utils
{
    namespace resource_manager
    {
	
	std::vector<animation*> g_animations;
	std::vector<texture*> g_textures;
	std::vector<shader*> g_shaders;
	std::vector<object*> g_objects;
	
	animation *get_animation(std::string _animation_name,bool _verbose)
	{
	    auto _animation = std::find_if(g_animations.begin(), g_animations.end(), [&](const animation *anim) { return anim->name == _animation_name; });
	    if (_animation != g_animations.end())
	    {
		if(_verbose)
		{
		    utils::log::info("resource_manager.cpp::get_animation() : %s animation had been found successfully",_animation_name);
		}
		return *_animation;
	    }
	    else
	    {
		if(_verbose)
		{
		    utils::log::error("resource_manager.cpp::get_animation() : %s animation not found.",_animation_name);
		}
		return NULL;
	    }
	}
	texture *get_texture(std::string _texture_name,bool _verbose)
	{
	    auto _texture = std::find_if(g_textures.begin(), g_textures.end(), [&](const texture *tex) { return tex->name == _texture_name; });
	    if (_texture != g_textures.end())
	    {
		if(_verbose)
		{
		    utils::log::info("resource_manager.cpp::get_texture() : %s texture had been found successfully",_texture_name);
		}
		return *_texture;
	    }
	    else
	    {
		if(_verbose)
		{
		    utils::log::error("resource_manager.cpp::get_texture() : %s texture not found.",_texture_name);
		}
		return NULL;
	    }
	}
	shader *get_shader(std::string _shader_program_name,bool _verbose)
	{
	    auto _shader = std::find_if(g_shaders.begin(), g_shaders.end(), [&](const shader *shdr) { return shdr->name == _shader_program_name; });
	    if (_shader != g_shaders.end())
	    {
		if(_verbose)
		{
		    utils::log::info("resource_manager.cpp::get_shader() : %s shader had been found successfully",_shader_program_name);
		}
		return *_shader;
	    }
	    else
	    {
		if(_verbose)
		{
		    utils::log::error("resource_manager.cpp::get_shader() : %s shader not found.",_shader_program_name);
		}
		return NULL;
	    }
	}
	object *get_object(std::string _object_name,bool _verbose)
	{
	    auto _object = std::find_if(g_objects.begin(), g_objects.end(), [&](const object *obj) { return obj->name == _object_name; });
	    if (_object != g_objects.end())
	    {
		if(_verbose)
		{
		    utils::log::info("resource_manager.cpp::get_object() : %s object had been found successfully",_object_name);
		}
		return *_object;
	    }
	    else
	    {
		if(_verbose)
		{
		    utils::log::error("resource_manager.cpp::get_object() : %s object not found.",_object_name);
		}
		return NULL;
	    }
	}
	
	// TODO: write the other functions here;
	void remove_animation(animation*_animation,bool _verbose)
	{
	    if (get_animation(_animation->name)==NULL)
	    {
		if (_verbose)
		{
		    utils::log::error("resource_manager.cpp::remove_animation() : Failed to remove %s animation: animmation not found.",_animation->name.c_str());
		}
		return;
	    }
	    g_animations.erase(std::remove(g_animations.begin(),g_animations.end(),_animation),g_animations.end());
	    
	    if (get_animation(_animation->name)==NULL)
	    {
		if (_verbose)
		{
		    utils::log::info("resource_manager.cpp::remove_animation() : %s animation removed successfully.",_animation->name.c_str());
		}
		return;
	    }
	    return;
	}
	void remove_texture(texture*_texture,bool _verbose);
	void remove_object(object*_object,bool _verbose)
	{
	    if (get_object(_object->name)==NULL)
	    {
		if (_verbose)
		{
		    utils::log::error("resource_manager.cpp::remove_object() : Failed to remove %s object: object not found.",_object->name.c_str());
		}
		return;
	    }
	    g_objects.erase(std::remove(g_objects.begin(),g_objects.end(),_object),g_objects.end());
	    
	    if (get_object(_object->name)==NULL)
	    {
		if (_verbose)
		{
		    utils::log::info("resource_manager.cpp::remove_object() : %s object removed successfully.",_object->name.c_str());
		}
		return;
	    }
	    return;
	}
	void remove_shader(shader*_shader,bool _verbose);
	
	// TODO: ensure that there are not already other objects with the same name in the vectors.
	void init_animation(animation *_animation, std::string _animation_name, animation_type _animation_type, unsigned int _delay, unsigned int _init_frame, bool _autoplay,bool _verbose)
	{
	    _animation->name = _animation_name;
	    
	    _animation->set_animation_type(_animation_type);
	    _animation->set_autoplay(_autoplay);
	    _animation->set_index(_init_frame);
	    _animation->set_delay(_delay);
	    
	    if (_autoplay == true)
	    {
		_animation->set_is_playing(true);
	    }
	    g_animations.emplace_back(_animation);
	    return;
	}
	void load_texture(texture *_texture, std::string _texture_name, std::string _texture_path, bool _alpha = true,bool _verbose)
	{
	    if (_texture_path == "")
	    {
		return;
	    }
	    *_texture = molson(load_texture)(_texture_name.c_str(), _texture_path.c_str(), _alpha);
	    g_textures.emplace_back(_texture);
	    return;
	}
	void load_shader(shader *_shader, const char *_shader_name, const char *_vertex_shader_path, const char *_fragment_shader_path,bool _verbose)
	{
	    if ((strcmp("", _fragment_shader_path)) == 0)
	    {
		return;
	    }
	    if ((strcmp("", _vertex_shader_path)) == 0)
	    {
		return;
	    }
	    molson(init_shader)(_shader_name, _vertex_shader_path, _fragment_shader_path, _shader);
	    g_shaders.emplace_back(_shader);
	    return;
	}
	
	void init_rectangle(object *_rectangle, std::string _object_name, texture *_texture,bool _verbose)
	{
	    renderer::init_rect(_rectangle, _texture, _object_name);
	    g_objects.emplace_back(_rectangle);
	    return;
	}
	
	void play_animations(void)
	{
	    for (animation *anim : g_animations)
	    {
		if (anim->get_is_playing())
		{
		    anim->process();
		}
		else
		{
		    anim->stop();
		}
	    }
	    return;
	}
	
	void render_objects(void)
	{
	    for (object *obj : g_objects)
	    {
		renderer::render_object(obj);
	    }
	    return;
	}
	
    }
}
