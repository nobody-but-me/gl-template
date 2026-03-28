
#pragma once
#ifndef SINGLETON_HPP
#define SINGLETON_HPP


template <typename T>
class singleton
{
protected:
    singleton() {}
public:
    singleton(const singleton *_singleton) = delete;
    singleton *operator = (const singleton *) = delete;
    
    static T *get_instance()
    {
	static T instance;
	return &instance;
    }
};

#endif//SINGLETON_HPP
