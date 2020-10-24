// <core/dtype.h> header is to define a type that can be held
// in multidimensional array defined in muldia.
//
//
//
#ifndef _CORE_DTYPE_H
#define _CORE_DTYPE_H

#include <name.h>
#include <typeinfo>
#include <string>
#include <iostream>
#include <type_traits>

namespace __md{
	template<typename T>
	class dtype{
			using type = T;
		public:
			constexpr std::string operator()() const { return std::string{typeid(T).name()}; } 
			template<typename D>
			bool operator==(const dtype<D>& __d){ return std::is_same<type,D>::value; }
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os,const dtype<T>& __d){
		return os << __d();
	}	
	
} // __md

#endif // _CORE_DTYPE_H
