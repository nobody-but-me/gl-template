
#include <libs/molson.h>
#include <iostream>
#include <vector>

#include <backend/gl.hpp>
#include <utils/resource_manager.hpp>
#include <common/object.hpp>
#include <utils/log.hpp>

#include <physics/collision.hpp>
#include <common/object.hpp>
#include <utils/input.hpp>

namespace application
{
    
    object sprite, sprite2, offset;
    texture texture;
    
    float speed = 4.0f;
    
    void process(double _delta)
    {
		sprite2.position.x += speed * _delta;
		offset.position = sprite2.position;
		if (sprite2.position.x >= 12.0f)
		    sprite2.position.x = -10.0f;
		
		if (math::physics::is_rect_colliding(&sprite2, &sprite))
		    sprite2.colour = glm::vec4(255.0f, 0.0f  , 0.0f  , 255.0f);
		else
		    sprite2.colour = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
		return;
    }
	
    void ready(void)
    {
		utils::resource_manager::load_texture(&texture, "mir", "../../application/res/sprites/sprite_sheet.png", true); // gosh
		
		utils::resource_manager::init_rectangle(&sprite2, "Sprite2", &texture);
		utils::resource_manager::init_rectangle(&sprite, "Sprite", &texture);
		
		utils::resource_manager::init_rectangle(&offset, "Offset", nullptr);
		
		sprite.colour = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
		sprite.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		sprite.position = glm::vec2(5.0f, 0.0f);
		sprite.scale = glm::vec2(5.0f, 5.0f);
		sprite.z_index = 0;
		
		sprite2.colour = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
		sprite2.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		sprite2.position = glm::vec2(-5.0f, 0.0f);
		sprite2.scale = glm::vec2(5.0f, 5.0f);
		sprite2.selected = true;
		sprite2.z_index = 0;
		
		offset.colour = glm::vec4(255.0f, 0.0f, 0.0f, 255.0f);
		offset.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		offset.position = glm::vec2(0.0f, 0.0f);
		offset.scale = sprite2.scale;
		offset.z_index = -10;
		
		sprite2.animated = true; sprite.animated = true;
		sprite2.rows = 8; sprite2.cols = 8;
		sprite.rows  = 8; sprite.cols  = 8;
	
		utils::resource_manager::init_animation(&sprite2.anim, "animation2", animation_type::loop, 5, 0, true );
		utils::resource_manager::init_animation(&sprite.anim , "animation" , animation_type::loop, 3, 0, false);
	
		// NOTE: Are the bellow numbers magic-numbers? Sort of. These are the frame numbers relative to the sprite 
		//   sheet loaded by this object. This will be useful when the game engine have a visual animation timeline where
		// you will be able to set up the frames visually, just like in game engines like unity and godot, for example.
		
		sprite2.anim.set_frames({9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20});
		sprite.anim.set_frames({ 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 1 });
		
		sprite.anim.play();
		return;
    }
    
}
