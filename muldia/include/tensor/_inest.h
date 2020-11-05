// <tensor/_inest.h> header is a header for handling a metrix by grouping nested
// initialize_lists.
//

#include <name.h>
#include <initializer_list>
#include <cstddef>
#include <vector>
#include <core/shape.h>
#include <tensor/_tenus.h>
#include <numeric>
#include <memory>
#include <type_traits>


namespace _md{
	using dim_t = unsigned int;
	using dim_length = unsigned int;
	namespace _ten{
		template<typename T,dim_t I>
		struct nest_init_list{
			constexpr static const dim_t C = I-1;
			using nested_type = typename nest_init_list<T,C>::type;
			using type = typename std::vector<nested_type>;
		};
		template<typename T>
		struct nest_init_list<T,0>{
			using type = T;
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

		/* 
		 *
		 *  definition of functions and structures required to create and
		 *  return nested multidimensional vectors in order from 1D(scratch)
		 *
		 */
		template<typename T>
		using traits = std::allocator_traits<T>;
		template<typename T>
		using pointer = typename traits<T>::pointer;

		template<typename T,dim_t A,dim_t N,typename Pointer>
		struct _scra_v{
			static void nest_scratch(shp_v shape_vector_,const Pointer& ptr_,nest_init_t<T,N> nest_now_,nest_init_t<T,A-1>& nest_max_){
				shape_t total_element_count =  std::accumulate(shape_vector_.begin(),shape_vector_.end(),1,[](shape_t a,shape_t b){ return a*b; });
				shape_t end_shape = shape_vector_.back();
				nest_init_t<T,N+1> up_dim_vector;
				for(auto i=0;i<(total_element_count/end_shape);++i){
					nest_init_t<T,N> now_dim_vector;
					for(auto j=0;j<end_shape;++j){
						now_dim_vector.push_back(nest_now_[j]);
					}
					up_dim_vector.push_back(now_dim_vector);
				}
				if (shape_vector_.size() >= 1)
					shape_vector_.pop_back();
				// recursion handle
				_scra_v<T,A,N+1,Pointer>::nest_scratch(shape_vector_,ptr_,up_dim_vector,nest_max_);
			}
		}; // struct _scra_v

		template<typename T,dim_t A,typename Pointer>
		struct _scra_v<T,A,0,Pointer>{
			static void nest_scratch(shp_v shape_vector_,const Pointer& ptr_,nest_init_t<T,0> nest_now_,nest_init_t<T,A-1>& nest_max_){
				shape_t total_element_count =  std::accumulate((shape_vector_.begin()+1),shape_vector_.end(),1,[](shape_t a,shape_t b){ return a*b; });
				shape_t end_shape = shape_vector_.back();
				nest_init_t<T,2> two_dim_vector;
				unsigned int ptr_length = end_shape;
				for(auto i=0;i<(total_element_count/end_shape);++i){
					nest_init_t<T,1> one_dim_vector;
					for(auto j=0;j<ptr_length;++j){
						std::cout << *(ptr_+(i*end_shape)+j) << std::endl;
						one_dim_vector.push_back(*(ptr_+(i*end_shape)+j));
					}
					two_dim_vector.push_back(one_dim_vector);
				}
				if (shape_vector_.size() >= 1)
					shape_vector_.pop_back();
				// recursion handle
				_scra_v<T,A,2,Pointer>::nest_scratch(shape_vector_,ptr_,two_dim_vector,nest_max_);
			}
		};

		template<typename T,dim_t A,typename Pointer>
		struct _scra_v<T,A,A,Pointer>{
			static void nest_scratch(shp_v shape_vector_,const Pointer& ptr_,nest_init_t<T,A> nest_now_,nest_init_t<T,A-1>& nest_max_){
				std::cout << nest_now_.size() << std::endl;
			}
		}; // struct _scra_v

		template<typename T,typename Allocator=std::allocator<T>>
		pointer<Allocator> nest_scratch(subsc_t ss_,shp_v shape_vector_,const pointer<Allocator>& ptr_){
			static_assert(std::is_same<T,typename Allocator::value_type>::value,"nest_scratch template type T and type allocator value_type must have same type!");
			shape_t t_dim_ele_number = std::accumulate((shape_vector_.begin()+1),shape_vector_.end(),1,[](shape_t a,shape_t b){ return a*b; });
			subsc_t n_dim_start_index = t_dim_ele_number * ss_;
			pointer<Allocator> n_dim_start_ptr = ptr_ + n_dim_start_index;
			return n_dim_start_ptr;
			//nest_init_t<T,0> _nest_init;
			//_scra_v<T,A,0,pointer<Allocator>>::nest_scratch(shape_vector_,n_dim_start_ptr,_nest_init,nest_);
		}

	} // namespace _ten
} // namespace _md
