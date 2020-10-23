// <name.h> header is a header that defines the name of the namespace and
// allows you to use the abbreviated name.
//
#ifndef _NAME_H
#define _NAME_H

#include <string>

// the abbreviations below allo refer to the same namespace
#define __MULDIA muldia
#define __MD	muldia
#define __md	muldia
namespace __md{
	extern std::string __namespace__; // "muldia"
} // namespace __md

#endif // _NAME_H
