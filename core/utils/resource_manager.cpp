
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <utils/resource_manager.hpp>
#include <renderer/renderer.hpp>
#include <common/object.hpp>
#include <libs/molson.h>

namespace ResourceManager
{
    
    std::vector<Texture *> g_textures;
    std::vector<Object *> g_objects;
    
    Texture *get_texture(std::string texture_name) {
	auto texture = std::find_if(g_textures.begin(), g_textures.end(), [&](const Texture *tex) { return tex->name == texture_name; });
	if (texture != g_textures.end()) return *texture;
	else return NULL;
    }
    Object *get_object(std::string object_name) {
	auto object = std::find_if(g_objects.begin(), g_objects.end(), [&](const Object *obj) { return obj->name == object_name; });
	if (object != g_objects.end()) return *object;
	else return NULL;
    }
    
    // TODO: ensure that there are not already other objects with the same name in the vectors.
    void load_texture(Texture *texture, std::string texture_name, std::string texture_path, bool alpha = true) {
	if (texture_path == "") return;
	*texture = molson(load_texture)(texture_name.c_str(), texture_path.c_str(), alpha);
	g_textures.emplace_back(texture);
	return;
    }
    
    void init_rectangle(Object *rectangle, std::string object_name, Texture *texture) {
	Gfx::Renderer::init_rect(rectangle, texture, object_name);
	g_objects.emplace_back(rectangle);
	return;
    }
    
    void render_objects() {
	for (Object *obj : g_objects) {
	    Gfx::Renderer::render_object(obj);
	}
	return;
    }
    
}
