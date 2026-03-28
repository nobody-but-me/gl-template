
#pragma once
#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <common/enums.hpp>

namespace backend
{
    
    void force_window_close(void);
    void destroy_application(void);
    
    bool is_window_open(void);
    
    int init(const window_mode& _window_mode);
    
    void begin_frame(void);
    void end_frame(void);
    
    void render(void);
    void loop(void);
    
}


#endif//BACKEND_HPP
