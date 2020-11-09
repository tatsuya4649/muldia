// <tensor/_op.h> header that defines the base class that manages the operators
// in the class _tensor,which is the basis of the tensor class.
//
//

#ifndef TENSOR_OP_H
#define TENSOR_OP_H

#include <name.h>
#include <tensor/name.h>
#include <tensor/_tenus.h>

namespace _md{
	namespace _ten{
		class _tensor_operator{
			//
			// base class of _tensor(<tensor/_tensor.h>)
			// * declare a pure virtual function of operator,which is 
			//   an operation required for the tensor class.
			//
			protected:
				// in the tensor class,you must implement a override function
				// (pure virtual function)
				// =========================
				// operator[] to get a tensor one dimension smaller than the current dimension
				/*  user-defined subscript operators can convert shapes,convert
				 *  reserverd memory size,free memory if necessary.
				 */
				virtual _tensor_operator& operator[](subsc_t) & = 0;
				// operator() to get a tensor information
				virtual _tensor_operator& operator()() = 0;
				// operator= to substitute a tensor
				// operator+ to add a tensor
				//virtual _tensor_operator& operator+(int) = 0;
				// operator+ to add a tensor
				//virtual _tensor_operator& operator+(float) = 0;
				// operator+ to add a tensor
				//virtual _tensor_operator& operator+(double) = 0;
				// operator+ to add a tensor
				//virtual _tensor_operator& operator+(unsigned) = 0;
				// operator- to subtract a tensor
				//virtual _tensor_operator& operator-(int) = 0;
				// operator- to subtract a tensor
				//virtual _tensor_operator& operator-(float) = 0;
				// operator- to subtract a tensor
				//virtual _tensor_operator& operator-(double) = 0;
				// operator- to subtract a tensor
				//virtual _tensor_operator& operator-(unsigned) = 0;
				// operator* to multiple a tensor
				//virtual _tensor_operator& operator*(int) = 0;
				// operator* to multiple a tensor
				//virtual _tensor_operator& operator*(float) = 0;
				// operator* to multiple a tensor
				//virtual _tensor_operator& operator*(double) = 0;
				// operator* to multiple a tensor
				//virtual _tensor_operator& operator*(unsigned) = 0;
				// operator/ to divide a tensor
				//virtual _tensor_operator& operator/(int) = 0;
				// operator/ to divide a tensor
				//virtual _tensor_operator& operator/(float) = 0;
				// operator/ to divide a tensor
				//virtual _tensor_operator& operator/(double) = 0;
				// operator/ to divide a tensor
				//virtual _tensor_operator& operator/(unsigned) = 0;
				// operator% to divide a tensor
				//virtual _tensor_operator% operator%(int) = 0;
				// operator% to divide a tensor
				//virtual _tensor_operator% operator%(float) = 0;
				// operator% to divide a tensor
				//virtual _tensor_operator% operator%(double) = 0;
				// operator% to divide a tensor
				//virtual _tensor_operator% operator%(unsigned) = 0;
		}; // class _tensor_operator
	} // namespace _ten
} // namespace _md

#endif // TENSOR_OP_H
