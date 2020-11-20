// <tensor/_tenit.h> header to summary the two iterators in <tensor/_iter.h>
// as variables and methods required by the _tensor class.
//
//
//

#ifndef TENSOR_ITER2_H
#define TENSOR_ITER2_H

#include <name.h>
#include <tensor/name.h>
#include <tensor/_tensor.h>
#include <memory>
#include <tensor/_iter.h>
#include <type_traits>
#include <iterator>

namespace _md{
	namespace _ten{
		template <typename T,typename Allocator>
		class _tensor_iter{
			protected:
//				using traits = std::allocator_traits<Allocator>;
//				using difference_type = int;
//				using value_type = T;
//				using reference = T&;
//				using pointer = typename traits::pointer;
//				using size_type = typename Allocator::size_type;
//				using iterator = I::_iterator<T,Allocator>;
//				using const_iterator = I::_const_iterator<T,Allocator>;
//				using iterator_type = typename _iterator<T,Allocator>::value_type;
//				using const_iterator_type = typename _const_iterator<T,Allocator>::value_type;
//				

				using iterator = _iterator<T,Allocator>;
				using const_iterator = _const_iterator<T,Allocator>;
			public:
				virtual iterator begin() noexcept = 0;
				virtual const_iterator begin() const noexcept = 0;
				virtual const_iterator cbegin() const noexcept = 0;
				virtual iterator end() noexcept = 0;
				virtual const_iterator end() const noexcept = 0;
				virtual const_iterator cend() const noexcept = 0;
		}; // class _tensor_iter
	} // namespace _ten
} // namespace _md

#endif // TENSOR_ITER2_H
