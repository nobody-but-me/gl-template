
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
