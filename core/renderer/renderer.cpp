
#include <iostream>
#include <string.h>
#include <string>

#include <libs/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <backend/gl.hpp>
#include <utils/resource_manager.hpp>
#include <renderer/renderer.hpp>
#include <common/object.hpp>
#include <common/enums.hpp>
#include <utils/log.hpp>

#define MOLSON_IMPLEMENTATION
#include <libs/molson.h>

namespace renderer
{
    // TODO: make a better function for that.
    static int check_gl_errors(void)
    {
	GLenum err = glGetError();
	if ((err == glGetError()) != GL_NO_ERROR)
	{
	    if (err == GL_NO_ERROR)
	        return 0;
	    std::string error_message;
	    
	    if (err == GL_INVALID_FRAMEBUFFER_OPERATION) error_message = "Invalid framebuffer operation.";
	    else if (err == GL_INVALID_OPERATION) error_message        = "Invalid operation.";
	    else if (err == GL_STACK_UNDERFLOW) error_message          = "stack underflow.";
	    else if (err == GL_STACK_OVERFLOW) error_message           = "stack overflow.";
	    else if (err == GL_INVALID_VALUE) error_message            = "Invalid value.";
	    else if (err == GL_OUT_OF_MEMORY) error_message            = "out of memory.";
	    else if (err == GL_INVALID_ENUM) error_message             = "Invalid enum.";
	    
	    utils::log::error("render.cpp::check_gl-errors() : %s.", error_message.c_str());
	    return 1;
	}
	return 0;
    }
    
    unsigned int g_QUAD_VAO = 0, g_QUAD_VBO = 0;
    shader *g_main_object_shader;
    
    unsigned int get_quad_vao(void)
    {
	return g_QUAD_VAO;
    }
    unsigned int get_quad_vbo(void)
    {
	return g_QUAD_VBO;
    }
    
    int init_global_quad(void)
    {
	glGenVertexArrays(1, &g_QUAD_VAO);
	glBindVertexArray(g_QUAD_VAO);
	glGenBuffers(1, &g_QUAD_VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, g_QUAD_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RECT_VERTEX_DATA), RECT_VERTEX_DATA, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return check_gl_errors();
    }
    
    int init_rect(object *_object, texture *_texture, std::string _name)
    {
	_object->set_type(object_type::QUAD);
	_object->name = _name;
	
	if (_texture != nullptr)
	{
	    _object->set_texture(_texture);
	}
	else
	{
	    _object->set_texture(nullptr);
	}
	_object->set_initialized(true);
	return 0;
    }
    
    int set_object_transform(object *_object)
    {
	molson(use_shader)(g_main_object_shader);
	
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(_object->position.x, _object->position.y, _object->z_index));
	
	trans = glm::translate(trans, glm::vec3( 0.5f * _object->scale.x,  0.5f * _object->scale.y, 0.0f ));
	trans = glm::rotate(trans, glm::radians(_object->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(_object->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(_object->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::translate(trans, glm::vec3(-0.5f * _object->scale.x, -0.5f * _object->scale.y, 0.0f ));
	
	trans = glm::scale(trans, glm::vec3(_object->scale.x,_object->scale.y, 1.0f));
	
	if (molson(set_matrix4)("transform", &trans, false, g_main_object_shader) != 0)
	{
	    utils::log::error("renderer.cpp::set_object_transform() : Failed to set object transform.");
	    return -1;
	}
	return 0;
    }
    void render_object(object *_object)
    {
	texture *object_texture = _object->get_texture();
	object_type object_type = _object->get_type();
	molson(use_shader)(g_main_object_shader);
	
	float colour[] = { _object->colour.x / 255, _object->colour.y / 255, _object->colour.z / 255, _object->colour.w / 255 };
	if ((molson(set_vector4_f)("colour", colour, false, g_main_object_shader)) != 0)
	{
	    utils::log::error("renderer.cpp::render_object() : Failed to set colour of object %s.", _object->name.c_str());
	    return;
	}
	
	set_object_transform(_object);
	if (!object_texture)
	{
	    molson(set_bool)("is_textured", false, g_main_object_shader);
	}
	else
	{
	    molson(set_int)("object_texture", 0, false, g_main_object_shader);
	    molson(set_bool)("is_textured", true, g_main_object_shader);
	    
	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, object_texture->id);
	    

	    if (_object->animated)
	    {
		molson(set_int)("index", _object->anim.get_index(), true, g_main_object_shader);
		molson(set_int)("columns", _object->cols, true, g_main_object_shader);
		molson(set_int)("rows", _object->rows, true, g_main_object_shader);
		molson(set_bool)("is_animated", true, g_main_object_shader);
	    }
	}
	
	switch (object_type)
	{
	    case object_type::QUAD:
		glBindVertexArray(g_QUAD_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		break;
	    case object_type::TRIANGLE:
		utils::log::todo("triangle is still not implemented.\n");
		break;
		
	}
	return;
    }
	
    void init(void)
    {
	// molson(init_shader)("main_shader", SHADER_PATH"object.vert", SHADER_PATH"object.frag", &g_main_object_shader);
	g_main_object_shader = utils::resource_manager::get_shader("main_shader");
	
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	
	float win_height = static_cast<float>(gl::get_current_window_height()) / 100.0f;
	float win_width = static_cast<float>(gl::get_current_window_width()) / 100.0f;
	
	projection = glm::ortho(win_width * -1.0f, win_width, win_height * -1.0f, win_height, -1.0f, 100.0f);
	view  = glm::translate(view, glm::vec3(-3.0f, -2.5f, -50.0f)); // TODO: magic numbers.
	
	if ((molson(set_matrix4)("projection", &projection, true, g_main_object_shader)) != 0)
	{
	    utils::log::error("renderer.cpp::init() : Failed to set main object shader project uniform variable.");
	}
	if ((molson(set_matrix4)("view", &view, true, g_main_object_shader)) != 0)
	{
	    utils::log::error("renderer.cpp::init() : Failed to set main object shader view uniform variable.");
	}
	// NOTE: bad: kinda hard-coded; It would be better if, after calling the rect initialize function, the code indentified if the global quad was already loaded or not.
	init_global_quad();
	return;
    }
}

// Perspective projection alternative
// projection = glm::perspective(glm::radians(45.0f), static_cast<float>(GlfwIntegration::get_current_window_width()) / static_cast<float>(glfwIntegration::get_current_window_height()), 0.1f, 100.0f);
