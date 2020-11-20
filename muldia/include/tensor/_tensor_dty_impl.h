
#ifndef TENSOR_TENSOR_DTY_IMPL_H
#define TENSOR_TENSOR_DTY_IMPL_H

#include "_tensor.h"

namespace _md{
	namespace _ten{
		template<typename T,typename Allocator>
		ten_type_name _tensor<T,Allocator>::name() const{
			return d_type();
		}

		template<typename T,typename Allocator>
		void _tensor<T,Allocator>::dtype() const{
			std::cout << d_type << std::endl;
		}
	} // namespace _ten
} // namespace _md

#endif // TENSOR_TENSOR_DTY_IMPL_H
