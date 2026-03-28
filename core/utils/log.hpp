
#pragma once
#ifndef LOG_HPP
#define LOG_HPP

#include <string>

namespace utils
{
    namespace log
    {
	
	// Don't ask me where I got these values.
	namespace colours {
	    enum colour {
		yellow  = 0x04,
		magenta = 0x06,
		green   = 0x03,
		white   = 0x08,
		black   = 0x01,
		none    = 0x00,
		blue    = 0x05,
		cyan    = 0x07,
		red     = 0x02
	    };
	}
	
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
