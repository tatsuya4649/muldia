// <include/_tensor.h> header that declares and defines the most basic
// and versatile tensor tempalte class of muldia.
//
//
#ifndef TENSOR_TENSOR_H_
#define TENSOR_TENSOR_H_

#include <name.h>
#include <tensor/name.h>
#include <memory>
#include <type_traits>
#include <tensor/_ctn.h>
#include <tensor/_c_ctn.h>
#include <core/dtype.h>
#include <initializer_list>
#include <core/shape.h>
#include <iostream>
#include <tensor/_inest.h>
#include <tensor/_inst.h>
#include <vector>
#include <cstddef>
#include <utility>
#include <tensor/_shape.h>
#include <tensor/_alloc.h>
#include <tensor/_dty.h>
#include <tensor/_tein.h>
#include <tensor/_tenit.h>
#include <tensor/_tenus.h>
#include <tensor/_op.h>
#include <tensor/_c.h>
#include <err/shape/shape.h>
#include <err/_tensor/operation.h>
#include <tensor/_concept.h>
#include <tensor/_open.h>
#include <algorithm>
#include <_tensor/helper/_bro.h>
#include <_tensor/helper/_broptr.h>
#include <_tensor/helper/_op.h>
#include <tensor/_init.h>

namespace _md{
	namespace _ten{
		template<typename T = int,typename Allocator = std::allocator<T>>
		class _tensor : public _tein,
				public _tensor_shape,
				public _tensor_alloc<T,Allocator>,
				public _tensor_dtype<T>,
				public _tensor_operator,
				public _tensor_concept<T>,
				public _hel::_autocast<_tensor<T,Allocator>>,
				public _tensor_iter<T,Allocator>{	
			//
			// a low-level tensor class shared by all high-level tensor
			// classes defined in muldia.
			//
			// .........................................................
			// 			all parameteras
			// .........................................................
			// * _shape _shp => the shape of _tensor
			// * Allocator _alloc => to allocate memory(default : std::allocator<T>)
			// * pointer _ptr => std::allocator_traits<Allocator>'s pointer
			// * size_type _cap => reserved memory size
			// * size_type _len => used memory size
		protected:
			using _tensor_alloc<T,Allocator>::_len;
			using _tensor_alloc<T,Allocator>::_cap;
			using _tensor_alloc<T,Allocator>::_alloc;
			using _tensor_alloc<T,Allocator>::_ptr;
			using typename _tensor_alloc<T,Allocator>::pointer;
		public:
			using const_reference = const T&;
			// --------------------------------------------------
			//			constructor
			// --------------------------------------------------
			//
			// how to initialize tensor_
			// * _tensor a{a,b,c,d,e,f} => pass a std::vector<T>)
			// * _tensor a{a,b,c,d,e,f} => pass a std::initializer_list<T>)
			// * _tensor a{{a,b,c},{a,b,v},{2,3}} => pass void* and shp_v
			// * _tensor a{{a,b,c},{a,b,v},{2,3}} => pass nested std::vector<T> and shp_v
			// * _tensor a{{1,2,3},0} => pass shp_v and value(=0)
			//
			_tensor();
			/*
			 * the values stored in std::vector<T> are stored
			 * in memory in order from the _ptr pointer.
			 * note: do not consider the shape.
			 */
			_tensor(std::vector<T> t_);
			/* 
			 * the values stored in std::initializer_list<T> are stored
			 * in memory in order from the _ptr pointer.
			 * note: do not consider the shape.
			 */
			_tensor(typename tensor_init_list<T>::type);
			//_tensor(nest_init_t<T,I> v_,shp_v l_){
				// disassemble the nested n-dimensional std::vector,
				// convert it to a linear array vector,and then allocate memory.
				//std::vector<T> total_v;
				//re_nest<T,I>(v_,total_v);
				//_shp = _shape{l_};
				//while(_cap < total_v.size()) _cap *= EXTENSION_RATE;
				//_ptr = _alloc.allocate(_cap);
				//this->_base = this->_ptr;
				//for (int i=0;i<total_v.size();++i){
				//	_emplace_back(total_v[i]);
				//}
			//}

			/* 
			 * the value of void* is stored in the memory for the
			 * number of elements in order from the _ptr pointer.
			 */
			_tensor(void*,shp_v);
			template<typename... Shape>
			_tensor(Shape...);
			/* 
			 * with _ptr pointer as the starting point,allocate memory
			 * for the number of elements based on the shape and
			 * store value.
			 */
			_tensor(shp_v,T=0);
			_tensor(pointer,_shape);
			_tensor(const _tensor& ten_);
			_tensor(_tensor&& ten_);
			~_tensor()override;
			// --------------------------------------------------
			//			shape
			// --------------------------------------------------
			/*
			 * return the total number of tensor's elementes
			 */
			shape_size_t size()  const override;
			/*
			 * return the dimension of tensor
			 */
			shape_size_t ndim()  const override;
			/*
			 * return the shape vector.
			 * shp_v => std::vector<shape_t>
			 */
			shp_v	     shape() const override;
			using _tensor_shape::shp_subsc;
			using _tensor_shape::shp;
			// --------------------------------------------------
			//			allocate
			// --------------------------------------------------
			using typename _tensor_alloc<T,Allocator>::traits;
			using typename _tensor_alloc<T,Allocator>::size_type;
			/*
			 * return memory size reserverd by the tensor.
			 */
			size_type cap() const override;
			/*
			 * return memory size actually used by the tensor.
			 */
			size_type len() const override;
			/*
			 * return true if the tensor is empty,false otherwise.
			 */
			bool empty() const noexcept override;
			//---------------------------------------------------
			//			dtype
			//---------------------------------------------------
			using _tensor_dtype<T>::d_type;
			/*
			 * return the type of the tensor element.
			 * te_type_name is alias for std::string.
			 */
			ten_type_name name() const override;
			/*
			 * display the type of the tensor element.
			 */
			void dtype() const override;
			//---------------------------------------------------
			//			tein
			//---------------------------------------------------
			/*
			 * get _tensor total memory size
			 */
			mem_size_t mem_size() const override;
			/* 
			 * display _tensor various information 
			 */
			void info() override;
			//---------------------------------------------------
			//			iterator
			//---------------------------------------------------
			/*
			 *  function required when using a tensor
			 *  as an iterator
			 */
			using iterator = _iterator<T,Allocator>;
			using const_iterator = _const_iterator<T,Allocator>;
			/*
			 *  return an "iterator" to the first element when the
			 *  tensor is an iterator.
			 */
			iterator begin() noexcept override;
			/*
			 *  return an "const_iterator" to the first element when the
			 *  tensor is an iterator.
			 */
			const_iterator begin() const noexcept override;
			/*
			 *  return an "const_iterator" to the first element when the
			 *  tensor is an iterator.
			 */
			const_iterator cbegin() const noexcept override;
			/*
			 *  return an "iterator" to the last element when the
			 *  tensor is an iterator.
			 */
			iterator end() noexcept override;
			/*
			 *  return an "const_iterator" to the last element when the
			 *  tensor is an iterator.
			 */
			const_iterator end() const noexcept override;
			/*
			 *  return an "const_iterator" to the last element when the
			 *  tensor is an iterator.
			 */
			const_iterator cend() const noexcept override;
			//---------------------------------------------------
			//			operator
			//---------------------------------------------------
			/*
			 * info() and return tensor itself
			 */
			_tensor<T,Allocator>& operator()() override;
			/*
			 * substitute another tensor
			 */
			_tensor<T,Allocator>& operator=(const _tensor<T,Allocator>&);
			/*
			 * move another tensor to tensor itself
			 */
			_tensor<T,Allocator>& operator=(_tensor<T,Allocator>&& ten_);
			//_tensor<T,Allocator>& operator[](subsc_t sb_) = 0;
			/*
			 * if there is no pointer to the first element of the
			 * tensor, it will give an error
			 */
			void _have_ptr();
			/*
			 * test _have_ptr() and, perform the corresponding processing
			 * in order from the first pointer according to the operator.
			 */
			template<typename K>
			void _op(_op_type,K);
			/*
			 * calculation with arthmetic type
			 */
			template<typename I>
			_tensor<T,Allocator>& operator+=(I);
			template<typename I>
			_tensor<T,Allocator>& operator-=(I);
			template<typename I>
			_tensor<T,Allocator>& operator*=(I);
			_tensor<T,Allocator>& operator++();
			_tensor<T,Allocator> operator++(int);
			_tensor<T,Allocator>& operator--();
			_tensor<T,Allocator> operator--(int);
			using ten_pair = std::pair<_tensor<T,Allocator>,_tensor<T,Allocator>>;
			/*
			 *  use the autocast function for tensor-to-tensor
			 *  calculations
			 */
			_tensor<T,Allocator> operator+(const _tensor<T,Allocator>&);
			_tensor<T,Allocator>& operator-(const _tensor<T,Allocator>&);
			_tensor<T,Allocator>& operator*(const _tensor<T,Allocator>& ten_);
			//---------------------------------------------------
			//			etc.	
			//---------------------------------------------------
		private:
			/*
			 * embed values in memory based on the arguments
			 * passed based on _ptr and _len
			 */
			template<typename... Args>
			void _emplace_back(Args&&...);
			/*
			 * copy between tensors
			 */
			_tensor<T,Allocator>& copy(const _tensor<T,Allocator>&);
			/*
			 * move between tensors
			 */
			_tensor<T,Allocator>& swap(_tensor<T,Allocator>&&);
		}; // _tensor

	}; // _ten
}; // namespace _md

#endif // TENSOR_TENSOR_H_
