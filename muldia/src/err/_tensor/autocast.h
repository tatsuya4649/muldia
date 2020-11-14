

#ifndef ERR_TENSOR_AUTOCAST_H
#define ERR_TENSOR_AUTOCAST_H

#include <name.h>
#include <err/name.h>
#include <string>

namespace _md{
	namespace _err{
		class _tensor_autocast_error{
			std::string message;
			public:
			explicit _tensor_autocast_error(const std::string& what_arg) : message{what_arg}{}
			explicit _tensor_autocast_error(const char *what_arg) : message{what_arg}{}
			const char *what(){ return message.c_str(); }
		}; // class _tensor_autocast_error
	} // namespace _err
} // namespace _md

#endif // ERR_TENSOR_AUTOCAST_H
