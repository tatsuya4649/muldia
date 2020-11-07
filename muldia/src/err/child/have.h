

#ifndef ERR_CHILD_HAVE_H
#define ERR_CHILD_HAVE_H

#include <name.h>
#include <string>

namespace _md{
	namespace err{
		class child_have_error{
			std::string message;
			public:
			explicit child_have_error(const std::string& what_arg) : message{what_arg}{}
			explicit child_have_error(const char *what_arg) : message{what_arg}{}
			const char* what() const noexcept{
				return message.c_str();
			}
		}; // class child_have_error
	} // namespace err
} // namespace _md

#endif // ERR_CHILD_HAVE_H
