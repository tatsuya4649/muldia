

#ifndef TENSOR_TENSOR_CON_IMPL_H
#define TENSOR_TENSOR_CON_IMPL_H

#include "_tensor.h"

namespace _md{
	namespace _ten{
		template<typename T,typename Allocator>
		_tensor<T,Allocator>::_tensor(){
			_shp = shp_v{0};
			_ptr = nullptr;
		}
		template<typename T,typename Allocator>
		_tensor<T,Allocator>::_tensor(std::vector<T> t_){
			_shp = shp_v{static_cast<shape_t>(t_.size())};
			size_t n = t_.size();
			while(_cap < n) _cap * EXTENSION_RATE;
			_ptr = _alloc.allocate(_cap);
			for (int i=0;i<n;i++){
				_emplace_back(t_[i]);
			}
		}
		template<typename T,typename Allocator>
		_tensor<T,Allocator>::_tensor(typename tensor_init_list<T>::type l_){
			_shp = shp_v{static_cast<shape_t>(l_.size())};
			size_t n = l_.size();
			while(_cap < n) _cap *= EXTENSION_RATE;
			_ptr = _alloc.allocate(_cap);
			for (int i=0;i<n;i++){
				_emplace_back( *(l_.begin()+i) );
			}
		}
		template<typename T,typename Allocator>
		_tensor<T,Allocator>::_tensor(void* p_,shp_v l_){
			T* ele_p = (T*)p_;
			_shp = l_;
			size_t n = _shp.size();
			while(_cap < n) _cap *= EXTENSION_RATE;
			_ptr = _alloc.allocate(_cap);
			for (int i=0;i<n;i++){
				_emplace_back( *(ele_p + i) );
			}
		}
		template<typename T,typename Allocator>
		template<typename... Shape>
		_tensor<T,Allocator>::_tensor(Shape... shape_){
			_shp = {static_cast<shape_size_t>(shape_)...};
			size_t n = _shp.size();
			while(_cap < n) _cap *= EXTENSION_RATE;
			_ptr = _alloc.allocate(_cap);
			for (int i=0;i<n;i++){
				_emplace_back(0);
			}
		}

		template<typename T,typename Allocator>
		_tensor<T,Allocator>::_tensor(shp_v l_,T value){
			_shp = l_;
			size_t n = _shp.size();
			while(_cap < n) _cap *= EXTENSION_RATE;
			_ptr = _alloc.allocate(_cap);
			for(int i=0;i<n;i++){
				_emplace_back( value );
			}
		}

		template<typename T,typename Allocator>
		_tensor<T,Allocator>::_tensor(pointer p_,_shape shape_){
			_shp = shape_;
			size_t n = _shp.size();
			while(_cap < n) _cap *= EXTENSION_RATE;
			_ptr = _alloc.allocate(_cap);
			for(int i=0;i<n;i++){
				_emplace_back( *(p_+i) );
			}
		}

		template<typename T,typename Allocator>
		_tensor<T,Allocator>::_tensor(const _tensor& ten_){
			while(_cap < ten_._len) _cap *= EXTENSION_RATE;
			_shp = ten_._shp;
			_len = ten_._len;
			d_type = ten_.d_type;
			_ptr = _alloc.allocate(_cap);
			for(int i=0;i<_len;i++){
				traits::construct(_alloc,_ptr+i,*(ten_._ptr+i));
			}
		}

		template<typename T,typename Allocator>
		_tensor<T,Allocator>::_tensor(_tensor&& ten_){
			_cap = ten_._cap;
			_shp = ten_._shp;
			_len = ten_._len;
			d_type = ten_.d_type;
			_ptr = ten_._ptr;
			ten_._ptr = nullptr;
		}
	} // namespace _ten
} // namespace _md

#endif // TENSOR_TENSOR_CON_IMPL_H
