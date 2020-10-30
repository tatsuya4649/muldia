// <tensor/_tein.h> header that declares and defines a basic information class
// that does not belong to any department in the _tensor class that is the 
// basic of the tensor class.
//
//
//

#ifndef TENSOR_TEIN_H
#define TENSOR_TEIN_H

#include <name.h>
#include <tensor/name.h>
#include <cstddef>

namespace _md{
	namespace _ten{
		using mem_size_t = std::size_t;
		class _tein{
			//
			// base class of _tensor( <tensor/_tensor.h> )
			// * get and display the information you need for a tensor
			//   that doesn't fit anywhere in allocate,shape,dtype
			//
			protected:
				// in the tensor class,you must implement a override function
				// (pure virtual function)
				// ============================
				// mem_size() to get total memory size
				virtual mem_size_t mem_size() const = 0;
				// info() to display all information about tensor classes
				virtual void info() = 0;
				
		}; // class _tein
	} // namespace _ten
} // namespace _md

#endif // TENSOR_TEIN_H
