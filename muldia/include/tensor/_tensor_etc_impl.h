

#ifndef TENSOR_TENSOR_ETC_IMPL_H
#define TENSOR_TENSOR_ETC_IMPL_H

#include "_tensor.h"

namespace _md{
	namespace _ten{

		template<typename T,typename Allocator>
		template<typename... Args>
		void _tensor<T,Allocator>::_emplace_back(Args&&... args){
			if (_len==_cap) this->_extension();
			traits::construct(_alloc,_ptr+_len,std::forward<Args>(args)...);
			++_len;
		}

		template<typename T,typename Allocator>
		_tensor<T,Allocator>& _tensor<T,Allocator>::copy(const _tensor<T,Allocator>& ten_){
			if (_shp.size()!=0 and _shp != ten_.shp())
				throw _err::shape_shape_error{"tensor's shape (_shp) and ten_'s tensor's shape (ten_._shp) must have same shape."};
			for (auto i=0;i<_len;i++){
				traits::destroy(_alloc,_ptr+i);
			}
			_alloc.deallocate(_ptr,_cap);
			_cap = 1;
			while(_cap < ten_._cap) _cap*=EXTENSION_RATE;
			_shp = ten_._shp;
			_len = ten_._len;
			d_type = ten_.d_type;
			_ptr = _alloc.allocate(_cap);
			for(auto i=0;i<_len;i++){
				traits::construct(_alloc,_ptr+i,*(ten_._ptr+i));
			}
			return *this;
		}
		
		template<typename T,typename Allocator>
		_tensor<T,Allocator>& _tensor<T,Allocator>::swap(_tensor<T,Allocator>&& ten_){
			if (_shp.size()!=0 and _shp != ten_.shp())
				throw _err::shape_shape_error{"tensor's shape (_shp) and ten_'s tensor's shape (ten_._shp) must have same shape."};
			for (auto i=0;i<_len;i++){
				traits::destroy(_alloc,_ptr+i);
			}
			_alloc.deallocate(_ptr,_cap);
			_alloc = ten_._alloc;
			_shp = ten_._shp;
			_len = ten_._len;
			d_type = ten_.d_type;
			_cap = ten_._cap;
			_ptr = ten_._ptr;
			ten_._ptr = nullptr;
			return *this;
		}
	} // namespace _ten
} // namespace _md

#endif // TENSOR_TENSOR_ETC_IMPL_H
