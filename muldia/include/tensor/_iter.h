// <tensor/_iter.h> header that declares and defines the container in the _tensor class,
// which is the basis of the tensor class.
//
//
//

#ifndef TENSOR_ITER_H
#define TENSOR_ITER_H

#include <name.h>
#include <tensor/name.h>
#include <memory>
#include <type_traits>
#include <iterator>

namespace _md{
	namespace _ten{
		template<typename T,typename Allocator = std::allocator<T>>
		class _iterator{
			public:
			using traits = std::allocator_traits<Allocator>;
			using difference_type = int;
			using value_type = T;
			using reference = T&;
			using pointer = typename traits::pointer; 
			using iterator_category = std::random_access_iterator_tag;
			//using tensor = typename _tensor<T,I,Allocator>;
			private:
			T* _p;
			public:
			//------------------------------------------------------
			//		 	constructor
			//------------------------------------------------------
			_iterator()noexcept : _p{nullptr}{}
			_iterator(pointer base_,difference_type index_)noexcept : _p{base_ + index_}{}
			_iterator(const _iterator& i_) : _p{i_._p} {}
			//------------------------------------------------------
			//			operater
			//------------------------------------------------------
			_iterator& operator++(){
				++_p;
				return *this;
			}
			_iterator operator++(int){
				_iterator res = *this;
				++_p;
				return res;
			}
			_iterator operator+(const difference_type& x_) const{
				return _iterator(*this) += x_;
			}
			_iterator& operator+=(const difference_type& x_) const{
				_p += x_;
				return *this;
			}
			_iterator& operator--(){
				--_p;
				return *this;
			}
			_iterator operator--(int){
				_iterator res = *this;
				--_p;
				return res;
			}
			_iterator operator-(const difference_type& x_) const{
				return _iterator(*this) -= x_;
			}
			difference_type operator-(const _iterator& i_) const{
				return _p - i_._p;
			}
			_iterator& operator-=(const difference_type& x_) {
				_p -= x_;
				return *this;
			}
			reference operator*() const{
				return *_p;
			}
			reference operator[](const difference_type& x_) const{
				return *(*this + x_);
			}
			bool operator<(const _iterator& i_) const{
				return _p < i_._p;
			}
			bool operator<=(const _iterator& i_) const{
				return _p <= i_._p;
			}
			bool operator==(const _iterator& i_) const{
				return _p == i_._p;
			}
			bool operator>(const _iterator& i_) const{
				return _p > i_._p;
			}
			bool operator>=(const _iterator& i_) const{
				return _p >= i_._p;
			}
			bool operator!=(const _iterator& i_) const{
				return _p != i_._p;
			}
		}; // class iterator

		template<typename T,typename Allocator = std::allocator<T>>
		class _const_iterator{
			public:
			using traits = std::allocator_traits<Allocator>;
			using difference_type = int;
			using value_type = T;
			using reference = const T&;
			using pointer = typename traits::pointer; 
			using iterator_category = std::random_access_iterator_tag;
			private:
			const T* _p;
			public:
			_const_iterator() noexcept : _p{nullptr} {}
			_const_iterator(pointer base_,difference_type index_) noexcept:_p{base_+index_}{}
			_const_iterator(const _iterator<T,Allocator>& i_) : _p{i_._p} {}
			_const_iterator& operator++(){
				++_p;
				return *this;
			}
			_const_iterator operator++(int){
				_const_iterator res = *this;
				++_p;
				return res;
			}
			_const_iterator operator+(const difference_type& x_) const{
				return _const_iterator(*this) += x_;
			}
			_const_iterator operator+=(const difference_type& x_) {
				_p += x_;
				return *this;
			}
			_const_iterator& operator--(){
				--_p;
				return *this;
			}
			_const_iterator operator--(int){
				_const_iterator res = *this;
				--_p;
				return res;
			}
			_const_iterator operator-(const difference_type& x_) const{
				return _const_iterator(*this) -= x_;
			}
			difference_type operator-(const _const_iterator& i_) const{
				return _p - i_._p;
			}
			_const_iterator& operator-=(const difference_type& x_) const{
				_p -= x_;
				return *this;
			}
			reference operator*() const{
				return *_p;
			}
			reference operator[](const difference_type& x_) const{
				return *(*this+x_);
			}
			bool operator<(const _const_iterator& i_) const{
				return _p < i_._p;
			}
			bool operator<=(const _const_iterator& i_) const{
				return _p <= i_._p;
			}
			bool operator==(const _const_iterator& i_) const{
				return _p == i_._p;
			}
			bool operator>(const _const_iterator& i_) const{
				return _p > i_._p;
			}
			bool operator>=(const _const_iterator& i_) const{
				return _p >= i_._p;
			}
			bool operator!=(const _const_iterator& i_) const{
				return _p != i_._p;
			}
		}; // class _const_iterator
	} // namespace _ten
} // namespace _md

#endif // TENSOR_ITER_H

