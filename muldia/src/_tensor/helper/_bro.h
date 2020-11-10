// <_tensor/helper/_bro.h> header declared and defines a helper class that supports
// convenient "autocasts" when calculating using the _tensor class in the
// <tensor/_tensor.h> header,which is a tensor class.
//
//

#include <name.h>
#include <tensor/name.h>
#include <_tensor/helper/name.h>
#include <core/shape.h>
#include <err/shape/autocast.h>
#include <memory>

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
			template<typename T,typename Allocator=std::allocator<T>>
			struct _autocast{
				using traits = std::allocator_traits<Allocator>;
				using pointer = typename traits::pointer;
				/* do tensor need to autocast ? */
				static bool need_cast(const _shape& t1_shp,const _shape& t2_shp) noexcept{
					return (t1_shp != t2_shp) ? true : false;
				}
				/* if autocast is needed, do the actual conversion */
				static void autocast(const _shape& t1_shp,pointer t1_ptr,const _shape& t2_shp,pointer t2_ptr){
					_shape small_shp;
					_shape big_shp;
					t1_shp.ndim() < t2_shp.ndim() ? 
						(small_shp=t1_shp,big_shp=t2_shp) : 
						(big_shp=t1_shp,small_shp=t2_shp);
					std::cout << small_shp << std::endl;	
					std::cout << big_shp << std::endl;
					/*		step1		*/
					while(small_shp.ndim() != big_shp.ndim()){
						small_shp.push_first(ADD_DIM);
					}
					std::cout << small_shp << std::endl;
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
							std::cout << big_shp()[now] << std::endl;
							std::cout << small_shp()[now] << std::endl;
						}
					}
				}
			}; // class _autocast
		} // namespace _hel
	} // namespace _ten
} // namespace _md

