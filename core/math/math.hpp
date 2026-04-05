
#pragma once
#ifndef MATH_HPP
#define MATH_HPP

namespace math
{
    
    namespace delta
    {
	void calculate_delta(void);
	float get_delta_time(void);
	bool is_frametiming(void); // TODO: terrible name;
	void update(void);
    }
    
    namespace vectors
    {
	typedef struct {double x,y; void zero(void) { this->x = 0.0f; this->y = 0.0f; } } dvec2;
	typedef struct {float  x,y; void zero(void) { this->x = 0.0f; this->y = 0.0f; } }  vec2;
	typedef struct {int    x,y; void zero(void) { this->x = 0;    this->y = 0; }    } ivec2;
	
	typedef struct {double x,y,z;} dvec3;
	typedef struct {float  x,y,z;}  vec3;
	typedef struct {int   x, y,z;} ivec3;
	
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
