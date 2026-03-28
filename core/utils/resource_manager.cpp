
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
	
	animation *get_animation(std::string _animation_name)
	{
	    auto _animation = std::find_if(g_animations.begin(), g_animations.end(), [&](const animation *anim) { return anim->name == _animation_name; });
	    if (_animation != g_animations.end()) return *_animation;
	    else return NULL;
	}
	texture *get_texture(std::string _texture_name)
	{
	    auto _texture = std::find_if(g_textures.begin(), g_textures.end(), [&](const texture *tex) { return tex->name == _texture_name; });
	    if (_texture != g_textures.end()) return *_texture;
	    else return NULL;
	}
	shader *get_shader(std::string _shader_program_name)
	{
	    auto _shader = std::find_if(g_shaders.begin(), g_shaders.end(), [&](const shader *shdr) { return shdr->name == _shader_program_name; });
	    if (_shader != g_shaders.end()) return *_shader;
	    else return NULL;
	}
	object *get_object(std::string _object_name)
	{
	    auto _object = std::find_if(g_objects.begin(), g_objects.end(), [&](const object *obj) { return obj->name == _object_name; });
	    if (_object != g_objects.end())
	    {
		utils::log::info("resource_manager.cpp::get_object() : Object had been found successfully");
		return *_object;
	    }
	    else
	    {
		utils::log::error("resource_manager.cpp::get_object() : Object not found.");
		return NULL;
	    }
	}
	
	// TODO: ensure that there are not already other objects with the same name in the vectors.
	void init_animation(animation *_animation, std::string _animation_name, animation_type _animation_type, unsigned int _delay, unsigned int _init_frame, bool _autoplay)
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
	void load_texture(texture *_texture, std::string _texture_name, std::string _texture_path, bool _alpha = true)
	{
	    if (_texture_path == "")
	    {
		return;
	    }
	    *_texture = molson(load_texture)(_texture_name.c_str(), _texture_path.c_str(), _alpha);
	    g_textures.emplace_back(_texture);
	    return;
	}
	void load_shader(shader *_shader, const char *_shader_name, const char *_vertex_shader_path, const char *_fragment_shader_path)
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
	
	void init_rectangle(object *_rectangle, std::string _object_name, texture *_texture)
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
