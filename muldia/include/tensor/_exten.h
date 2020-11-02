// <tensor/_exten.h> header that define useful helper functions etc. that are not
// used directly in the tensor_ class.
//
//
#ifndef TENSOR_EXTEN_H
#define TENSOR_EXTEN_H

#include <name.h>
#include <tensor/name.h>
#include <tensor/shape.h>
#include <tensor/_tensor.h>
#include <core/shape.h>
#include <cstddef>

namespace _md{
	namespace _ten{
		// takes a nested initializer_list and dimension number dim_t,
		// computes the shape and returns what created the class shape.
		template<typename T,dim_t I>
		shape& make_shape(nest_init_t<T,I>,dim_t);

		template<typename T,dim_t I>
		std::vector<dim_length> nest_dims(nest_init_t<T,I> t_){
		}

		template<typename T,dim_t I>
		shape& make_shape(nest_init_t<T,I> t_,dim_t d_){
			std::size_t total_size = sizeof(I);
			std::size_t ele_t_size = sizeof(T);
			std::size_t ele_len = total_size / ele_t_size; // element_length	
		}
	}// namespace _ten
}// namespace _md
