//
//
//

#ifndef TENSOR_CONCEPT_H
#define TENSOR_CONCEPT_H

#include <name.h>
#include <tensor/name.h>
#include <type_traits>

namespace _md{
	namespace _ten{
		template<typename T>
		struct _tensor_concept{
			//
			// the type T used in the template argument of the tensor provides
			// an interface to check if the type is as per the concept.
			//
			//  * value_type is able to calculate.
			//  * tensor's value is able to descruct.
			//
			using _arth = std::is_arithmetic<T>;
			using _dest = std::is_destructible<T>;
			static_assert(_arth::value,"_tensor's value_type T must have arithmetic type");
			static_assert(_dest::value,"_tensor's value must be able to destruct");
		}; // struct _tensor_concept
	} // namespace _ten
} // namespace _md

#endif // TENSOR_CONCEPT_H
