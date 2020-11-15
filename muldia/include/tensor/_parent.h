//
//


#ifndef TENSOR_PARENT_H
#define TENSOR_PARENT_H

#include <name.h>
#include <tensor/name.h>
#include <tensor/_tensor.h>

namespace _md{
	namespace _ten{
		template<typename T,typename Allocator=std::allocator<T>>
		class _parent_tensor : _tensor<T,Allocator>{
			public:
			_parent_tensor() : _tensor<T,Allocator>(){}
		}; // class _parent_tensor : _tensor<T,Allocator>
	} // namespace _ten
} // namespace _md

#endif // TENSOR_PARENT_H
