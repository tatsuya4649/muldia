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
	class _dtype{
			using type = T;
			using type_name = std::string;
		public:
			_dtype() : _name{ type_name{typeid(T).name()} } {}
			constexpr std::string operator()() const { return std::string{typeid(T).name()}; } 
			template<typename D>
			bool operator==(const _dtype<D>& d_){ return std::is_same<type,D>::value; }
			type_name name() const noexcept { return _name; }
		private:
			type_name _name;
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os,const _dtype<T>& d_){
		return os << d_();
	}	
	
} // _md

#endif // CORE_DTYPE_H
