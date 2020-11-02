// <tensor/_dtype.h> header that declares and defines the base class that handles
// type information in the _tensor class that is the basis of the tensor class.
// 
//

#ifndef _TENSOR_DTYPE_H
#define _TENSOR_DTYPE_H

#include <name.h>
#include <tensor/name.h>
#include <core/dtype.h>
#include <string>

namespace _md{
	namespace _ten{
		using ten_type_name = std::string;
		template<typename T>
		class _tensor_dtype{
			//
			// base class of _tensor (<tensor/_tensor.h>)
			// * to collect variables and methods related to "tensor type information".
			//
			protected:
				_dtype<T> d_type;
				// in the tensor class,you must implement a override function
				// (pure virtual function)
				// ==========================
				// name() to get tensor type name
				virtual ten_type_name name() const = 0;
				// dtype() to show tensor type name
				virtual void dtype() const = 0;
		}; // class _tensor_dtype
	} // namespace _ten
} // namespace _md

#endif // _TENSOR_DTYPE_H
