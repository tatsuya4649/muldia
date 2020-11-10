// <err/shape/autocast.h> header that defines a class for notifying an error
// regarding autocast, which is an automatic shape conversion function.
//
//

#ifndef ERR_SHAPE_AUTOCAST_H
#define ERR_SHAPE_AUTOCAST_H

#include <name.h>
#include <err/name.h>
#include <string>

namespace _md{
	namespace _err{
		class shape_autocast_error{
			std::string message;
			public:
			explicit shape_autocast_error(const std::string& what_arg) : message{what_arg}{}
			explicit shape_autocast_error(const char *what_arg) : message{what_arg}{}
			const char *what() const noexcept { return message.c_str(); }
		}; // class shape_autocast_error
	} // namespace _err
} // namespace _md
			

#endif // ERR_SHAPE_AUTOCAST_H
