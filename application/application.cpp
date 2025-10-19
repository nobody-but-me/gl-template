
#include <libs/molson.h>
#include <iostream>

#include <backend/glfw_integration.hpp>
#include <utils/resource_manager.hpp>
#include <common/object.hpp>
#include <utils/log.hpp>

#include <physics/collision.hpp>
#include <common/object.hpp>
#include <utils/input.hpp>

namespace Application {
    
    Object sprite, sprite2, offset;
    Texture texture;
    
    float speed = 4.0f;
    
    void process(double delta) {
	sprite2.position.x += speed * delta;
	offset.position = sprite2.position;
	
	if (sprite2.position.x >= 12.0f) sprite2.position.x = -10.0f;

	if (Physics::is_rect_colliding(&sprite2, &sprite)) sprite2.colour = glm::vec4(255.0f, 0.0f  , 0.0f  , 255.0f);
	else                                               sprite2.colour = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
	
	return;
    }
    void ready() {
	ResourceManager::load_texture(&texture, "mir", "../../application/res/sprites/sprite_sheet.png", true);
	
	ResourceManager::init_rectangle(&sprite2, "Sprite2", &texture);
	ResourceManager::init_rectangle(&sprite, "Sprite", &texture);

	ResourceManager::init_rectangle(&offset, "Offset", nullptr);
	
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
	offset.rotation = glm::vec3(0.0f, 0.0f, 45.0f);
	offset.position = glm::vec2(0.0f, 0.0f);
	offset.scale = glm::vec2(0.5f, 0.5f);
	offset.z_index = 10;
	
	sprite2.animated = true; sprite.animated = true;
	sprite2.rows = 8; sprite2.cols = 8;
	sprite.rows  = 8; sprite.cols  = 8;
	
	ResourceManager::init_animation(&sprite2.animation, "animation2", AnimationType::LOOP, 5, 0, true);
	ResourceManager::init_animation(&sprite.animation , "animation" , AnimationType::LOOP, 3, 0, true);
	
	// NOTE: Are the bellow numbers magic-numbers? Sort of. These are the frame numbers relative to the sprite sheet loaded by this object. This will be useful when the game engine have a visual animation timeline where you will be able to set up the frames visually, just like in game engines like unity and godot, for example.
	sprite2.animation.set_frames({9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20});
	sprite.animation.set_frames({ 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 1 });
	
	return;
    }
    
}
