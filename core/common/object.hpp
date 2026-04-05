
#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <common/animation.hpp>
#include <utils/singleton.hpp>
#include <common/enums.hpp>
#include <libs/molson.h>
#include <math/math.hpp>

class object: public singleton<object>
{
    private:
	unsigned int m_indices;
	glm::mat4 m_transform;
	bool m_initialized;
	
	texture *m_texture;
	object_type m_type;
	
    public:
	bool animated = false;
	int rows, cols = 1;
	animation anim;
	
	int z_index;
	
	math::vectors::vec2 position;
	math::vectors::vec3 rotation;
	math::vectors::vec2 scale;
	
	std::string name;
	
	glm::vec4 colour;
	
	bool selected = false;
	
	void set_initialized(bool new_initialized)	    { this->m_initialized = new_initialized; }
	void set_transform(glm::mat4 new_transform)	    { this->m_transform = new_transform; }
	void set_indices(unsigned int new_indices)	    { this->m_indices = new_indices; }
	void set_texture(texture *new_texture)		    { this->m_texture = new_texture; }
	void set_type(object_type new_type)		    { this->m_type = new_type; }
	
	bool get_initialized()		{ return this->m_initialized; }
	glm::mat4 get_transform()	{ return this->m_transform; }
	texture *get_texture()		{ return this->m_texture; }
	unsigned int get_indices()	{ return this->m_indices; }
	object_type get_type()		{ return this->m_type; }
	
};

#endif//OBJECT_HPP
