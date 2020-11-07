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
#include <tensor/_op.h>
#include <tensor/_c.h>

namespace _md{
	namespace _ten{
		template<typename T,typename Allocator = std::allocator<T>>
		class _tensor : public _tein,public _tensor_shape, public _tensor_alloc<T,Allocator>,public _tensor_dtype<T>,public _tensor_iter<T,Allocator>,public _tensor_operator,public _tensor_child<T,Allocator>{
			//
			// a low-level tensor class shared by all high-level tensor
			// classes defined in muldia.
			//
			// .........................................................
			// 			all parameteras
			// .........................................................
			// * _shape _shp => the shape of _tensor
			// * Allocator _alloc => to allocate memory(default : std::allocator<T>)
			// * pointer _ptr => std::allocator_traits<Allocator>'s pointer
			// * size_type _cap => reserved memory size
			// * size_type _len => used memory size
			// * pointer _base => the pointer on which the iterator is based
			// * size_type _ilen => used memory size for _tensor_iterator
			// * _dtype<T> d_type => tensor type information
			// * (private) pointer _c_start_ptr => pointer to child tensor start pointer
			// * (private) _shape _c_shp => the shape of _tensor for child tensor
		private:
			using _tensor_alloc<T,Allocator>::_len;
			using _tensor_alloc<T,Allocator>::_cap;
			using _tensor_alloc<T,Allocator>::_alloc;
			using _tensor_alloc<T,Allocator>::_ptr;
			using typename _tensor_alloc<T,Allocator>::pointer;
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
			//_tensor(nest_init_t<T,I> v_,shp_v l_){
				// disassemble the nested n-dimensional std::vector,
				// convert it to a linear array vector,and then allocate memory.
				//std::vector<T> total_v;
				//re_nest<T,I>(v_,total_v);
				//_shp = _shape{l_};
				//while(_cap < total_v.size()) _cap *= EXTENSION_RATE;
				//_ptr = _alloc.allocate(_cap);
				//this->_base = this->_ptr;
				//for (int i=0;i<total_v.size();++i){
				//	_emplace_back(total_v[i]);
				//}
			//}
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
			_tensor(pointer p_,_shape shape_){
				_shp = shape_;
				size_t n = shape_.size();
				while(_cap < n) _cap *= EXTENSION_RATE;
				_ptr = _alloc.allocate(_cap);
				this->_base = p_;
				for(int i=0;i<n;++i){
					std::cout << *(p_+i) << std::endl;
					_emplace_back( *(p_+i) );
				}
			}
			_tensor(const _tensor& ten_){
				while(_cap < ten_._len) _cap *= EXTENSION_RATE;
				_shp = ten_._shp;
				_len = ten_._len;
				_ilen = ten_._ilen;
				d_type = ten_.d_type;
				_ptr = _alloc.allocate(_cap);
				this->_base = _ptr;
				for(int i=0;i<_len;++i){
					traits::construct(_alloc,_ptr+i,*(ten_._ptr+i));
				}
			}
			_tensor(_tensor&& ten_){
				_cap = ten_._cap;
				_shp = ten_._shp;
				_len = ten_._len;
				_ilen = ten_._ilen;
				d_type = ten_.d_type;
				_ptr = ten_._ptr;
				this->_base = ten_._base;
				ten_._ptr = nullptr;
			}
			~_tensor()override{}
			// --------------------------------------------------
			//			shape
			// --------------------------------------------------
			shape_size_t size()  override{ return _shp.size(); }
			shape_size_t ndim()  override{ return _shp.ndim(); }
			shp_v	     shape() override{ return _shp();	     }
			using _tensor_shape::shp_subsc;
			using _tensor_shape::shp;
			// --------------------------------------------------
			//			allocate
			// --------------------------------------------------
			using typename _tensor_alloc<T,Allocator>::traits;
			using typename _tensor_alloc<T,Allocator>::size_type;
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
				if (_c_start_ptr == nullptr){
					std::cout << " number of element => " << size() << '\n';
					std::cout << " tensor shape => " << shape() << '\n';
					std::cout << " memory consumption size => " << mem_size() * sizeof(char) << " bytes" << '\n';
					std::cout << " memory length => " << len() * sizeof(char) << "bytes" << '\n';
					std::cout << " capacity size => " << cap() * sizeof(char) << "bytes" << '\n';
				}else{
					std::cout << " number of element => " << _c_shp.size() << '\n';
					std::cout << " tensor shape => " << _c_shp() << '\n';
					std::cout << " memory length => " << _c_shp.size() * sizeof(char) << "bytes" << '\n';
				}
				std::cout << " tensor element type => " << d_type << '\n';
				std::cout << "+----------------------------------+" << '\n';
				std::cout << "=============== value ==============" << '\n';
				unsigned int n = _c_start_ptr==nullptr?_cap:_c_shp.size();
				for (unsigned int i=0;i<n;++i){
					if (_c_start_ptr == nullptr)
						std::cout << *(_ptr+i);
					else
						std::cout << *(_c_start_ptr+i);
					if (i!=(n-1)){
						std::cout << " ,"; 
					}else{
						std::cout << '\n';
					}
				}
				std::cout << "====================================" << '\n'; 
				std::cout << '\n';
				child_delete();
			}
			//---------------------------------------------------
			//			iterator
			//---------------------------------------------------
			using _tensor_iter<T,Allocator>::_base;
			using _tensor_iter<T,Allocator>::_ilen;
			//---------------------------------------------------
			//			child	
			//---------------------------------------------------
			using _tensor_child<T,Allocator>::_c_start_ptr;
			using _tensor_child<T,Allocator>::_c_len;
			using _tensor_child<T,Allocator>::_c_shp;
			using _tensor_child<T,Allocator>::child_delete;
			using _tensor_child<T,Allocator>::have_c_tensor;
			using _tensor_child<T,Allocator>::_c_shp_size;
			using _tensor_child<T,Allocator>::c_start_ptr;
			using _tensor_child<T,Allocator>::c_len;
			using _tensor_child<T,Allocator>::c_shp;
			//---------------------------------------------------
			//			operator
			//---------------------------------------------------
			_tensor<T,Allocator>& operator()() override{
				info();
				return *this;
			}
			_tensor<T,Allocator>& operator=(_tensor<T,Allocator>& ten_){
				return copy(ten_);
			}
			_tensor<T,Allocator>& operator=(_tensor<T,Allocator>&& ten_){
				return swap(std::move(ten_));
			}
			_tensor<T,Allocator>& operator[](subsc_t sb_) &{
				pointer _subsc_ptr = nest_scratch<T,Allocator>(sb_,_shp(),_ptr);
				_shape _subsc_shp = shp_subsc(sb_);
				_c_start_ptr = _subsc_ptr;	// child tensor start pointer
				_c_shp = _subsc_shp;		// child tensor shape
				return *this;
			}
			//---------------------------------------------------
			//			etc.	
			//---------------------------------------------------
		private:
			template<typename... Args>
			void _emplace_back(Args&&... args){
				if (_len == _cap) this->_extension();
				traits::construct(_alloc,_ptr+_len,std::forward<Args>(args)...);
				++_len;
				this->_ilen = _len;
			}
			_tensor<T,Allocator>& copy(_tensor<T,Allocator>& ten_){
				if (have_c_tensor()){
					if (ten_.have_c_tensor()){
						if (_c_shp != ten_.c_shp()){std::cout << "error1";}
						for (auto i=0;i<_c_shp_size();++i){
							*(_c_start_ptr + i) = *(ten_.c_start_ptr() + i);
						}
						ten_.child_delete();
					}else{
						if (_c_shp != ten_.shp()){std::cout << "error1";}
						for (auto i=0;i<_c_shp_size();++i){
							*(_c_start_ptr + i) = *(ten_.ptr() + i);
						}
					}
					child_delete();
				}else{
					if (ten_.have_c_tensor()){
						if (_shp != ten_.c_shp()){std::cout << "error2";}
						for(auto i=0;i<_len;++i){
							traits::destroy(_alloc,_ptr+i);
						}
						_alloc.deallocate(_ptr,_cap);
						_cap = 1;
						while(_cap < ten_.c_len()) _cap*=EXTENSION_RATE;
						_shp = ten_.c_shp();
						_len = ten_.c_len();
						_ilen = ten_.c_len();
						d_type = ten_.d_type;
						_ptr = _alloc.allocate(_cap);
						_base = _ptr;
						for(auto i=0;i<_len;++i){
							traits::construct(_alloc,_ptr+i,*(ten_.c_start_ptr()+i));
						}
						ten_.child_delete();
					}else{
						for(auto i=0;i<_len;++i){
							traits::destroy(_alloc,_ptr+i);
						}
						_alloc.deallocate(_ptr,_cap);
						_cap = 1;
						while(_cap < ten_._len) _cap*=EXTENSION_RATE;
						_shp = ten_._shp;
						_len = ten_._len;
						_ilen = ten_._ilen;
						d_type = ten_.d_type;
						_ptr = _alloc.allocate(_cap);
						_base = _ptr;
						for(auto i=0;i<_len;++i){
							traits::construct(_alloc,_ptr+i,*(ten_._ptr+i));
						}
					}
				}
				return *this;
			}
			_tensor<T,Allocator>& swap(_tensor<T,Allocator>&& ten_){
				if (have_c_tensor()){
					if (ten_.have_c_tensor()){
						for (auto i=0;i<_c_shp_size();++i){
							*(_c_start_ptr+i) = *(ten_.c_start_ptr()+i);
						}
						ten_.child_delete();
					}else{
						for (auto i=0;i<_c_shp_size();++i){
							*(_c_start_ptr+i) = *(ten_.ptr()+i);
						}
					}
					ten_.ptr = nullptr;
					child_delete();
				}else{
					if (ten_.have_c_tensor()){
						for(auto i=0;i<_len;++i){
							traits::destroy(_alloc,_ptr+i);
						}
						_alloc.deallocate(_ptr,_cap);
						_alloc = ten_._alloc;
						_shp = ten_.c_shp();
						_len = ten_.c_len();
						_ilen = _len;
						d_type = ten_.d_type;
						_cap = _len;
						_ptr = _alloc.allocate(_cap);
						_base = _ptr;
						ten_.child_delete();
					}else{
						for(auto i=0;i<_len;++i){
							traits::destroy(_alloc,_ptr+i);
						}
						_alloc.deallocate(_ptr,_cap);
						_alloc = ten_._alloc;
						_shp = ten_._shp;
						_len = ten_._len;
						_ilen = ten_._ilen;
						d_type = ten_.d_type;
						_cap = ten_._cap;
						_len = ten_._len;
						_ptr = ten_._ptr;
						_base = ten_._base;
					}
					ten_._ptr = nullptr;
				}
				return *this;
			}
		}; // _tensor
	}; // _ten
}; // namespace _md

#endif // TENSOR_H
