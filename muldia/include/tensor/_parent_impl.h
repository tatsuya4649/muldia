

#ifndef TENSOR_PARENT_IMPL_H
#define TENSOR_PARENT_IMPL_H

#include "_parent.h"

namespace _md{
	namespace _ten{

		template<typename T,typename Allocator>
		_parent_tensor<T,Allocator>::_parent_tensor() : _tensor<T,Allocator>(){}

		template<typename T,typename Allocator>
		_parent_tensor<T,Allocator>::_parent_tensor(std::initializer_list<T> t_)
			: _tensor<T,Allocator>{t_}{}
		
		template<typename T,typename Allocator>
		template<typename... Shape>
		_parent_tensor<T,Allocator>::_parent_tensor(Shape... shape_) :
			_tensor<T,Allocator>(static_cast<shape_size_t>(shape_)...){}

		template<typename T,typename Allocator>
		_parent_tensor<T,Allocator>::_parent_tensor(std::vector<T> t_) :
			_tensor<T,Allocator>{t_}{
		}
		
		template<typename T,typename Allocator>
		_parent_tensor<T,Allocator>::_parent_tensor(const _child_tensor<T,Allocator> c_)
				: _tensor<T,Allocator>{c_}
		{
		}
	} // namespace _ten
} // namespace _md

#endif // TENSOR_PARENT_IMPL_H
