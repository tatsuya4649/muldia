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
			type _v;
		};
		template<typename T>
		struct nest_init_list<T,0>{
			using type = T;
			type _v;
		};
		template<typename T,dim_t I>
		using nest_init_t = typename nest_init_list<T,I>::type;

		template<typename T,dim_t A>
		struct _nest_v{
			static void re_nest(nest_init_t<T,A> v_,std::vector<T>& ele_v_){
				size_t top_element = v_.size();
				for (auto i=0;i<top_element;++i){
					nest_init_t<T,A-1> res{v_[i]};
					_nest_v<T,A-1>::re_nest(res,ele_v_);
				}
			}
		};
		template<typename T>
		struct _nest_v<T,1>{
			static void re_nest(nest_init_t<T,1> v_,std::vector<T>& ele_v_){
				ele_v_.insert(ele_v_.end(),v_.begin(),v_.end());
			}
		};
		//
		// the nested std::vector(tensor) is diassembled once
		// and stored in the one-dimensional array in the order of the element.
		// note: the resulting one-dimensional array modifies the reference,
		// so there is no return value.
		//
		template<typename T,dim_t A>
		void re_nest(nest_init_t<T,A> v_,std::vector<T>& ele_v_){
			_nest_v<T,A>::re_nest(v_,ele_v_);
		}

	} // namespace _ten
} // namespace _md
