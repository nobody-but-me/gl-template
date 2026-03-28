
#include <iostream>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <sstream>

#include <utils/log.hpp>

namespace utils
{
    namespace log
    {
	
	static inline std::string set_colour(colours::colour _foreground = colours::colour::none, colours::colour _background = colours::colour::none)
	{
	    std::stringstream s; s << "\033[";
	    if (!_foreground && ! _background)
	    {
		s << "0";
	    }
	    if (_foreground)
	    {
	        s << 29 + _foreground;
	        if (_background) s << ";";
	    }
	    if (_background)
            {
		s << 39 + _background;
		s << "m";
            }
	    return s.str();
	}
	
	static void message(colours::colour _foreground_colour = colours::colour::none, colours::colour _background_colour = colours::colour::none, const char *_string = "", va_list args = NULL)
	{
	    char token[1000]; int index = 0;
	    for (int i = 0; _string[i] != '\0'; i++)
	    {
	        token[index++] = _string[i];
	        if (_string[i + 1] == '%' || _string[i + 1] == '\0')
		{
		    token[index] = '\0';
		    index = 0;
		    if (token[0] != '%')
		    {
			fprintf(stdout, "%s%s", set_colour(_foreground_colour, _background_colour).c_str(), token);
		    }
		    else
		    {
		        char character_type = 0;
		        int j = 1;

		        while ((character_type = token[j++]) < 58) {}
		        if (character_type == 'i' || character_type == 'd' || character_type == 'u' || character_type == 'h')
			{
			    fprintf(stdout, token, va_arg(args, int));
			}
		        else if (character_type == 'f') fprintf(stdout, token, va_arg(args, double));
		        else if (character_type == 'c') fprintf(stdout, token, va_arg(args, int));
		        else if (character_type == 'l')
			{
			    char ct2 = token[2];
			    
			    if (ct2 == 'u' || ct2 == 'd' || ct2 == 'i')
			    {
				fprintf(stdout, token, va_arg(args, long));
			    }
			    else if (ct2 == 'f')
			    {
				fprintf(stdout, token, va_arg(args, double));
			    }
		        }
		        else if (character_type == 'L')
			{
			    char ct2 = token[2];
			    
			    if (ct2 == 'u' || ct2 == 'd'|| ct2 == 'i')
			    {
				fprintf(stdout, token, va_arg(args, long long));
			    }
			    else if (ct2 == 'f')
			    {
				fprintf(stdout, token, va_arg(args, long double));
			    }
		        }
		        else if (character_type == 's')
			{
			    fprintf(stdout, token, va_arg(args, char*));
			}
		        else
			{
			    fprintf(stdout, "%s", token);
			}
		    }
	        }
	    }
	    fprintf(stdout, "\n%s", set_colour().c_str());
	    return;
	}
	
	void warning(const char *_text, ...)
	{
	    va_list args; va_start(args, _text);
	    const char *warning = "[WARNING] : ";
	    
	    size_t length = strlen(warning) + strlen(_text) + 1;
	    char *new_string = (char*)malloc(length);
	    snprintf(new_string, length, "%s%s", warning, _text);
	    
	    message(colours::colour::yellow, colours::colour::none, new_string, args);
	    free(new_string);
	    va_end(args);
	    return;
	}
	void error(const char *_text, ...)
	{
	    va_list args; va_start(args, _text);
	    const char *error = "[ERROR] : ";
	    
	    size_t length = strlen(error) + strlen(_text) + 1;
	    char *new_string = (char*)malloc(length);
	    snprintf(new_string, length, "%s%s", error, _text);
	    
	    message(colours::colour::red, colours::colour::none, new_string, args);
	    free(new_string);
	    va_end(args);
	    return;
	}
	void fatal(const char *_text, ...)
	{
	    va_list args; va_start(args, _text);
	    const char *fatal = "[FATAL] : ";
	    
	    size_t length = strlen(fatal) + strlen(_text) + 1;
	    char *new_string = (char*)malloc(length);
	    snprintf(new_string, length, "%s%s", fatal, _text);
	    
	    message(colours::colour::black, colours::colour::red, new_string, args);
	    free(new_string);
	    va_end(args);
	    return;
	}
	void note(const char *_text, ...)
	{
	    va_list args; va_start(args, _text);
	    const char *note = "[NOTE] : ";
	    
	    size_t length = strlen(note) + strlen(_text) + 1;
	    char *new_string = (char*)malloc(length);
	    snprintf(new_string, length, "%s%s", note, _text);
	    
	    message(colours::colour::white, colours::colour::none, new_string, args);
	    free(new_string);
	    va_end(args);
	    return;
	}
	void todo(const char *_text, ...)
	{
	    va_list args; va_start(args, _text);
	    const char *todo = "[TODO] : ";
	    
	    size_t length = strlen(todo) + strlen(_text) + 1;
	    char *new_string = (char*)malloc(length);
	    snprintf(new_string, length, "%s%s", todo, _text);
	    
	    message(colours::colour::magenta, colours::colour::none, new_string, args);
	    free(new_string);
	    va_end(args);
	    return;
	}
	void info(const char *_text, ...)
	{
	    va_list args; va_start(args, _text);
	    const char *info = "[INFO] : ";
	    
	    size_t length = strlen(info) + strlen(_text) + 1;
	    char *new_string = (char*)malloc(length);
	    snprintf(new_string, length, "%s%s", info, _text);
	    
	    message(colours::colour::black, colours::colour::none, new_string, args);
	    free(new_string);
	    va_end(args);
	    return;
	}
	void log(const char *_text, ...)
	{
	    va_list args; va_start(args, _text);
	    const char *log = "[LOG] : ";
	    
	    size_t length = strlen(log) + strlen(_text) + 1;
	    char *new_string = (char*)malloc(length);
	    snprintf(new_string, length, "%s%s", log, _text);
	    
	    message(colours::colour::cyan, colours::colour::none, new_string, args);
	    free(new_string);
	    va_end(args);
	    return;
	}
    }
}
