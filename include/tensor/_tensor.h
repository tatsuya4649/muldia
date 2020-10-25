// <include/_tensor.h> header that declares and defines the most basic
// and versatile tensor tempalte class of muldia.
//
//
#ifndef TENSOR_H
#define TENSOR_H

#include <name.h>
#include <memory>
#include <type_traits>
#include <tensor/_ctn.h>
#include <tensor/_c_ctn.h>
#include <core/dtype.h>
#include <initializer_list>
#include <core/shape.h>
#include <iostream>
#include <tensor/_inest.h>
#include <tensor/_inst.h>
#include <vector>
#include <cstddef>

namespace _md{
	namespace TEN{
		template<typename T,dim_t I,typename Allocator = std::allocator<T>>
		class tensor_{
			static_assert(std::is_same<T,typename Allocator::value_type>::value,"allocator value type is not matched tensor value type 'T'");
		private:
			using traits = std::allocator_traits<Allocator>;
			using iterator = _container;
			using const_iterator = _const_container;
		public:
			using value_type = T;
			using allocator_type = Allocator;
			using difference_type = typename allocator_type::difference_type;
			using size_type = typename allocator_type::size_type;
			using reference = T&;
			using const_reference = const T&;
			using pointer = typename traits::pointer;
			using const_pointer = typename traits::const_pointer;
			//
			// how to initialize tensor_
			// * tensor_ a{{{a,b,c},{e,d,f}...} => pass a multidimensional array and data type
			// * tensor_ a{std::initializer_list
			//
			tensor_(std::vector<T> t_){}
			tensor_(nest_init_t<T,I> t_){}
		public:
			dtype<T> d_type;
		private:
			//shape _shape;
		}; // tensor_
	}; // TEN
}; // namespace _md

#endif // TENSOR_H
