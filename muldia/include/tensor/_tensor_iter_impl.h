

#ifndef TENSOR_TENSOR_ITER_IMPL_H
#define TENSOR_TENSOR_ITER_IMPL_H

#include "_tensor.h"

namespace _md{
	namespace _ten{

		template<typename T,typename Allocator>
		typename _tensor<T,Allocator>::iterator _tensor<T,Allocator>::begin() noexcept{
			return iterator(_ptr,0);
		}

		template<typename T,typename Allocator>
		typename _tensor<T,Allocator>::const_iterator _tensor<T,Allocator>::begin() const noexcept{
			return const_iterator(_ptr,0);
		}
		
		template<typename T,typename Allocator>
		typename _tensor<T,Allocator>::const_iterator _tensor<T,Allocator>::cbegin() const noexcept{
			return const_iterator(_ptr,0);
		}
		
		template<typename T,typename Allocator>
		typename _tensor<T,Allocator>::iterator _tensor<T,Allocator>::end() noexcept{
			return iterator(_ptr,_len);
		}
		
		template<typename T,typename Allocator>
		typename _tensor<T,Allocator>::const_iterator _tensor<T,Allocator>::end() const noexcept{
			return const_iterator(_ptr,_len);
		}
		
		template<typename T,typename Allocator>
		typename _tensor<T,Allocator>::const_iterator _tensor<T,Allocator>::cend() const noexcept{
			return const_iterator(_ptr,_len);
		}
	} // namespace _ten
} // namespace _md


#endif // TENSOR_TENSOR_ITER_IMPL_H
