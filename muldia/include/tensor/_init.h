

#ifndef TENSOR_INIT_H
#define TENSOR_INIT_H

#include <name.h>
#include <tensor/name.h>
#include <initializer_list>

namespace _md{
	namespace _ten{
		template<typename T>
		struct tensor_init_list{
			using type = std::initializer_list<T>;
		}; // struct tensor_init_list
	} // namespace _ten
} // namespace _md

#endif // TENOSR_INIT_H
