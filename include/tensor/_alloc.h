// <tensor/_shape.h> header that declares and defines the class that manages
// memory allocation among _tensor class that is the basis of the tensor class.
//
//

#ifndef TENSOR_ALLOC_H
#define TENSOR_ALLOC_H

#include <name.h>
#include <tensor/name.h>
#include <memory>
#include <type_traits>

namespace _md{
	namespace _ten{
		constexpr const int EXTENSION_RATE = 2;

		template<typename T,typename Allocator = std::allocator<T>>
		class _tensor_alloc{
			//
			// base class of _tensor ( <tensor/_tensor.h> )
			// * to collect variables,using,methods,etc. related to "tensor memory allocation"
			//
			protected:
				static_assert(std::is_same<T,typename Allocator::value_type>::value,"allocator value type is not matched tensor value type 'T'");
				using traits = std::allocator_traits<Allocator>;
				using allocator_type = Allocator;
				using difference_type = typename allocator_type::difference_type;
				using size_type = typename allocator_type::size_type;
				using pointer = typename traits::pointer;
				using const_pointer = typename traits::const_pointer;
				_tensor_alloc(Allocator a_=Allocator()) : _alloc{a_}{}

				// in the tensor class,you must implement a override function
				// (pure virtual function)
				// =============================
				// capa() to get actually reserverd memory size
				virtual size_type cap() const = 0;
				// len() to get memory size used
				virtual size_type len() const = 0;
				// empty() to check whether tensor is empty
				virtual bool empty() const noexcept = 0;
				
				allocator_type _alloc;
				pointer _ptr;				// pointer of tensor
				size_type _cap = 1;
				size_type _len = 0;

				virtual void _extension(){
					pointer ptr = _alloc.allocate(_cap * EXTENSION_RATE);
					for (int i=0;i<_len;++i){
						traits::construct(_alloc,ptr+i,*(ptr+i));
					}
					for (int i=0;i<_len;++i){
						traits::destroy(_alloc,_ptr+i);
					}
					_alloc.deallocate(_ptr,_cap);
					_ptr = ptr;
					_cap *= EXTENSION_RATE;
				}
				virtual void _extension(size_type n){
					size_type r = 1;
					while(n > _cap * r) r *= EXTENSION_RATE;
					if (r == 1) return;
					pointer ptr = _alloc.allocate(_cap*r);
					for(int i=0;i<_len;++i){
						traits::construct(_alloc,ptr+i,*(ptr+i));
					}
					for(int i=0;i<_len;++i){
						traits::destroy(_alloc,_ptr+i);
					}
					_alloc.deallocate(_ptr,_cap);
					_ptr = ptr;
					_cap *= r;
				}
		}; // class tensor_alloc
	} // namespace _ten
} // namespace _md


#endif // TENSOR_ALLOC_H

