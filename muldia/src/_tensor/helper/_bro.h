// <_tensor/helper/_bro.h> header declared and defines a helper class that supports
// convenient "autocasts" when calculating using the _tensor class in the
// <tensor/_tensor.h> header,which is a tensor class.
//
//

#ifndef HELPER_BRO_H
#define HELPER_BRO_H

#include <name.h>
#include <tensor/name.h>
#include <_tensor/helper/name.h>
#include <core/shape.h>
#include <err/shape/autocast.h>
#include <memory>
#include <_tensor/helper/_broptr.h>
#include <tensor/_tensor.h>

namespace _md{
	namespace _ten{
		namespace _hel{
			/*  -------------------------------------------------------
			 *  			what is autocast?
			 *  -------------------------------------------------------
			 *   a function that automatically adjusts the shape when
			 *   calculating a tensor and easily supports the calculation.
			 *     
			 *  -> rf : https://numpy.org/doc/stable/user/basics.broadcasting.html 
			 *  
			 *  muldia autocast rules...
			 *
			 *  1. align the number of dimensions
			 *  	
			 *  	if the two tensor have different dimensions,add a new dimension
			 *  	with a size (lenght) of 1 to the beginning of the tensor shape
			 *  	(muldia's shape is _shape(vector<shape_t>) in <core/shape.h>
			 *  	of <tensor/_shape.h>) with smaller number of dimensios
			 *  	to align the dimensions.
			 *
			 *  2. align the size(length) of each dimension
			 *
			 * 	if the dimensions of each dimensions(_shape) of the two tensor do 
			 * 	not match, the dimensions of size 1 is stretched to the size of
			 * 	the dimension of the other tensor (the value are repeated).
			 *	if there is a dimension in which the size of either of the 
			 *	two tensor is not "1",it cannot be autocast and en error occurs.
			 * 
			 * =======================================================================
			 * 
			 *	how apply to tenosr?
			 *	---------------------
			 *
			 *	step0. if two tensor's shape is same, do nothing.
			 *
			 *	step1. add element 1 to the one with the smaller number of
			 *		dimensions (number of elements of shape vector) to
			 *		match the number of dimensions.
			 *
			 *		{0,1,2}  	=>	{{0,1,2}}
			 *		shape : (3)		shape : (1,3)
			 *	
			 *	step2. when comparing the number of elements in each dimension,
			 *		if it is small (one is 1), the number of 1 element is
			 *		repeatedly increased so that the number of elements
			 *		is the same.
			 *
			 *		{{0,1,2}}	=>	{{0,1,2},{0,1,2},{0,1,2}}
			 *		shape : (1,3)		shape : (3,3)
			 *
			 *	step3. calculate
			 *
			 */
			// number of elemets to add when autocasting(magic number) 
			constexpr static const shape_t ADD_DIM = 1;
			constexpr bool NEED_CAST = true;
			constexpr bool NOT_NEED_CAST = false;
			template<typename T>
			struct _autocast{
				/* do tensor need to autocast ? */
				static bool need_cast(const _shape& t1_shp,const _shape& t2_shp)noexcept{
					return (t1_shp != t2_shp) ? NEED_CAST : NOT_NEED_CAST;
				}
				/* check if autocast is required for each tensor  */
				static bool need_cast_tensor(const T& t1_,const T& t2_){
					if (t1_.have_c_tensor()){
						if (t2_.have_c_tensor()){
							if (_autocast<T>::need_cast(t1_.c_shp(),
										t2_.c_shp())){
								return NEED_CAST;
							}else{
								return NOT_NEED_CAST;
							}
						}else{
							if (_autocast<T>::need_cast(t1_.c_shp(),
										t2_.shp())){
								return NEED_CAST;
							}else{
								return NOT_NEED_CAST;
							}
						}
					}else{
						if (t2_.have_c_tensor()){
							if (_autocast<T>::need_cast(t1_.shp(),
										t2_.c_shp())){
								return NEED_CAST;
							}else{
								return NOT_NEED_CAST;
							}
						}else{
							if (_autocast<T>::need_cast(t1_.shp(),
										t2_.shp())){
								return NEED_CAST;
							}else{
								return NOT_NEED_CAST;
							}
						}
					}
				}
				/* if autocast is needed, do the actual conversion */
				static T autocast(const T& t1_,const T& t2_){
					_shape small_shp;
					_shape big_shp;
					T tensor;
					std::cout << t1_.shp().ndim() << std::endl;
					if (t1_.shp().ndim() == t2_.shp().ndim()){
						t1_.shp().size() < t2_.shp().size() ? 
							(small_shp=t1_.shp(),big_shp=t2_.shp(),
							 tensor = t1_) : 
							(big_shp=t1_.shp(),small_shp=t2_.shp(),
							 tensor = t2_);
					}else{
						t1_.shp().ndim() < t2_.shp().ndim() ? 
							(small_shp=t1_.shp(),big_shp=t2_.shp(),
							 tensor = t1_) : 
							(big_shp=t1_.shp(),small_shp=t2_.shp(),
							 tensor = t2_);
					}
					
					/*		step1		*/
					while(small_shp.ndim() != big_shp.ndim()){
						small_shp.push_first(ADD_DIM);
						tensor.reshp().push_first(ADD_DIM);
					}
					tensor.chl2par();
					std::cout << small_shp << std::endl;
					std::cout << tensor.shp() << std::endl;
					/*		step2		*/
					shape_size_t n = small_shp.ndim();
					for (auto i=0;i<n;++i){
						shape_size_t now = (n-1) - i;
						if (small_shp()[now] != big_shp()[now]){
							if (small_shp()[now] != ADD_DIM)
								throw _err::shape_autocast_error{"the number of elements in the autocast tensor must have '1'."};
							/* 
							 * the shapes of small and big each have
							 * the same number of idmensions,and if the
							 * number of elements in each dimensions is
							 * the same of different,small has 1.
							 */
							
							/*  
							 *  TODO: 
							 *  	create a new tensor by indentifying
							 *  	the repeating part of the small
							 *  	tensor from the specified pointer
							 *  	and shape.
							 */

							// repeat for the number of elements
							// in the large tensor
							_autocast<T>::expand_small(tensor,now,big_shp()[now]);
							//for(unsigned int i=0;i<big_shp()[now];++i){
								// start index from _ptr
								//unsigned int index = i*number_ele_now;
								// TODO:
								// copy number_ele_now from index
								// (copy source is 0 to number_ele_now)
							//}
						}
					}
					return tensor;
				}
				/* expand by the required number of iterations of small tensor */
				static void expand_small(T& ten_,unsigned int index_,unsigned int count_){
					/*  
					 *  ten_   => small tensor
					 *  index_ => different dimension's index
					 *  count_ => repeat number
					 */
					// get small tensor's shape number of
					// elements below different dimensions.
					unsigned int number_ele_now = _autoshape::s2b(index_,
							(ten_.have_c_tensor()?ten_.c_shp():ten_.shp()));
					unsigned int pre_size = _autoshape::pre_size(index_,
							(ten_.have_c_tensor()?ten_.c_shp():ten_.shp()));
					std::cout << number_ele_now << std::endl;
					std::cout << pre_size << std::endl;
					/*
					 *  this loop iterates over the number of elements in
					 *  a dimension higher than the current number of dimensions
					 */
					for (unsigned int k=0;k<=pre_size;k++){
						unsigned int start_pre_index = 
							k*count_*number_ele_now;
						/*
						 * this loop repeats the count required for
						 * autocast(the number of elements in big tensor)
						 * and calls it to allocate memory and copy elements
						 */
						for (unsigned int i=0;i<count_;i++){
							// separate processing depending on whether or
							// not ten_ has a child tensor.
							if(ten_.have_c_tensor()){
							}else{
								unsigned int start_index =
							start_pre_index+(i*number_ele_now);
								ten_.insert(start_index,start_pre_index,number_ele_now);
								//for(unsigned int j=0;j<number_ele_now;j++){
								//}	
							}
						}
					}
					if (ten_.have_c_tensor()){
						ten_.c_shp().reshape(index_,count_);
					}else{
						ten_.reshp().reshape(index_,count_);
					}
				}
			}; // class _autocast
		} // namespace _hel
	} // namespace _ten
} // namespace _md

#endif // HELPER_BRO_H
