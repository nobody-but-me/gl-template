
#include <libs/molson.h>
#include <iostream>
#include <memory>
#include <vector>

#include <backend/gl.hpp>
#include <utils/resource_manager.hpp>
#include <common/object.hpp>
#include <utils/log.hpp>

#include <physics/collision.hpp>
#include <common/object.hpp>
#include <utils/input.hpp>
#include <math/math.hpp>

using namespace math::vectors;

namespace application
{
    object*quad;
    // object player, player_hitbox, floor;
    // object circle;
    
    // texture texture,circle_texture;
    
    // static void update_player_sprite_position(void)
    // {
    // 	// player.position = glm::vec2(player_hitbox.position.x - 1.5f, player_hitbox.position.y - 0.5f);
    // 	player.position = vector2(player_hitbox.position.x - 1.5f, player_hitbox.position.y - 0.5f);
    // 	return;
    // }
    
    // constexpr float GRAVITY = 1.0f;
    
    vec2 velocity = vector2(0.0f,0.0f);
    float acceleration = 0.03f;
    float friction = 0.03f;
    float speed = 10.0f;
    
    // bool is_on_floor = false;
    
    void process(double _delta)
    {
	float direction = 0.0f;
	if (utils::input_manager::is_key_pressed(KEY_D))
	{
	    direction = 1.0f;
	}
	else  if (utils::input_manager::is_key_pressed(KEY_A))
	{
	    direction = -1.0f;
	}
	
	if (direction != 0.0f)
	{
	    velocity.x = math::lerp(velocity.x, speed * direction, acceleration);
	}
	else
	{
	    velocity.x = math::lerp(velocity.x, 0.0f, friction);
	}
	quad->position.x += velocity.x * _delta;
	quad->position.y += velocity.y * _delta;
	// update_player_sprite_position();
	
	// bool on_collision = false;
	// if (physics::is_rect_colliding(&player_hitbox,&floor))
	// {
	//     if (velocity.y > 0.0f)
	//     {
	// 	player_hitbox.position.y = floor.position.y - player_hitbox.scale.y;
	//     }
	//     else if (velocity.y < 0.0f)
	//     {
	// 	player_hitbox.position.y = floor.position.y + floor.scale.y;
	// 	is_on_floor = true;
	//     }
	//     velocity.y = 0.0f;
	//     on_collision = true;
	// }
	
	// if (!on_collision)
	// {
	//     velocity.y -= GRAVITY;
	//     is_on_floor= false;
	// }
	// else 
	// {
	//     if (utils::input_manager::is_key_pressed(KEY_UP))
	//     {
	// 	if (is_on_floor==true)
	// 	{
	// 	    velocity.y = 33.0f;
	// 	}
	//     }
	// }
	// player.anim.process();
	return;
    }
    
    void ready(void)
    {
	// void init_texture(std::string _texture_name, std::string _texture_path, bool _alpha,bool _verbose)
	utils::resource_manager::init_texture("texture","../../application/res/sprites/sprite_sheet.png",true);
	
	utils::resource_manager::init_quad("quad",utils::resource_manager::get_texture("texture"));
	quad=utils::resource_manager::get_object("quad");
	
	quad->colour = glm::vec4(255.0f, 0.0f, 0.0f, 255.0f);
	quad->rotation = vector3(0.0f, 0.0f, 0.0f);
	quad->position = vector2(0.0f, 0.0f);
	quad->scale = vector2(4.0f, 4.0f);
	quad->z_index = 0;
	
	quad->create_animation("walking",animation_type::loop,3,{ 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 1 });
	quad->set_cols(8); quad->set_rows(8);
	
	quad->current_animation=quad->get_animation("walking");
	
	// utils::resource_manager::load_texture(&texture, "player_sprite", "../../application/res/sprites/sprite_sheet.png", true);
	// utils::resource_manager::load_texture(&circle_texture,"circle_texture","../../application/res/sprites/m.png",true);
	
	// utils::resource_manager::init_rectangle(&player, "player", &texture);
	
	// utils::resource_manager::init_rectangle(&player_hitbox, "player_hitbox", nullptr);
	// utils::resource_manager::init_rectangle(&floor, "offset", nullptr);
	
	// utils::resource_manager::init_generic(&circle,&circle_texture,object_type::CIRCLE,"circle");
	
	// circle.colour = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
	// circle.rotation = vector3(0.0f, 0.0f, 0.0f);
	// circle.position = vector2(-4.0f, 2.5f);
	// circle.scale = vector2(5.0f, 5.0f);
	// circle.z_index = -5;
	
	// player_hitbox.colour = glm::vec4(255.0f, 0.0f, 0.0f, 0.0f);
	// player_hitbox.rotation = vector3(0.0f, 0.0f, 0.0f);
	// player_hitbox.position = vector2(5.0f, 0.0f);
	// player_hitbox.scale = vector2(2.0f, 4.0f);
	// player_hitbox.z_index = -5;
	
	// player.colour = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
	// player.rotation = vector3(0.0f, 0.0f, 0.0f);
	// player.position = vector2(player_hitbox.position.x - 1.5f, player_hitbox.position.y - 0.5f);
	// player.scale = vector2(5.0f, 5.0f);
	// player.z_index = 0;
	
	// player.animated = true;
	// player.rows  = 8; player.cols  = 8;
	
	// floor.colour = glm::vec4(255.0f, 0.0f, 0.0f, 255.0f);
	// floor.rotation = vector3(0.0f, 0.0f, 0.0f);
	// floor.position = vector2(-4.5f, -4.5f);
	// floor.scale = vector2(15.0f, 2.0f);
	// floor.z_index = 0;
	
	// animation walking;
	// utils::resource_manager::init_animation(&walking , "walking_anim" , animation_type::loop, 3, 0, true);
	// /// NOTE: Are the bellow numbers magic-numbers? Sort of. These are the frame numbers relative to the sprite 
	// ///   sheet loaded by this object. This will be useful when the game engine have a visual animation timeline where
	// /// you will be able to set up the frames visually, just like in game engines like unity and godot, for example.
	// walking.set_frames({ 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 1 });
	// player.animations.push_back(walking);
	// utils::resouce_manager::remove_animation(&walking);
	return;
    }
    
}
