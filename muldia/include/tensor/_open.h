#ifndef TENSOR_OPEN_H
#define TENSOR_OPEN_H

#include <name.h>
#include <tensor/name.h>

namespace _md{
	namespace _ten{
		enum class _op_type{
			plus_eq,
			minus_eq,
			multi_eq,
			plus_plus,
			minus_minus
		}; // enum class _op_type

		template<typename T,typename K>
		void eq_type(T* ptr_,unsigned int len_,const _op_type& t_,K k_){
			switch (t_){
				case _op_type::plus_eq:
					for (auto i=0;i<len_;++i)
						*(ptr_ + i) += k_;
					break;
				case _op_type::minus_eq:
					for (auto i=0;i<len_;++i)
						*(ptr_ + i) -= k_;
					break;
				case _op_type::multi_eq:
					for (auto i=0;i<len_;++i)
						*(ptr_ + i) *= k_;
					break;
				case _op_type::plus_plus:
					for (auto i=0;i<len_;++i)
						++*(ptr_ + i);
					break;
				case _op_type::minus_minus:
					for (auto i=0;i<len_;++i)
						--*(ptr_ + i);
					break;
			}
		}
	} // namespace _ten
} // namespace _md

#endif // TENSOR_OPEN_H
