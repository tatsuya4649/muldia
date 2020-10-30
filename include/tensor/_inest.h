// <tensor/_inest.h> header is a header for handling a metrix by grouping nested
// initialize_lists.
//

#include <name.h>
#include <initializer_list>
#include <cstddef>
#include <vector>

namespace _md{
	using dim_t = unsigned int;
	using dim_length = unsigned int;
	namespace _ten{
		template<typename T,dim_t I>
		struct nest_init_list{
			using nested_type = typename nest_init_list<T,I-1>::type;
			using type = typename std::vector<nested_type>;
		};
		template<typename T>
		struct nest_init_list<T,0>{
			using type = T;
		};
		template<typename T,dim_t I>
		using nest_init_t = typename nest_init_list<T,I>::type;
	} // namespace _ten
} // namespace _md
