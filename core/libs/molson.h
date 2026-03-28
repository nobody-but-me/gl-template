
#ifndef MOLSON_H
#define MOLSON_H
#define molson(x) molson##x

#include <stdbool.h>

// -- Texture and Shader types.
typedef struct
{
    unsigned int internal_format;
    unsigned int image_format;
    unsigned int filter_min;
    unsigned int filter_max;
    unsigned int wrap_s;
    unsigned int wrap_t;
    unsigned int height;
    unsigned int width;
    unsigned int id;
    bool alpha;
    
    const char *name;
    const char *path;
} texture;

typedef struct
{
    unsigned int fragment_shader;
    unsigned int vertex_shader;
    unsigned int ID;
    
    const char *name;
} shader;

const char *molson(file_to_char)(const char *_file_path);

texture molson(load_texture)(const char *_name, const char *_file_path, bool _alpha);

int molson(init_shader)(const char *_shader_name, const char *_vertex_path, const char *_fragment_path, shader *_shader);
void molson(destroy_shader)(shader *_shader);
void molson(use_shader)(shader *_shader);

int molson(set_vector2_f)(const char *_name, float _value[2], bool _use_shader, shader *_shader);
int molson(set_vector3_f)(const char *_name, float _value[3], bool _use_shader, shader *_shader);
int molson(set_vector4_f)(const char *_name, float _value[4], bool _use_shader, shader *_shader);
int molson(set_matrix4)(const char *_name, void *_value, bool _use_shader, shader *_shader);

int molson(set_float)(const char *_name, float _value, bool _use_shader, shader *_shader);
int molson(set_int)(const char *_name, int _value, bool _use_shader, shader *_shader);
int molson(set_bool)(const char *_name, bool _value, shader *_shader);

// --------------------------------------------------
// |               IMPLEMENTATION                   |
// --------------------------------------------------

#endif//MOLSON_H
#ifdef MOLSON_IMPLEMENTATION

#define GLAD 0
#define GLUT 1

#define GLLOADER GLAD
#define VERBOSE true

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

// -- Dependencies:
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#if GLLOADER == GLAD
#include <glad.h>
#elif GLLOADER == GLUT
// TODO: Add glut support(although it's deprecated and old and you were not supposed to be using it.);
#endif
// --

// -- Function destinated to load text files. Sometimes it's useful.
const char *molson(file_to_char)(const char *_file_path)
{
    long buffer_size = 0;
    char *buffer;
    FILE *file;
    
    file = fopen(_file_path, "r");
    if (file == NULL)
    {
	fprintf(stderr, "[MOLSON]: FAILED :: File could not be loaded. \n");
	fclose(file);
	return NULL;
    }
    if (fseek(file, 0, SEEK_END) < 0) goto BLANK;
    buffer_size = ftell(file);
    buffer = (char *)malloc(buffer_size + 1);
    if (buffer == NULL) {
	fprintf(stderr, "[MOLSON]: FAILED :: Buffer could not be read. \n");
	return NULL;
    }
    
    if (fseek(file, 0, SEEK_SET) < 0) goto BLANK;
    fread(buffer, 1, buffer_size, file);
    if (ferror(file))
    {
	fprintf(stderr, "[MOLSON]: FAILED :: File could not be read. \n");
	return NULL;
    }
    fclose(file);
    
#if VERBOSE == true
    printf("[MOLSON]: File have been loaded sucessfully. \n");
#endif
    return buffer;
    
BLANK:
    fprintf(stderr, "[INFO]: File is blank. \n");
    fclose(file);
    
    buffer = (char *)malloc(sizeof(char));
    free(buffer);
    return NULL;
}
// --

// -- Texture loading and generating.
static void init_texture(texture *_texture)
{
    _texture->filter_min = GL_LINEAR;
    _texture->filter_max = GL_LINEAR;
    _texture->image_format = GL_RGB;
    _texture->wrap_s = GL_REPEAT;
    _texture->wrap_t = GL_REPEAT;
    _texture->height = 0;
    _texture->width = 0;
    
    glGenTextures(1, &_texture->id);
    return;
}

static void generate_texture(unsigned int _width, unsigned int _height, unsigned char *_data, texture *_texture)
{
    _texture->height = _height;
    _texture->width = _width;
    
    glBindTexture(GL_TEXTURE_2D, _texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0, _texture->internal_format, _texture->width, _texture->height, 0, _texture->image_format, GL_UNSIGNED_BYTE, _data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _texture->wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _texture->wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _texture->filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _texture->filter_max);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
}

texture molson(load_texture)(const char *_name, const char *_file_path, bool _alpha)
{
    texture new_texture;
    init_texture(&new_texture);
    
    // Setting alpha format if alpha parameters is true
    if (_alpha)
    {
	new_texture.internal_format = GL_RGBA;
	new_texture.image_format    = GL_RGBA;
    }
    int height, width, channels;
    
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(_file_path, &width, &height, &channels, 0);
    if (data == NULL) {
	printf("[MOLSON]: FAILED :: Failed to load _texture. \n");
	return new_texture;
    }
    generate_texture(width, height, data, &new_texture);
    stbi_image_free(data);
    
    new_texture.path = _file_path;
    new_texture.alpha = _alpha;
    new_texture.name = _name;
#if VERBOSE == true
    printf("[MOLSON]: Texture had been loaded successfully. \n");
#endif
    return new_texture;
}
// --

/*
 -- OpenGL Shader loader.
    INFO: yes, here I write a similar code found in 'file_to_char' function, within this same file. I do that for some reasons:
        - Vertex and fragment shader error handling;
	- Vertex and fragment shader text formating;
	- 
    Again: that is what works for me and this is, for sure, not the better approach. Any changes suggestions would be welcome.
*/
int molson(init_shader)(const char *_shader_name, const char *_vertex_path, const char *_fragment_path, shader *_shader)
{
    _shader->name = _shader_name;
    long buffer_length = 0;
    
    char *fragment_buffer, *vertex_buffer;
    FILE *fragment_code, *vertex_code;
    
    fragment_code = fopen(_fragment_path, "r");
    if (fragment_code == NULL)
    {
	fprintf(stderr, "[MOLSON]: FAILED :: Fragment shader file could not be loaded. \n");
	fclose(fragment_code);
	_shader->ID = -1;
	return 1;
    }
    if (fseek(fragment_code, 0, SEEK_END) < 0) goto BLANK;
    
    buffer_length = ftell(fragment_code);
    fragment_buffer = (char *)malloc(buffer_length + 1);
    if (fragment_buffer == NULL)
    {
	fprintf(stderr, "[MOLSON]: FAILED :: Fragment shader variable could not be allocated. \n");
	fclose(fragment_code);
	_shader->ID = -1;
	return 1;
    }
    if (fseek(fragment_code, 0, SEEK_SET) < 0) goto BLANK;
    fread(fragment_buffer, 1, buffer_length, fragment_code);
    if (ferror(fragment_code))
    {
	fprintf(stderr, "[MOLSON]: FAILED :: Fragment shader file could not be read. \n");
	fclose(fragment_code);
	_shader->ID = -1;
	return 1;
    }
    fragment_buffer[buffer_length] = '\0';
    
    vertex_code = fopen(_vertex_path, "r");
    if (vertex_code == NULL)
    {
	fprintf(stderr, "[MOLSON]: FAILED :: Vertex shader file could not be loaded. \n");
	fclose(vertex_code);
	_shader->ID = -1;
	return 1;
    }
    if (fseek(vertex_code, 0, SEEK_END) < 0) goto BLANK;
    
    buffer_length = ftell(vertex_code);
    vertex_buffer = (char *)malloc(buffer_length + 1);
    if (vertex_buffer == NULL)
    {
	fprintf(stderr, "[MOLSON]: FAILED :: Vertex shader variable could not be allocated. \n");
	fclose(vertex_code);
	_shader->ID = -1;
	return 1;
    }
    
    if (fseek(vertex_code, 0, SEEK_SET < 0)) goto BLANK;
    fread(vertex_buffer, 1, buffer_length, vertex_code);
    if (ferror(vertex_code))
    {
	fprintf(stderr, "[FAILED]: Fragment shader file could not be read. \n");
	fclose(vertex_code);
	_shader->ID = -1;
	return 1;
    }
    vertex_buffer[buffer_length] = '\0';
    
    if (fragment_code) fclose(fragment_code);
    if (vertex_code)   fclose(vertex_code);
    
    char info_log[512];
    int  success;
    
    _shader->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_shader->vertex_shader, 1, (GLchar const * const *)&vertex_buffer, NULL);
    glCompileShader(_shader->vertex_shader);
    glGetShaderiv(_shader->vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
	glGetShaderInfoLog(_shader->vertex_shader, 512, NULL, info_log);
	fprintf(stderr, "[MOLSON]: FAILED :: Vertex shader compilation failed. \n");
	fprintf(stderr, "[INFO_LOG]: %s. \n", info_log);
	return 1;
    }
#if VERBOSE == true
    printf("[MOLSON]: Vertex shader compiled successfully. \n");
#endif
    
    _shader->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_shader->fragment_shader, 1, (GLchar const * const *)&fragment_buffer, NULL);
    glCompileShader(_shader->fragment_shader);
    glGetShaderiv(_shader->fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
	glGetShaderInfoLog(_shader->fragment_shader, 512, NULL, info_log);
	fprintf(stderr, "[MOLSON]: FAILED :: Fragment shader compilation failed. \n");
	fprintf(stderr, "[INFO_LOG]: %s. \n", info_log);
	return 1;
    }
#if VERBOSE == true
    printf("[MOLSON]: Fragment shader compiled successfully. \n");
#endif
    
    _shader->ID = glCreateProgram();
    glAttachShader(_shader->ID, _shader->fragment_shader);
    glAttachShader(_shader->ID, _shader->vertex_shader);
    glLinkProgram(_shader->ID);
    glGetProgramiv(_shader->ID, GL_LINK_STATUS, &success);
    if (!success) {
	glGetProgramInfoLog(_shader->ID, 512, NULL, info_log);
	fprintf(stderr, "[MOLSON]: FAILED :: Shader program linking failed. \n");
	fprintf(stderr, "[INFO_LOG]: %s. \n", info_log);
	return 1;
    }
#if VERBOSE == true
    printf("[MOLSON]: Shader program had been linked successfully. \n");
#endif
    return 0;
    
BLANK:
#if VERBOSE == true
    printf("[MOLSON]: Shader file is blank. \n");
#endif
    if (fragment_code)  fclose(fragment_code);
    else if (vertex_code) fclose(vertex_code);
    _shader->ID = -1;
    return 0;
}

void molson(destroy_shader)(shader *_shader)
{
    glDeleteShader(_shader->fragment_shader);
    glDeleteShader(_shader->vertex_shader);
    glDeleteProgram(_shader->ID);
#if VERBOSE == true
    printf("[MOLSON]: Shaders deleted successfully. \n");
#endif
    return;
}
// --

// -- OpenGL shader use and uniforms setter.
void molson(use_shader)(shader *_shader)
{
    glUseProgram(_shader->ID);
    return;
}

// -- TODO: find a workaround so generics are not used here.
int molson(set_matrix4)(const char *_name, void *_value, bool _use_shader, shader *_shader)
{
    if (_value == NULL) return 1;
    if (_use_shader) {
	glUseProgram(_shader->ID);
    }
    glUniformMatrix4fv(glGetUniformLocation(_shader->ID, _name), 1, false, (float *)_value);
    return 0;
}
// --

int molson(set_vector2_f)(const char *_name, float _value[2], bool _use_shader, shader *_shader)
{
    if (_value == NULL) return 1;
    if (_use_shader) {
	glUseProgram(_shader->ID);
    }
    glUniform2fv(glGetUniformLocation(_shader->ID, _name), 1, _value);
    return 0;
}
int molson(set_vector3_f)(const char *_name, float _value[3], bool _use_shader, shader *_shader)
{
    if (_value == NULL) return 1;
    if (_use_shader) {
	glUseProgram(_shader->ID);
    }
    glUniform3fv(glGetUniformLocation(_shader->ID, _name), 1, _value);
    return 0;
}
int molson(set_vector4_f)(const char *_name, float _value[4], bool _use_shader, shader *_shader)
{
    if (_value == NULL) return 1;
    if (_use_shader) {
	glUseProgram(_shader->ID);
    }
    glUniform4fv(glGetUniformLocation(_shader->ID, _name), 1, _value);
    return 0;
}

int molson(set_float)(const char *_name, float _value, bool _use_shader, shader *_shader)
{
    if (_use_shader) {
	glUseProgram(_shader->ID);
    }
    glUniform1f(glGetUniformLocation(_shader->ID, _name), _value);
    return 0;
}
int molson(set_int)(const char *_name, int _value, bool _use_shader, shader *_shader)
{
    if (_use_shader) {
	glUseProgram(_shader->ID);
    }
    glUniform1i(glGetUniformLocation(_shader->ID, _name), _value);
    return 0;
}
int molson(set_bool)(const char *_name, bool _value, shader *_shader) {
    glUniform1i(glGetUniformLocation(_shader->ID, _name), _value);
    return 0;
}
// --

#endif




