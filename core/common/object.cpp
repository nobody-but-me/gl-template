
#include "utils/resource_manager.hpp"
#include "common/animation.hpp"
#include "common/object.hpp"

#include <algorithm>
#include <memory>
#include <vector>

void object::create_animation(std::string _name,animation_type _type,int _delay,std::vector<unsigned int> _frames)
{
    if (this->m_texture==nullptr)
    {
	utils::log::error("can't create animation for object without texture.\n");
	return;
    }
    utils::resource_manager::init_animation(_name,_type,_delay,_frames,true);
    
    animation*anim=utils::resource_manager::get_animation(_name);
    this->m_animations.emplace_back(anim);
    return;
}

animation *object::get_animation(std::string _name)
{
    auto _animation = std::find_if(this->m_animations.begin(), this->m_animations.end(), [&](const animation *anim) { return anim->name == _name; });
    if (_animation != this->m_animations.end())
    {
	utils::log::info("object.cpp::get_animation() : %s animation had been found successfully.\n",_name.c_str());
	return *_animation;
    }
    else
    {
	utils::log::error("object.cpp::get_animation() : %s animation not found.\n",_name.c_str());
	return nullptr;
    }
}
void object::remove_animation(std::string _name)
{
    animation*_animation=object::get_animation(_name);
    if (_animation==nullptr)
    {
	utils::log::error("object.cpp::remove_animation() : Failed to remove %s animation: animation not found.\n",_name.c_str());
	return;
    }
    // this->m_animations.erase(_name);
   this->m_animations.erase(std::remove(this->m_animations.begin(),this->m_animations.end(),_animation),this->m_animations.end());
    
    _animation=object::get_animation(_name);
    if (_animation==nullptr)
    {
	utils::log::info("object.cpp::remove_animation() : %s animation removed successfully.\n",_name.c_str());
	return;
    }
    utils::resource_manager::delete_animation(_name);
    return;
}
