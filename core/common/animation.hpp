
#pragma once
#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>

#include <utils/singleton.hpp>
#include <common/enums.hpp>
#include <utils/log.hpp>

class animation: public singleton<animation>
{
    private:
	bool m_initialized = false;
	bool m_is_playing = false;
	bool m_in_reverse = false;
	bool m_autoplay = false;
	bool m_played = false;
	
	std::vector<unsigned int> m_frames;
	unsigned int m_delay_length = 0;
	unsigned int m_delay = 0;
	
	unsigned int m_index = 0;
	unsigned int m_idx = 0;
	
	animation_type m_type;
	
    public:
	std::string name;
	
	bool get_initialized(void) { return this->m_initialized; }
	bool get_is_playing(void)  { return this->m_is_playing; }
	bool get_in_reverse(void)  { return this->m_in_reverse; }
	bool get_autoplay(void)    { return this->m_autoplay; }
	bool get_played(void)      { return this->m_played; }
	
	void set_initialized(bool _new_initialized) { this->m_initialized = _new_initialized; }
	void set_is_playing (bool _new_is_playing)  { this->m_is_playing  = _new_is_playing; }
	void set_in_reverse (bool _new_in_reverse)  { this->m_in_reverse  = _new_in_reverse; }
	void set_autoplay   (bool _new_autoplay)    { this->m_autoplay    = _new_autoplay; }
	void set_played     (bool _new_played)      { this->m_played      = _new_played; }
	
	std::vector<unsigned int> get_frames(void) { return this->m_frames; }
	animation_type get_animation_type(void) { return this->m_type; }
	unsigned int get_delay(void) { return this->m_delay_length; }
	unsigned int get_index(void) { return this->m_index; }
	
	void set_frames(std::vector<unsigned int>_new_frames) { this->m_frames = _new_frames; }
	void set_animation_type(animation_type _new_type)     { this->m_type = _new_type; }
	void set_delay(unsigned int _new_delay)               { this->m_delay_length = _new_delay; }
	void set_index(unsigned int _new_index)               { this->m_index = _new_index; }
	
	void process(void)
	{
	    switch (this->get_animation_type())
	    {
	    case animation_type::ping_pong:
		if (this->m_delay < this->m_delay_length)
		{
		    this->m_delay++;
		}
		else
		{
		    size_t length = this->get_frames().size();
		    
		    this->m_index = this->m_frames[this->m_idx];
		    if (this->get_in_reverse())
		    {
			if (this->m_idx > 0) this->m_idx--;
		    } else
		    {
			if (this->m_idx < static_cast<unsigned int>(length)) this->m_idx++;
		    }
		    
		    if (this->m_idx == static_cast<unsigned int>(length))
		    {
			this->set_in_reverse(true);
		    }
		    else if (this->m_idx == 0)
		    {
			this->set_in_reverse(false);
		    }
		    this->m_delay = 0;
		}
		break;
	    case animation_type::loop:
		if (this->m_delay < this->m_delay_length)
		{
		    this->m_delay++;
		}
		else
		{
		    size_t length = this->get_frames().size();
		    if (this->m_idx < static_cast<unsigned int>(length))
		    {
			this->m_index = this->m_frames[this->m_idx];
			this->m_idx++;
		    }
		    else
		    {
			this->m_index = this->m_frames[0];
			this->m_idx = 0;
		    }
		    this->m_delay = 0;
		}
		break;
	    case animation_type::once:
		if (this->m_delay < this->m_delay_length)
		{
		    this->m_delay++;
		}
		else
		{
		    size_t length = this->get_frames().size();
		    if (this->m_idx < static_cast<unsigned int>(length))
		    {
			this->m_index = this->m_frames[this->m_idx];
			this->m_idx++;
		    }
		    else
		    {
			this->stop();
		    }
		    this->m_delay = 0;
		}
		break;
	    }
	}
	void stop(void) { this->set_is_playing(false); }
	void play(void) { this->set_is_playing(true);  }
};


#endif//ANIMATION_HPP

