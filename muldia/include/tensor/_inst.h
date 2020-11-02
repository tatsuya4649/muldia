
#ifndef TENSOR_INST_H
#define TENSOR_INST_H

#include <name.h>
#include <cstddef>
#include <iostream>

namespace _md{
	namespace _ten{
		template<typename T,typename... Tail>
		struct inst{
			inst(){
				std::size_t param_size = sizeof...(Tail);
				std::cout << param_size << std::endl;
			}
		};
	} // namespace _ten
} // namespace _md

#endif // TENSOR_INST_H
