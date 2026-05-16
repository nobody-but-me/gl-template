
#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>

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
	
	bool m_animated = false;
	int m_rows, m_cols = 1;
	
	std::vector<animation*> m_animations;
	
    public:
	animation*current_animation=nullptr;
	
	int z_index;
	
	math::vectors::vec2 position;
	math::vectors::vec3 rotation;
	math::vectors::vec2 scale;
	
	std::string name;
	
	glm::vec4 colour;
	
	void set_initialized(bool new_initialized)	    { this->m_initialized = new_initialized; }
	void set_transform(glm::mat4 new_transform)	    { this->m_transform = new_transform; }
	void set_indices(unsigned int new_indices)	    { this->m_indices = new_indices; }
	void set_texture(texture *new_texture)		    { this->m_texture = new_texture; }
	void set_type(object_type new_type)		    { this->m_type = new_type; }
	
	int get_rows(void) { return this->m_rows; }
	int get_cols(void) { return this->m_cols; }
	
	void set_rows(int _rows) { this->m_rows = _rows; }
	void set_cols(int _cols) { this->m_cols = _cols; }
	
	bool get_initialized(void)	{ return this->m_initialized; }
	glm::mat4 get_transform(void)	{ return this->m_transform; }
	texture *get_texture(void)	{ return this->m_texture; }
	unsigned int get_indices(void)	{ return this->m_indices; }
	object_type get_type(void)	{ return this->m_type; }
	
	bool is_animated(void)
	{
	    if(this->m_animations.size()>0)
	        return true;
	    return false;
	}
	
	void create_animation(std::string _name,animation_type _type,int _delay,std::vector<unsigned int> _frames);
	animation*get_animation(std::string _name);
	void remove_animation(std::string _name);
};

#endif//OBJECT_HPP
