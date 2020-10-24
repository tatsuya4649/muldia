// <core/shape.h> header is to define Muldia shape.
// store shape as an array using vector library.
//
#ifndef CORE_SHAPE_H
#define CORE_SHAPE_H

#include <name.h>
#include <vector>
#include <type_traits>
#include <initializer_list>
#include <iostream>

namespace __md{
	using __shape_t = unsigned int;
	using __shape_size_t = unsigned int;
	class shape{
		private:
			bool chck_shape_size(__shape_t i){
				if ( i >= _shape_size or i < 0){
					return false;
				}else{
					return true;
				}
			}
		public:
			// 
			// how to initialize muldia::shape<T> class
			// =========================================
			// muldia::shape<T>([a,b,c]) => shape (a,b,c)
			// muldia::shape<T>(std::vector<T>(a,b,c)) => shape (a,b,c)
			// muldia::shape<T>((a,b,c)) => shape (a,b,c)
			// muldia::shape<T>(T a)   => shape (a)
			// muldia::shape<T>(std::initialize_list<T>({a,b,c})) => shape {a,b,c}
			//
			//
			shape() = delete;
			shape(__shape_t _t,__shape_size_t _ts=1) : _shape_size{_ts}{
				for (;_ts!=0;--_ts){
					_shape.push_back(_t);
				}
			}
			shape(std::vector<__shape_t> _vt) : _shape{_vt},_shape_size{static_cast<__shape_size_t>(_vt.size())}{}
			shape(__shape_t* _pt,__shape_size_t _ts=1) : _shape_size{_ts}{
				for (__shape_size_t i=0;i!=_ts;++i){
					_shape.push_back(*(_pt+i));
				}
			}
			shape(const shape& __s) : _shape{__s._shape},_shape_size{__s._shape_size}{}
			shape(shape&& __s) : _shape{__s._shape},_shape_size{__s._shape_size}{
				__s._shape = std::vector<__shape_t>{};
				__s._shape_size = 0;
			}
			shape& operator=(const shape& __s){
				this->_shape = __s._shape;
				this->_shape_size = __s._shape_size;
				return *this;
			}
			shape& operator=(shape&& __s){
				if (this!=&__s){
					this->_shape = __s._shape;
					this->_shape_size = __s._shape_size;
				}
				return *this;
			}
			__shape_t operator[](__shape_t i){ 
				if (chck_shape_size(i)){
					// error handle (out_of_index)
				}
				return _shape[i];
			}
			__shape_t operator()(__shape_t i){
				if (chck_shape_size(i)){
					// error handle (out_of_index)
				}
				return _shape[i];
			}
			std::vector<__shape_t> operator()() const{ return _shape; }
			__shape_size_t ndim() { return _shape_size; }
			std::string str(){
				std::string res{};
				res += "{";
				for (auto __sp : _shape){
					res += std::to_string(__sp);
					if (__sp != _shape.back())
						res += ",";
				}
				res += "}";
				return res;
			}

		private:
			std::vector<__shape_t> _shape;
			__shape_size_t   _shape_size;
	
	}; // class shape

	std::ostream& operator<<(std::ostream&,shape);
	bool operator==(const shape&,const shape&);
	bool operator!=(const shape&,const shape&);

} // namespace __md

#endif // CORE_SHAPE_H
