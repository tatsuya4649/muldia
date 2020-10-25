// <name.h> header is a header that defines the name of the namespace and
// allows you to use the abbreviated name.
//
#ifndef NAME_H
#define NAME_H

#include <string>

// the abbreviations below allo refer to the same namespace
#define MULDIA muldia
#define MD	muldia
#define _md	muldia
namespace _md{
	extern std::string namespace_; // "muldia"
} // namespace _md

#endif // NAME_H
