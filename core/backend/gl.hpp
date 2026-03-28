
#pragma once
#ifndef GLFW_INTEGRATION_HPP
#define GLFW_INTEGRATION_HPP

#include <iostream>
#include <string>

#include <common/enums.hpp>
#include <GLFW/glfw3.h>

#define  DEFAULT_WINDOW_WIDTH  800
#define  DEFAULT_WINDOW_HEIGHT DEFAULT_WINDOW_WIDTH/4*3
#define DEFAULT_WINDOW_TITLE   "Prototype"

namespace gl
{
    
    void set_window_mode(const window_mode& _window_mode);
    
    unsigned int get_current_window_height(void);
    unsigned int get_current_window_width(void);
    GLFWwindow* get_current_window(void);
    
    bool is_window_minimized(void);
    bool is_window_focused(void);
    bool is_window_open(void);
    
    void toggle_window_fullscreen(void);
    void force_window_close(void);
    
    int init(const window_mode& _window_mode);
    void destroy(void);
    
    void begin_frame(void);
    void end_frame(void);
    
}

#endif//GLFW_INTEGRATION_HPP
