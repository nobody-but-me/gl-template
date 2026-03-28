
#pragma once
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <iostream>
#include <string>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

#include <common/object.hpp>
#include <common/enums.hpp>
#include <libs/molson.h>


constexpr float RECT_VERTEX_DATA[] = {
    0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    
    0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
    1.0f, 0.0f, 1.0f,  1.0f, 0.0f
};

namespace renderer
{
    
    unsigned int get_quad_vao(void);
    unsigned int get_quad_vbo(void);
    
    int init_global_quad(void);
    
    int init_rect(object *_object, texture *texture, std::string _name);
    
    int set_object_transform(object *_object);
    void render_object(object *_object);
    
    void init(void);
}


#endif//RENDERER_HPP
