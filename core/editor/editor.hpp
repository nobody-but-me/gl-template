
#pragma once
#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <GLFW/glfw3.h>

namespace editor
{
    
    void init(GLFWwindow *_window);
    void destroy(void);
    void render(void);
    
}

#endif//EDITOR_HPP
