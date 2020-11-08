

#ifndef ERR_SHAPE_SHAPE_H
#define ERR_SHAPE_SHAPE_H

#include <name.h>
#include <err/name.h>
#include <string>

namespace _md{
	namespace _err{
		class shape_shape_error{
			std::string message;
			public:
			explicit shape_shape_error(const std::string& what_arg) : message{what_arg}{}
			explicit shape_shape_error(const char *what_arg) : message{what_arg}{}
			const char* what() const noexcept { return message.c_str(); }
		};
	}// namespace _ten
}// namespace _md
#endif // ERR_SHAPE_SHAPE_H
