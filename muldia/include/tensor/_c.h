// this file is a header that the base class for declaring and defining methods and
// variables related to child tensors in the _tensor class that is the basis of the tensor.
//
//

#ifndef TENSOR_C_H
#define TENSOR_C_H

#include <name.h>
#include <tensor/name.h>
#include <core/shape.h>
#include <memory>
#include <err/child/have.h>

namespace _md{
	namespace _ten{
		template<typename T,typename Allocator = std::allocator<T>>
		class _tensor_child{
			protected:
				using traits = std::allocator_traits<Allocator>;
				using pointer = typename traits::pointer;
				using size_type = typename Allocator::difference_type;
				// in the tensor class , you must implemnet a override function
				// (pure virtual function)
				// ======================================
				// have_c_tensor() to get whether tensor class has child tensor
				virtual bool have_c_tensor() const noexcept{
					return _c_start_ptr != nullptr;	
				};
				virtual void child_error(){
					if (have_c_tensor()){
						throw err::child_have_error{"don't have child"};
					}
				}
				shape_size_t _c_shp_size() { return _c_shp.size(); }
				// member
				pointer _c_start_ptr = nullptr;
				size_type _c_len = 0;
				_shape _c_shp;
			public:
				// if child tensor, delete
				virtual void child_delete(){
					if (have_c_tensor()){
						_c_start_ptr = nullptr;
						_c_len = 0;
						_c_shp = {};
					}
				}
				pointer c_start_ptr() const noexcept { return _c_start_ptr; }
				_shape c_shp() const noexcept { return _c_shp; }
				size_type c_len() const noexcept { return _c_len; }
		}; // class _tensor_child
	} // namespace _ten
} // namespace _md

#endif // TENSOR_C_H
