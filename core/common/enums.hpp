
#pragma once
#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <GLFW/glfw3.h>

enum KEYCODES {
    
    BUG_A = GLFW_KEY_A,
    BUG_B = GLFW_KEY_B,
    BUG_C = GLFW_KEY_C,
    BUG_D = GLFW_KEY_D,
    BUG_E = GLFW_KEY_E,
    BUG_F = GLFW_KEY_F,
    BUG_G = GLFW_KEY_G,
    BUG_H = GLFW_KEY_H,
    BUG_I = GLFW_KEY_I,
    BUG_J = GLFW_KEY_J,
    BUG_K = GLFW_KEY_K,
    BUG_L = GLFW_KEY_L,
    BUG_M = GLFW_KEY_M,
    BUG_N = GLFW_KEY_N,
    BUG_O = GLFW_KEY_O,
    BUG_P = GLFW_KEY_P,
    BUG_Q = GLFW_KEY_Q,
    BUG_R = GLFW_KEY_R,
    BUG_S = GLFW_KEY_S,
    BUG_T = GLFW_KEY_T,
    BUG_U = GLFW_KEY_U,
    BUG_V = GLFW_KEY_V,
    BUG_W = GLFW_KEY_W,
    BUG_X = GLFW_KEY_X,
    BUG_Y = GLFW_KEY_Y,
    BUG_Z = GLFW_KEY_Z,
    
    BUG_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
    BUG_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
    
    BUG_RIGHT_CTRL = GLFW_KEY_RIGHT_CONTROL,
    BUG_LEFT_CTRL = GLFW_KEY_LEFT_CONTROL,
    
    BUG_SPACE  = GLFW_KEY_SPACE,
    BUG_ENTER  = GLFW_KEY_ENTER,
    BUG_ESC = GLFW_KEY_ESCAPE,
    
    BUG_RIGHT = GLFW_KEY_RIGHT,
    BUG_LEFT  = GLFW_KEY_LEFT,
    BUG_DOWN  = GLFW_KEY_DOWN,
    BUG_UP    = GLFW_KEY_UP
    
};

enum class ObjectType
{
    TRIANGLE,
    QUAD
};

enum class WindowMode
{
    FULLSCREEN_MODE,
    WINDOWED_MODE
};

#endif//ENUMS_HPP
