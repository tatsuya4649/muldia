
#ifndef TENSOR_CHILD_IMPL_H
#define TENSOR_CHILD_IMPL_H

#include "_child.h"

namespace _md{
	namespace _ten{

		template<typename T,typename Allocator>
		_child_tensor<T,Allocator>& _child_tensor<T,Allocator>::operator=(_child_tensor<T,Allocator>&& c_){

		}

		template<typename T,typename Allocator>
		_child_tensor<T,Allocator>& _child_tensor<T,Allocator>::operator=(const _child_tensor<T,Allocator>& c_){

		}

		template<typename T,typename Allocator>
		template<typename U>
		_child_tensor<T,Allocator>::_child_tensor(const U& par_,subsc_t sub_){
			pointer subsc_ptr = nest_scratch<T,Allocator>(sub_,par_.shp()(),this->_ptr);
			_shape subsc_shp = this->shp_subsc(par_._shp,sub_);
			this->_ptr = subsc_ptr;
			this->_shp = subsc_shp;
			this->_len = this->_shp.size();
			this->_cap = this->_len;
		}

		template<typename T,typename Allocator>
		_child_tensor<T,Allocator>::~_child_tensor(){
			child_delete();
		}

		template<typename T,typename Allocator>
		void _child_tensor<T,Allocator>::child_delete(){
			this->_ptr = nullptr;
			this->_len = 0;
			this->_shp = {};
		}


	} // namespace _ten
} // namespace _md
#endif // TENSOR_CHILD_IMPL_H
