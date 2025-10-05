
#pragma once
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <common/object.hpp>
#include <libs/molson.h>

namespace ResourceManager
{
    
    Texture *get_texture(std::string texture_name);
    Object *get_object(std::string object_name);
    
    void load_texture(Texture *texture, std::string texture_name, std::string texture_path, bool alpha);
    void init_rectangle(Object *rectangle, std::string object_name, Texture *texture);
    
    void render_objects();
    
}


#endif//RESOURCE_MANAGER_HPP
