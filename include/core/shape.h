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
#include <numeric>

namespace _md{
	using shape_t = unsigned int;
	using shape_size_t = unsigned int;
	using shp_v = std::vector<shape_t>;
	using shp_l = std::initializer_list<shape_t>;
	class _shape{
		private:
			bool _chck_shape_size(shape_t i){
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
			// muldia::_shape([a,b,c]) => shape (a,b,c)
			// muldia::_shape(std::vector<__shape_t>(a,b,c)) => shape (a,b,c)
			// muldia::_shape((a,b,c)) => shape (a,b,c)
			// muldia::_shape(__shape_t a)   => shape (a)
			// muldia::_shape(std::initialize_list<__shape_t>({a,b,c})) => shape {a,b,c}
			//
			_shape() = default;
			_shape(shape_t t_,shape_size_t ts_=1) : _shape_size{ts_}{
				for (;ts_!=0;--ts_){
					_shp.push_back(t_);
				}
			}
			_shape(shp_v vt_) : _shp{vt_},_shape_size{static_cast<shape_size_t>(vt_.size())}{}
			_shape(shape_t* pt_,shape_size_t ts_=1) : _shape_size{ts_}{
				for (shape_size_t i=0;i!=ts_;++i){
					_shp.push_back(*(pt_+i));
				}
			}
			_shape(shp_l il_) : _shape_size{static_cast<shape_size_t>(il_.size())}{
				for (shape_size_t i=0;i!=_shape_size;++i){
					_shp.push_back(*(il_.begin() + i));
				}
			}
			_shape(const _shape& s_) : _shp{s_._shp},_shape_size{s_._shape_size}{}
			_shape(_shape&& s_) : _shp{s_._shp},_shape_size{s_._shape_size}{
				s_._shp = shp_v{};
				s_._shape_size = 0;
			}
			_shape& operator=(const _shape& s_){
				this->_shp = s_._shp;
				this->_shape_size = s_._shape_size;
				return *this;
			}
			_shape& operator=(_shape&& s_){
				if (this!=&s_){
					this->_shp = s_._shp;
					this->_shape_size = s_._shape_size;
				}
				return *this;
			}
			shape_t operator[](shape_t i){ 
				if (_chck_shape_size(i)){
					// error handle (out_of_index)
				}
				return _shp[i];
			}
			shape_t operator()(shape_t i){
				if (_chck_shape_size(i)){
					// error handle (out_of_index)
				}
				return _shp[i];
			}
			shp_v operator()() const{ return _shp; }
			shape_size_t ndim() { return _shape_size; }
			std::string str(){
				std::string res{};
				res += "(";
				for (const auto& sp_ : _shp){
					res += std::to_string(sp_);
					if (&sp_ != &(_shp.back()))
						res += ",";
				}
				res += ")";
				return res;
			}
			shape_size_t size() {return std::accumulate(_shp.begin(),_shp.end(),1,[](int init,int v){ return init * v;});}

		private:
			shp_v 	       _shp;
			shape_size_t   _shape_size;
	
	}; // class _shape

	std::ostream& operator<<(std::ostream&,_shape);
	bool operator==(const _shape&,const _shape&);
	bool operator!=(const _shape&,const _shape&);

} // namespace _md

#endif // CORE_SHAPE_H
