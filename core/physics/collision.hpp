
#pragma once
#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <common/object.hpp>

namespace physics
{
    
    bool is_rect_horizontally_aligned(object *_object1, object *_object2);
    bool is_rect_vertically_aligned(object *_object1, object *_object2);
    
    bool is_rect_colliding(object *_object1, object *_object2);
    
}

#endif//COLLISION_HPP
