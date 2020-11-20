

#ifndef TENSOR_TENSOR_SHP_IMPL_H
#define TENSOR_TENSOR_SHP_IMPL_H

#include "_tensor.h"

namespace _md{
	namespace _ten{

		template<typename T,typename Allocator>
		shape_size_t _tensor<T,Allocator>::size() const{
			return _shp.size();
		}

		template<typename T,typename Allocator>
		shape_size_t _tensor<T,Allocator>::ndim() const{
			return _shp.ndim();
		}

		template<typename T,typename Allocator>
		shp_v _tensor<T,Allocator>::shape() const{
			return _shp();
		}

	} // namespace _ten
} // namespace _md

#endif // TENSOR_TENSOR_SHP_IMPL_H

