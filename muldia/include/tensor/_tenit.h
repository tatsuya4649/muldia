// <tensor/_tenit.h> header to summary the two iterators in <tensor/_iter.h>
// as variables and methods required by the _tensor class.
//
//
//

#ifndef TENSOR_ITER2_H
#define TENSOR_ITER2_H

#include <name.h>
#include <tensor/name.h>
#include <memory>
#include <tensor/_iter.h>
#include <type_traits>
#include <iterator>

namespace _md{
	namespace _ten{
		template <typename T,typename Allocator = std::allocator<T>>
		class _tensor_iter : public _iterator<T,Allocator>,public _const_iterator<T,Allocator>{
			protected:
				using traits = std::allocator_traits<Allocator>;
				using difference_type = int;
				using value_type = T;
				using reference = T&;
				using pointer = typename traits::pointer;
				using size_type = typename Allocator::size_type;
				using iterator = _iterator<T,Allocator>;
				using const_iterator = _const_iterator<T,Allocator>;
				using iterator_type = typename _iterator<T,Allocator>::value_type;
				using const_iterator_type = typename _const_iterator<T,Allocator>::value_type;
				static_assert(std::is_same<T,iterator_type>::value,"_tensor_iter pointer and _iterator::pointer must have same type.");
				static_assert(std::is_same<T,const_iterator_type>::value,"_tensor_iter pointer and _const_iterator::pointer must have same type.");
				pointer _base;
				size_type _ilen = 0;
			public:
				virtual iterator begin() noexcept{
					return iterator(_base,0);
				}
				virtual const_iterator begin() const noexcept{
					return const_iterator(_base,0);
				}
				virtual const_iterator cbegin() const noexcept{
					return const_iterator(_base,0);
				}
				virtual iterator end() noexcept{
					return iterator(_base,_ilen);
				}
				virtual const_iterator end() const noexcept{
					return const_iterator(_base,_ilen);
				}
				virtual const_iterator cend() const noexcept{
					return const_iterator(_base,_ilen);
				}
		}; // class _tensor_iter
	} // namespace _ten
} // namespace _md

#endif // TENSOR_ITER2_H
