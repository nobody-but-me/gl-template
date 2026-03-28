
#include <iostream>
#include <backend/backend.hpp>

int main(int argc, char *argv[])
{
    if ((backend::init(window_mode::windowed_mode)) == -1)
    {
	return -1;
    }
    
    while (backend::is_window_open())
    {
	backend::loop();
    }
    
    backend::destroy_application();
    return 0;
}
