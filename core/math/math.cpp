
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
    
    float lerp(float x, float y, float t) { return (1.0f - t) * x + t * y; }
    
    double lerpd(double x, double y, double t) { return (1.0f - t) * x + t * y; }
    int lerpi(int x, int y, int t)             { return (1 - t) * x + t * y; }
    
    float min(float x, float y) { return (y < x) ? y : x; }
    
    double mind(double x, double y) { return (y < x) ? y : x; }
    int mini(int x, int y)          { return (y < x) ? y : x; }
}
