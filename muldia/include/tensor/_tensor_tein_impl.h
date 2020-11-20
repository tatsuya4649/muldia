

#ifndef TENSOR_TENSOR_TEIN_IMPL_H
#define TENSOR_TENSOR_TEIN_IMPL_H

#include "_tensor.h"

namespace _md{
	namespace _ten{
		template<typename T,typename Allocator>
		mem_size_t _tensor<T,Allocator>::mem_size() const{
			return sizeof(*this);
		}
		template<typename T,typename Allocator>
		void _tensor<T,Allocator>::info(){
			std::cout << '\n';
			std::cout << "+----------------- info ----------------+" << std::endl;
			std::cout << "number of element => " << size() << '\n';
			std::cout << "tensor shape => " << shape() << '\n';
			std::cout << "memory consumption size => " <<
				mem_size() * sizeof(char) << "bytes" << '\n';
			std::cout << "memory length => " << len() * 
				sizeof(char) << "bytes" << '\n';
			std::cout << "capacity size => " << cap() *
				sizeof(char) << "bytes" << '\n';
			std::cout << "tensor element type => " << d_type << '\n';
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "=================== value ===============" << std::endl;
			for (unsigned int i=0;i<_len;i++){
				std::cout << *(_ptr+i);
				if (i!=(_len-1)){
					std::cout << " ,";
				}else{
					std::cout << '\n';
				}
			}

			std::vector<int> left_brackets;
			std::vector<int> right_brackets;
			/* i is now dimensions */
			for (unsigned i=0;i<ndim()-1;i++){
				/* get the number of elements in a dimension
				 * smaller than i*/
				unsigned int i_le_el = 1;
				for (unsigned j=i+1;j<ndim();j++){
					i_le_el *= shape()[j];
				}
				
			}

			std::cout << "=========================================" << std::endl;
			std::cout << '\n';
		}

	} // namespace _ten
} // namespace _md


#endif // TENSOR_TENSOR_TEIN_IMPL_H
