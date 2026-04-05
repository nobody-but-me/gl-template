
#pragma once
#ifndef LOG_HPP
#define LOG_HPP

#include <string>

namespace utils
{
    namespace log
    {
	// NOTE: this became kinda overwork when there's no colours...
	
	void warning(const char *text, ...);
	void error(const char *text, ...);
	void fatal(const char *text, ...);
	void note(const char *text, ...);
	void todo(const char *text, ...);
	void info(const char *text, ...);
	void log(const char *text, ...);
    }
}

#endif//LOG_HPP
