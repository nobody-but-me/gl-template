
#include <GLFW/glfw3.h>
#include <iostream>

namespace utils
{
    namespace input_manager
    {
	
	GLFWwindow *window;
	
	bool is_key_pressed(int _key)
	{
	    int state = glfwGetKey(window, _key);
	    if (state == GLFW_PRESS) 
	    {
		return true;
	    }
	    return false;
	}
	
	void init(GLFWwindow *_win)
	{
	    window = _win;
	    return;
	};
	
    }
}
