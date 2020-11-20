

#ifndef TENSOR_TENSOR_ALLC_IMPL_H
#define TENSOR_TENSOR_ALLC_IMPL_H

namespace _md{
	namespace _ten{

		template<typename T,typename Allocator>
		typename _tensor<T,Allocator>::size_type 
		_tensor<T,Allocator>::cap() const { 
			return _cap;
		}
		
		template<typename T,typename Allocator>
		typename _tensor<T,Allocator>::size_type 
		_tensor<T,Allocator>::len() const{
			return _len;
		}

		template<typename T,typename Allocator>
		bool _tensor<T,Allocator>::empty() const noexcept{
			return !_len;
		}
	} // namespace _ten
} // namespace _md

#endif // TENSOR_TENSOR_ALLC_IMPL_H
