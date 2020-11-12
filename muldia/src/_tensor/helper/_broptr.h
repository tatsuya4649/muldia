// <_tensor/helper/_broptr.h> header that defines a class that provides helper function
// for pointers and the number of elements needed for autocast.
//
//

#ifndef HELPER_BROPTR_H
#define HELPER_BROPTR_H

#include <name.h>
#include <tensor/name.h>
#include <_tensor/helper/name.h>
#include <core/shape.h>
#include <numeric>

namespace _md{
	namespace _ten{
		namespace _hel{
			class _autoshape{
				/*  func for autocast
				 *
				 *  receives the pointer of a small tensor with a
				 *  different shape,the number of elements of a tensor
				 *  with a large number of dimensions,and the overall shape.
				 *
				 * 	now_ => tensor dimension shape's subscription
				 * 	small_shp_ => small tensor's shape
				 *
				 *  return number of elements below different dimensions.
				 */
			public:
				static unsigned int s2b(shape_size_t now_,_shape small_shp_){
					std::cout << "s2b()" << std::endl;
					unsigned int res = 1;
					for(auto i=now_;i<small_shp_.ndim();++i){
						res *= small_shp_()[i];
					}
					return res;
				}
				static unsigned int pre_size(shape_size_t idx_,_shape shp_){
					std::cout << idx_ << std::endl;
					std::cout << "pre_size" << std::endl;
					if (idx_ == 0) return 0;
					unsigned int res = 1;
					for(auto i=0;i<idx_-1;++i){
						res *= shp_()[i];
					}
					return res;
				}
			}; // class _autoshape
		} // namespace _hel
	} // namespace _ten
} // namespace _md

#endif // HELPER_BROPTR_H
