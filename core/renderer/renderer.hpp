
#pragma once
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <iostream>
#include <string>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

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

namespace Gfx
{
    
    // TODO: re-place this object class definition.
    class Object
    {
	private:
	    unsigned int m_indices;
	    glm::mat4 m_transform;
	    bool m_initialized;
	    
	    std::string m_texture_path;
	    Texture m_texture;
	    bool m_alpha;
	    
	    ObjectType m_type;
	    
	public:
	    int z_index;
	    
	    glm::vec2 position;
	    glm::vec3 rotation;
	    glm::vec2 scale;
	    
	    std::string name;
	    
	    glm::vec4 colour;
	    
	    
	    void set_texture_path(std::string new_texture_path) { this->m_texture_path = new_texture_path; }
	    void set_initialized(bool new_initialized)		{ this->m_initialized = new_initialized; }
	    void set_transform(glm::mat4 new_transform)	{ this->m_transform = new_transform; }
	    void set_indices(unsigned int new_indices)		{ this->m_indices = new_indices; }
	    void set_texture(Texture new_texture)		{ this->m_texture = new_texture; }
	    void set_alpha(bool new_alpha)			{ this->m_alpha = new_alpha; }
	    void set_type(ObjectType new_type)			{ this->m_type = new_type; }
	    
	    std::string get_texture_path()	{ return this->m_texture_path; }
	    bool get_initialized()		{ return this->m_initialized; }
	    glm::mat4 get_transform()		{ return this->m_transform; }
	    Texture get_texture()		{ return this->m_texture; }
	    unsigned int get_indices()		{ return this->m_indices; }
	    bool get_alpha()			{ return this->m_alpha; }
	    ObjectType get_type()		{ return this->m_type; }
	    
    };
    
    namespace Renderer
    {
	
	unsigned int get_quad_vao();
	unsigned int get_quad_vbo();
	Shader *get_main_shader();
	
	int init_global_quad();
	
	int init_rect(Object *object, std::string texture_path, bool alpha, std::string name);
	
	int set_object_transform(Gfx::Object *object);
	void render_object(Gfx::Object *object);
	
	void init();
    }
    
}


#endif//RENDERER_HPP
