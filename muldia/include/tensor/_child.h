// <tensor/_child.h> header defines a derived class of the _tensor class
// that reprensents the child element of the tensor
//
//

#ifndef TENSOR_CHILD_H
#define TENSOR_CHILD_H

#include <name.h>
#include <tensor/name.h>
#include <tensor/_tensor.h>

namespace _md{
	namespace _ten{
		template<typename T,typename Allocator=std::allocator<T>>
		class _child_tensor : _tensor<T,Allocator>{
			public:
			_child_tensor(){}	
		}; // class _child_tensor : _tensor<T,Allocator>
	} // namespace _ten
} // namespace _md	

#endif // TENSOR_CHILD_H
