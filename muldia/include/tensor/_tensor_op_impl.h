

#ifndef TENSOR_TENSOR_OP_IMPL_H
#define TENSOR_TENSOR_OP_IMPL_H

#include "_tensor.h"

namespace _md{
	namespace _ten{

		template<typename T,typename Allocator>
		_tensor<T,Allocator>& _tensor<T,Allocator>::operator()(){
			info();
			return *this;
		}

		template<typename T,typename Allocator>
		_tensor<T,Allocator>& _tensor<T,Allocator>::operator=(const _tensor<T,Allocator>& ten_){
			return copy(ten_);
		}
		
		template<typename T,typename Allocator>
		_tensor<T,Allocator>& _tensor<T,Allocator>::operator=(_tensor<T,Allocator>&& ten_){
			return swap(std::move(ten_));
		}

		template<typename T,typename Allocator>
		void _tensor<T,Allocator>::_have_ptr(){
			if (_ptr==nullptr)
				throw _err::_tensor_operation_error{"must not be _ptr"};
		}
		
		template<typename T,typename Allocator>
		template<typename K>
		void _tensor<T,Allocator>::_op(_op_type e_,K k_){
			_have_ptr();
			eq_type(_ptr,_len,e_,k_);
		}

		template<typename T,typename Allocator>
		template<typename I>
		_tensor<T,Allocator>& _tensor<T,Allocator>::operator+=(I t_){
			_op(_op_type::plus_eq,t_);
			return *this;
		}
		
		template<typename T,typename Allocator>
		template<typename I>
		_tensor<T,Allocator>& _tensor<T,Allocator>::operator-=(I t_){
			_op(_op_type::minus_eq,t_);
			return *this;
		}
		
		template<typename T,typename Allocator>
		template<typename I>
		_tensor<T,Allocator>& _tensor<T,Allocator>::operator*=(I t_){
			_op(_op_type::multi_eq,t_);
			return *this;
		}
		
		template<typename T,typename Allocator>
		_tensor<T,Allocator>& _tensor<T,Allocator>::operator++(){
			_op(_op_type::plus_plus,0);
			return *this;
		}
		
		template<typename T,typename Allocator>
		_tensor<T,Allocator> _tensor<T,Allocator>::operator++(int){
			_tensor<T,Allocator> res = *this;
			++*this;
			return res;
		}
		
		template<typename T,typename Allocator>
		_tensor<T,Allocator>& _tensor<T,Allocator>::operator--(){
			_op(_op_type::minus_minus,0);
			return *this;
		}
		
		template<typename T,typename Allocator>
		_tensor<T,Allocator> _tensor<T,Allocator>::operator--(int){
			_tensor<T,Allocator> res = *this;
			--*this;
			return res;
		}
		
		template<typename T,typename Allocator>
		_tensor<T,Allocator> _tensor<T,Allocator>::operator+(const _tensor<T,Allocator>& ten_){
			typename _tensor<T,Allocator>::ten_pair pair = _hel::autocheck(*this,ten_);
			iterator begin = pair.first.begin();
			iterator end = pair.first.end();
			iterator res = pair.second.begin();
			while(begin!=end){
				*res++ += *begin++;
			}
			return pair.second;
		}
		
		template<typename t,typename allocator>
		_tensor<t,allocator>& _tensor<t,allocator>::operator-(const _tensor<t,allocator>& ten_){
			typename _tensor<t,allocator>::ten_pair pair = _hel::autocheck(*this,ten_);
			iterator begin = pair.first.begin();
			iterator end = pair.first.end();
			iterator res = pair.second.begin();
			while(begin!=end){
				*res++ -= *begin++;
			}
			return *this;
		}
		
		template<typename t,typename allocator>
		_tensor<t,allocator>& _tensor<t,allocator>::operator*(const _tensor<t,allocator>& ten_){
			typename _tensor<t,allocator>::ten_pair pair = _hel::autocheck(*this,ten_);
			iterator begin = pair.first.begin();
			iterator end = pair.first.end();
			iterator res = pair.second.begin();
			while(begin!=end){
				*res++ *= *begin++;
			}
			return *this;
		}
	} // namespace _ten
} // namespace _md

#endif // TENSOR_TENSOR_OP_IMPL_H
