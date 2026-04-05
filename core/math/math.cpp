
#include <iostream>

#include <GLFW/glfw3.h>

#include <math/math.hpp>

namespace math
{
    
    namespace delta
    {
	constexpr double MAX_FRAMERATE = 60.0f;
	
	double previous_time = 0.0f;
	double current_time = 0.0f;
	double delta = 1 / MAX_FRAMERATE;
	double updates = 0.0f;
	double time = 0.0f;
	double frame_time;
	
	void calculate_delta(void)
	{
	    previous_time = current_time;
	    current_time = glfwGetTime(); // I really don't like this
	    frame_time = current_time - previous_time;
	}
	float get_delta_time(void)
	{
	    return math::mind(frame_time,delta);
	}
	bool is_frametiming(void)
	{
	    return (frame_time > 0.0f);
	}
	void update(void)
	{
	    float dt = get_delta_time();
	    frame_time -= dt;
	    updates += dt;
	    return;
	}
    }
    
    
    namespace vectors
    {
	dvec2 vector2(double x,double y) { return (dvec2){x, y}; }
	vec2 vector2(float x,float y) { return (vec2){x, y}; }
	ivec2 vector2(int x,int y) { return (ivec2){x, y}; }
	
	dvec3 vector3(double x,double y,double z) { return (dvec3){x, y, z}; }
	vec3 vector3(float x,float y,float z) { return (vec3){x, y, z}; }
	ivec3 vector3(int x,int y,int z) { return (ivec3){x, y, z}; }
	
	vec2 add_vec2(vec2 a,vec2 b) { return vector2(a.x + b.x, a.y + b.y); }
	vec2 sub_vec2(vec2 a,vec2 b) { return vector2(a.x - b.x, a.y - b.y); }
	vec2 mul_vec2(vec2 a,vec2 b) { return vector2(a.x * b.x, a.y * b.y); }
	vec2 div_vec2(vec2 a,vec2 b) { return vector2(a.x / b.x, a.y / b.y); }
	
	ivec2 add_vec2(ivec2 a,ivec2 b) { return vector2(a.x + b.x, a.y + b.y); }
	ivec2 sub_vec2(ivec2 a,ivec2 b) { return vector2(a.x - b.x, a.y - b.y); }
	ivec2 mul_vec2(ivec2 a,ivec2 b) { return vector2(a.x * b.x, a.y * b.y); }
	ivec2 div_vec2(ivec2 a,ivec2 b) { return vector2(a.x / b.x, a.y / b.y); }
	
	dvec2 add_vec2(dvec2 a,dvec2 b) { return vector2(a.x + b.x, a.y + b.y); }
	dvec2 sub_vec2(dvec2 a,dvec2 b) { return vector2(a.x - b.x, a.y - b.y); }
	dvec2 mul_vec2(dvec2 a,dvec2 b) { return vector2(a.x * b.x, a.y * b.y); }
	dvec2 div_vec2(dvec2 a,dvec2 b) { return vector2(a.x / b.x, a.y / b.y); }
	
	vec3 add_vec3(vec3 a,vec3 b) { return vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
	vec3 sub_vec3(vec3 a,vec3 b) { return vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
	vec3 mul_vec3(vec3 a,vec3 b) { return vector3(a.x * b.x, a.y * b.y, a.z * b.z); }
	vec3 div_vec3(vec3 a,vec3 b) { return vector3(a.x / b.x, a.y / b.y, a.z / b.z); }
	
	ivec3 add_vec3(ivec3 a,ivec3 b) { return vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
	ivec3 sub_vec3(ivec3 a,ivec3 b) { return vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
	ivec3 mul_vec3(ivec3 a,ivec3 b) { return vector3(a.x * b.x, a.y * b.y, a.z * b.z); }
	ivec3 div_vec3(ivec3 a,ivec3 b) { return vector3(a.x / b.x, a.y / b.y, a.z / b.z); }
	
	dvec3 add_vec3(dvec3 a,dvec3 b) { return vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
	dvec3 sub_vec3(dvec3 a,dvec3 b) { return vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
	dvec3 mul_vec3(dvec3 a,dvec3 b) { return vector3(a.x * b.x, a.y * b.y, a.z * b.z); }
	dvec3 div_vec3(dvec3 a,dvec3 b) { return vector3(a.x / b.x, a.y / b.y, a.z / b.z); }
    }
    
    
    float lerp(float x, float y, float t) { return (1.0f - t) * x + t * y; }
    
    double lerpd(double x, double y, double t) { return (1.0f - t) * x + t * y; }
    int lerpi(int x, int y, int t)             { return (1 - t) * x + t * y; }
    
    float min(float x, float y) { return (y < x) ? y : x; }
    
    double mind(double x, double y) { return (y < x) ? y : x; }
    int mini(int x, int y)          { return (y < x) ? y : x; }
}
