

#ifndef ERR_SHAPE_SIZE_H
#define ERR_SHAPE_SIZE_H

#include <name.h>
#include <err/name.h>
#include <string>

namespace _md{
	namespace _err{
		class shape_size_error{
			std::string message;
			public:
			explicit shape_size_error(const std::string& what_arg) : message{what_arg}{}
			explicit shape_size_error(const char *what_arg) : message{what_arg}{}
			const char* what() const noexcept { return message.c_str(); }
		}; // class shape_size_error
	} // namespace _err
} // namespace _md


#endif // ERR_SHAPE_SIZE_H
