
#pragma once
#ifndef MATH_HPP
#define MATH_HPP

namespace math
{
    
    constexpr double PI=3.14159265358979323846264338327950288419716939937510;
    
    namespace delta
    {
	void calculate_delta(void);
	float get_delta_time(void);
	bool is_frametiming(void); // TODO: terrible name;
	void update(void);
    }
    
    namespace vectors
    {
	typedef struct {double x,y,z,w; void zero(void) { this->x = 0.0f; this->y = 0.0f; this->z = 0.0f; this->w = 0.0f; } } dvec4;
	typedef struct {float  x,y,z,w; void zero(void) { this->x = 0.0f; this->y = 0.0f; this->z = 0.0f; this->w = 0.0f; } }  vec4;
	typedef struct {int    x,y,z,w; void zero(void) { this->x = 0; this->y = 0; this->z = 0; this->w = 0; } }             ivec4;
	
	typedef struct {double x,y,z; void zero(void) { this->x = 0.0f; this->y = 0.0f; this->z = 0.0f; } } dvec3;
	typedef struct {float  x,y,z; void zero(void) { this->x = 0.0f; this->y = 0.0f; this->z = 0.0f; } }  vec3;
	typedef struct {int    x,y,z; void zero(void) { this->x = 0; this->y = 0; this->z = 0; } }          ivec3;
	
	typedef struct {double x,y; void zero(void) { this->x = 0.0f; this->y = 0.0f; } } dvec2;
	typedef struct {float  x,y; void zero(void) { this->x = 0.0f; this->y = 0.0f; } }  vec2;
	typedef struct {int    x,y; void zero(void) { this->x = 0;    this->y = 0; }    } ivec2;
	
	dvec2 vector2(double x,double y);
	vec2 vector2(float x,float y);
	ivec2 vector2(int x,int y);
	
	dvec3 vector3(double x,double y,double z);
	vec3 vector3(float x,float y,float z);
	ivec3 vector3(int x,int y,int z);
	
	vec2 add_vec2(vec2 a,vec2 b);
	vec2 sub_vec2(vec2 a,vec2 b);
	vec2 mul_vec2(vec2 a,vec2 b);
	vec2 div_vec2(vec2 a,vec2 b);
	
	ivec2 add_vec2(ivec2 a,ivec2 b);
	ivec2 sub_vec2(ivec2 a,ivec2 b);
	ivec2 mul_vec2(ivec2 a,ivec2 b);
	ivec2 div_vec2(ivec2 a,ivec2 b);
	
	dvec2 add_vec2(dvec2 a,dvec2 b);
	dvec2 sub_vec2(dvec2 a,dvec2 b);
	dvec2 mul_vec2(dvec2 a,dvec2 b);
	dvec2 div_vec2(dvec2 a,dvec2 b);
	
	vec3 add_vec3(vec3 a,vec3 b);
	vec3 sub_vec3(vec3 a,vec3 b);
	vec3 mul_vec3(vec3 a,vec3 b);
	vec3 div_vec3(vec3 a,vec3 b);
	
	ivec3 add_vec3(ivec3 a,ivec3 b);
	ivec3 sub_vec3(ivec3 a,ivec3 b);
	ivec3 mul_vec3(ivec3 a,ivec3 b);
	ivec3 div_vec3(ivec3 a,ivec3 b);
	
	dvec3 add_vec3(dvec3 a,dvec3 b);
	dvec3 sub_vec3(dvec3 a,dvec3 b);
	dvec3 mul_vec3(dvec3 a,dvec3 b);
	dvec3 div_vec3(dvec3 a,dvec3 b);
	
	vec4 add_vec4(vec4 a,vec4 b);
	vec4 sub_vec4(vec4 a,vec4 b);
	vec4 mul_vec4(vec4 a,vec4 b);
	vec4 div_vec4(vec4 a,vec4 b);
	
	ivec4 add_vec4(ivec4 a,ivec4 b);
	ivec4 sub_vec4(ivec4 a,ivec4 b);
	ivec4 mul_vec4(ivec4 a,ivec4 b);
	ivec4 div_vec4(ivec4 a,ivec4 b);
	
	dvec4 add_vec4(dvec4 a,dvec4 b);
	dvec4 sub_vec4(dvec4 a,dvec4 b);
	dvec4 mul_vec4(dvec4 a,dvec4 b);
	dvec4 div_vec4(dvec4 a,dvec4 b);
    }
    
    float lerp(float x, float y, float t); // default lerp function
    
    double lerpd(double x, double y, double t);
    float lerpf(float x, float y, float t);
    int lerpi(int x, int y, int t);
    
    float min(float x, float y); // default min function
    
    double mind(double x, double y);
    float minf(float x, float y);
    int mini(int x, int y);
}

#endif//MATH_HPP
