// <tensor/_shape.h> header is to declare and define a class that
// holds the basis for the shape in the _tensor class that is the basis of the tensor.
//
//

#ifndef TENSOR_SHAPE_H
#define TENSOR_SHAPE_H

#include <name.h>
#include <tensor/name.h>
#include <core/shape.h>

namespace _md{
	namespace _ten{
		class _tensor_shape{
			//
			// base class of _tensor ( <tensor/_tensor.h> )
			// * to collect variables and methods related to "the shape of the tensor"
			//
			protected:
				// class that holds the shape of _tensor
				_shape _shp;
				// in the tensor class, you must implement a override function
				// (pure virtual function)
				// ==============================
				// size() to get number of tensor element.
				virtual shape_size_t size()  = 0;
				// ndim() to get number of tensor dimension.
				virtual shape_size_t ndim()  = 0;
				// shape() to get vector of tensor shape.
				virtual shp_v        shape() = 0;
		};
	} // namespace _ten
} // namespace _md

#endif // TENSOR_SHAPE_H