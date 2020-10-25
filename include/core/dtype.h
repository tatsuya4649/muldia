// <core/dtype.h> header is to define a type that can be held
// in multidimensional array defined in muldia.
//
//
//
#ifndef CORE_DTYPE_H
#define CORE_DTYPE_H

#include <name.h>
#include <typeinfo>
#include <string>
#include <iostream>
#include <type_traits>

namespace _md{
	template<typename T>
	class dtype{
			using type = T;
		public:
			constexpr std::string operator()() const { return std::string{typeid(T).name()}; } 
			template<typename D>
			bool operator==(const dtype<D>& d_){ return std::is_same<type,D>::value; }
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os,const dtype<T>& d_){
		return os << d_();
	}	
	
} // _md

#endif // CORE_DTYPE_H
