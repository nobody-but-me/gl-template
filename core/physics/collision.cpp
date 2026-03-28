
#include <iostream>
#include <math.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <physics/collision.hpp>
#include <common/object.hpp>
#include <common/enums.hpp>
#include <utils/log.hpp>

namespace math
{
    namespace physics
    {
	
	bool is_rect_horizontally_aligned(object *_object1, object *_object2);
	bool is_rect_vertically_aligned(object *_object1, object *_object2);
	
	bool is_rect_colliding(object *_object1, object *_object2) {
	    if (_object1->get_type() != object_type::QUAD) {
		utils::log::warning("collision.cpp::is_rect_collidng() : Object 1 is not a rectangle.");
		return false;
	    }
	    if (_object2->get_type() != object_type::QUAD) {
		utils::log::warning("collision.cpp::is_rect_collidng() : Object 2 is not a rectangle.");
		return false;
	    }
	    const float MARGIN = 6.0f;
	    
	    glm::vec2 center1 = {_object1->position.x + _object1->scale.x / 2.0f, _object1->position.y + _object1->scale.y / 2.0f};
	    glm::vec2 center2 = {_object2->position.x + _object2->scale.x / 2.0f, _object2->position.y + _object2->scale.y / 2.0f};
	    
	    glm::vec2 distance = {std::abs(center1.x - center2.x), std::abs(center1.y - center2.y)};
	    glm::vec2 max = {(_object1->scale.x + _object2->scale.x) / 2.0f + MARGIN, (_object1->scale.y + _object2->scale.y) / 2.0f + MARGIN};
	    if (distance.x > max.x || distance.y > max.y)
	    {
		return false;
	    }
	    
	    return (_object1->position.x < _object2->position.x + _object2->scale.x    &&
            _object1->position.x + _object1->scale.x    > _object2->position.x &&
	    _object1->position.y < _object2->position.y + _object2->scale.y    &&
            _object1->position.y + _object1->scale.y    > _object2->position.y  );
	}
	
    }
}
