//
//


#ifndef TENSOR_PARENT_H
#define TENSOR_PARENT_H

#include <name.h>
#include <tensor/name.h>
#include <tensor/_tensor.h>
#include <type_traits>
#include <tensor/_child_impl.h>

namespace _md{
	namespace _ten{
		template<typename T,typename Allocator=std::allocator<T>>
		class _parent_tensor : public _tensor<T,Allocator>{
			friend class _child_tensor<T,Allocator>;
			public:
			_parent_tensor();
			template<typename U>
			_parent_tensor(std::initializer_list<U>) = delete;
			_parent_tensor(std::initializer_list<T>);
			template<typename... Shape>
			_parent_tensor(Shape...);
			_parent_tensor(std::vector<T>);
			_parent_tensor(const _child_tensor<T,Allocator>);
			~_parent_tensor() = default;
		}; // class _parent_tensor : _tensor<T,Allocator>
	} // namespace _ten
} // namespace _md

#endif // TENSOR_PARENT_H
