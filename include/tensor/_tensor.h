// <include/_tensor.h> header that declares and defines the most basic
// and versatile tensor tempalte class of muldia.
//
//
#ifndef TENSOR_H
#define TENSOR_H

#include <name.h>
#include <tensor/name.h>
#include <memory>
#include <type_traits>
#include <tensor/_ctn.h>
#include <tensor/_c_ctn.h>
#include <core/dtype.h>
#include <initializer_list>
#include <core/shape.h>
#include <iostream>
#include <tensor/_inest.h>
#include <tensor/_inst.h>
#include <vector>
#include <cstddef>
#include <utility>
#include <tensor/_shape.h>
#include <tensor/_alloc.h>
#include <tensor/_dty.h>
#include <tensor/_tein.h>
#include <tensor/_tenit.h>
#include <tensor/_tenus.h>

namespace _md{
	namespace _ten{
		template<typename T,dim_t I=1,typename Allocator = std::allocator<T>>
		class _tensor : public _tein,public _tensor_shape, public _tensor_alloc<T,Allocator>,public _tensor_dtype<T>,public _tensor_iter<T,Allocator>{
			//
			// a low-level tensor class shared by all high-level tensor
			// classes defined in muldia.
			//
		private:
			using _tensor_alloc<T,Allocator>::_len;
			using _tensor_alloc<T,Allocator>::_cap;
			using _tensor_alloc<T,Allocator>::_alloc;
			using _tensor_alloc<T,Allocator>::_ptr;
		public:
			using const_reference = const T&;
			// --------------------------------------------------
			//			constructor
			// --------------------------------------------------
			//
			// how to initialize tensor_
			// * _tensor a{a,b,c,d,e,f} => pass a std::vector<T>)
			// * _tensor a{a,b,c,d,e,f} => pass a std::initializer_list<T>)
			// * _tensor a{{a,b,c},{a,b,v},{2,3}} => pass void* and shp_v
			// * _tensor a{{a,b,c},{a,b,v},{2,3}} => pass nested std::vector<T> and shp_v
			// * _tensor a{{1,2,3},0} => pass shp_v and value(=0)
			//
			_tensor() = delete;
			_tensor(std::vector<T> t_) {
				// the values stored in std::vector<T> are stored
				// in memory in order from the _ptr pointer.
				// note: do not consider the shape.
				_shp = shp_v{static_cast<shape_t>(t_.size())};
				size_t n = t_.size();
				while(_cap < n) _cap *= EXTENSION_RATE;
				this->_ptr = _alloc.allocate(_cap);
				this->_base = this->_ptr;
				for (int i=0;i<n;++i){
					_emplace_back(t_[i]);
				}
			}
			_tensor(std::initializer_list<T> l_){
				// the values stored in std::initializer_list<T> are stored
				// in memory in order from the _ptr pointer.
				// note: do not consider the shape.
				_shp = shp_v{static_cast<shape_t>(l_.size())};
				size_t n = l_.size();
				while(_cap < n) _cap *= EXTENSION_RATE;
				_ptr = _alloc.allocate(_cap);
				this->_base = this->_ptr;
				for (int i=0;i<n;++i){
					_emplace_back( *(l_.begin() + i) );
				}
			}
			_tensor(nest_init_t<T,I> v_,shp_v l_){
				// disassemble the nested n-dimensional std::vector,
				// convert it to a linear array vector,and then allocate memory.
				std::vector<T> total_v;
				re_nest<T,I>(v_,total_v);
				_shp = _shape{l_};
				for(auto i=0;i<total_v.size();++i){
					std::cout << total_v[i] << std::endl;
				}
			}
			_tensor(void* p_,shp_v l_){
				// the value of void* is stored in the memory for the
				// number of elements in order from the _ptr pointer.
				T* ele_p = (T*)p_;
				_shp = l_;
				size_t n = _shp.size();
				while(_cap < n) _cap *= EXTENSION_RATE;
				_ptr = _alloc.allocate(_cap);
				this->_base = this->_ptr;
				for (int i=0;i<n;++i){
					_emplace_back( *(ele_p + i) );
				}
			}
			_tensor(shp_v l_,T value=0){
				// with _ptr pointer as the starting point,allocate memory
				// for the number of elements based on the shape and
				// store value.
				_shp = l_;
				size_t n = _shp.size();
				while(_cap < n) _cap *= EXTENSION_RATE;
				_ptr = _alloc.allocate(_cap);
				this->_base = this->_ptr;
				for (int i=0;i<n;++i){
					_emplace_back( value );
				}
			}
			// --------------------------------------------------
			//			shape
			// --------------------------------------------------
			shape_size_t size()  override{ return _shp.size(); }
			shape_size_t ndim()  override{ return _shp.ndim(); }
			shp_v	     shape() override{ return _shp();	     }
			// --------------------------------------------------
			//			allocate
			// --------------------------------------------------
			using typename _tensor_alloc<T,Allocator>::traits;
			using typename _tensor_alloc<T,Allocator>::size_type;
			using typename _tensor_alloc<T,Allocator>::pointer;
			size_type cap() const override{ return _cap; }
			size_type len() const override{ return _len; }
			bool empty() const noexcept override{ return !_len; }
			//---------------------------------------------------
			//			dtype
			//---------------------------------------------------
			using _tensor_dtype<T>::d_type;
			ten_type_name name() const override { return d_type(); } 
			void dtype() const override{
				std::cout << d_type << std::endl;
			}
			//---------------------------------------------------
			//			tein
			//---------------------------------------------------
			mem_size_t mem_size() const override{ return sizeof(*this); } // total memory size
			void info() override{
				std::cout << '\n';
				std::cout << "+---------------info---------------+" << '\n';
				std::cout << " number of element => " << size() << '\n';
				std::cout << " tensor shape => " << shape() << '\n';
				std::cout << " tensor element type => " << d_type << '\n';
				std::cout << " memory consumption size => " << mem_size() * sizeof(char) << " bytes" << '\n';
				std::cout << " capacity size => " << cap() * sizeof(char) << "bytes" << '\n';
				std::cout << " memory length => " << len() * sizeof(char) << "bytes" << '\n';
				std::cout << "+----------------------------------+" << '\n'; 
				std::cout << '\n';
			}
			//---------------------------------------------------
			//			operator
			//---------------------------------------------------
			//_tensor<T,I-1,Allocator>& operator[](subsc_t s_){

			//}
		private:
			template<typename... Args>
			void _emplace_back(Args&&... args){
				if (_len == _cap) this->_extension();
				traits::construct(_alloc,_ptr+_len,std::forward<Args>(args)...);
				++_len;
				this->_ilen = _len;
			}
		}; // _tensor
	}; // _ten
}; // namespace _md

#endif // TENSOR_H
