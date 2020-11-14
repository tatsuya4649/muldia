


#ifndef HELPER_OP_H
#define HELPER_OP_H

#include <name.h>
#include <tensor/name.h>
#include <_tensor/helper/name.h>
#include <utility>
#include <err/_tensor/operation.h>
#include <_tensor/helper/_bro.h>

namespace _md{
	namespace _ten{
		namespace _hel{
			/* helper function that collectively performs operations
			 * required for autocast(autocast & constraint check)
			 */
			template<typename T>
			std::pair<T,T> autocheck(T ten1_,T ten2_){
				std::pair<T,T> _pair = autocast(ten1_,ten2_);
				ope_concept(_pair.first,_pair.second);
				return _pair;
			}
			/*  a helper function that summarizes the items to be checked
			 *  when performing calculations between _tensors as a function.
			 *  so T = _tensor<T,Allocator>
			 */
			template<typename T>
			void ope_concept(const T& ten1_,const T& ten2_){
				if (ten1_.have_c_tensor())
					throw _err::_tensor_operation_error{"the operation between tensors must not have child tensor."};
				if (ten2_.have_c_tensor())
					throw _err::_tensor_operation_error{"the operation between tensors must not have child tensor."};
				if (ten1_.size()!=ten2_.size())
					throw _err::_tensor_operation_error{"the operation between tensors must have the same number of elements"};
				if (ten1_.ndim()!=ten2_.ndim())
					throw _err::_tensor_operation_error{"the operation between tensors must have the same dimensions"};
				if (ten1_.shp()!=ten2_.shp())
					throw _err::_tensor_operation_error{"the operation between tensors must have the same shape"};
			}

			/* a helper function that performs troublesome autocast
			 * (automatic shape conversion) when calculating between tensors
			 */
			template<typename T>
			std::pair<T,T> autocast(T ten1_,T ten2_){
				if (ten1_.have_c_tensor())
					ten1_.chl2par();
				if (ten2_.have_c_tensor())
					ten2_.chl2par();
				if (_autocast<T>::need_cast_tensor(ten1_,ten2_)){
					return _autocast<T>::autocast(ten1_,ten2_);
				}else{
					return std::pair<T,T>{ten1_,ten2_};
				}
			}

			/*
			 * TODO:
			 * the calculation is performed based on the passed type function
			 * and the pointer of the tensor.
			 *
			 */
		} // namespace _hel
	} // namespace _ten
} // namespace _md

#endif // HELPER_OP_H
