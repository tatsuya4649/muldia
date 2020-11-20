// <tensor/_child.h> header defines a derived class of the _tensor class
// that reprensents the child element of the tensor
//
//

#ifndef TENSOR_CHILD_H
#define TENSOR_CHILD_H

#include <name.h>
#include <tensor/name.h>
#include <tensor/_tensor.h>
#include <tensor/_tenus.h>
#include <tensor/_parent.h>
#include <algorithm>

namespace _md{
	namespace _ten{
		template<typename T=int,typename Allocator=std::allocator<T>>
		class _child_tensor : public _tensor<T,Allocator>{
			/*
			 * child tensor is a derived class of _tensor created by functions
			 * such as parent tensor's subscript operator and row()
			 * since it is the reference class of the parent tensor,
			 * it is the role to hold the pointer of the parent class.
			 *
			 * note : 
			 *  _child_tensor cannnot change its shape.(since it is a just a
			 *  reference to _parent_tensor,the usable memory range is fixed.)
			 *
			 */
			using pointer = typename _tensor<T,Allocator>::pointer;
			public:
			_child_tensor() = delete;
			_child_tensor(_child_tensor&&) = default;
			_child_tensor& operator=(_child_tensor&&);
			_child_tensor(const _child_tensor&) = default;
			_child_tensor& operator=(const _child_tensor&);
			/*  construnctors based on parent classes and subscripts.
			 */
			template<typename U>
			_child_tensor(const U& par_,subsc_t);
			~_child_tensor()override;
			/* operator[] used when making smaller tensors.
			 */
			_child_tensor operator[](subsc_t);
			private:
			/* constructor used to create a child tensor from the subscripts of the child tensor.
			 * private so that it cannot be used from the outside.
			 */
			_child_tensor(const _child_tensor&,subsc_t);
			/*  
			 *  since the child refers to the pointer of the parent,
			 *  the pointer of the reference destination is deleted (nullptr)
			 *  first when the destructor is called.
			 *  note:otherwise you will release the same pointer twice and it will
			 *  crash.
			 *
			 */
			void child_delete();
		}; // class _child_tensor : _tensor<T,Allocator>
	} // namespace _ten
} // namespace _md	

#endif // TENSOR_CHILD_H
