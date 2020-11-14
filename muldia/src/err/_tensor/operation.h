

#ifndef ERR_TENSOR_OPERATION_H
#define ERR_TENSOR_OPERATION_H

#include <name.h>
#include <err/name.h>
#include <string>

namespace _md{
	namespace _err{
		class _tensor_operation_error{
			std::string message;
			public:
			explicit _tensor_operation_error(const std::string& what_arg) : message{what_arg}{}
			explicit _tensor_operation_error(const char *what_arg) : message{what_arg}{}
			const char *what() const noexcept{ return message.c_str(); }
		}; // class _tensor_operation_error
	} // namespace _err
} // namespace _md


#endif // ERR_TENSOR_OPERATION_H
