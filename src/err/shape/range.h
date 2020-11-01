// <src/err/shape/range.h> header that defines class for handling shape errors
//
//

#ifndef ERR_SHAPE_ERROR_H
#define ERR_SHAPE_ERROR_H

#include <name.h>
#include <stdexcept>
#include <string>

namespace _md{
	namespace err{
		class shape_subscript_error{
			std::string message;
			public:
			explicit shape_subscript_error(const std::string& what_arg) : message{what_arg}{}
			explicit shape_subscript_error(const char* what_arg):message{what_arg}{}
			const char* what() const noexcept{
				return "hello";
			}
		}; // class shape_subscript_error
	} // namespace err
} // namespace _md
#endif // ERR_SHAPE_ERROR_H
