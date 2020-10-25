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
	class shape{
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
			// muldia::shape([a,b,c]) => shape (a,b,c)
			// muldia::shape(std::vector<__shape_t>(a,b,c)) => shape (a,b,c)
			// muldia::shape((a,b,c)) => shape (a,b,c)
			// muldia::shape(__shape_t a)   => shape (a)
			// muldia::shape(std::initialize_list<__shape_t>({a,b,c})) => shape {a,b,c}
			//
			//
			shape() = delete;
			shape(shape_t t_,shape_size_t ts_=1) : _shape_size{ts_}{
				for (;ts_!=0;--ts_){
					_shape.push_back(t_);
				}
			}
			shape(shp_v vt_) : _shape{vt_},_shape_size{static_cast<shape_size_t>(vt_.size())}{}
			shape(shape_t* pt_,shape_size_t ts_=1) : _shape_size{ts_}{
				for (shape_size_t i=0;i!=ts_;++i){
					_shape.push_back(*(pt_+i));
				}
			}
			shape(shp_l il_) : _shape_size{static_cast<shape_size_t>(il_.size())}{
				for (shape_size_t i=0;i!=_shape_size;++i){
					_shape.push_back(*(il_.begin() + i));
				}
			}
			shape(const shape& s_) : _shape{s_._shape},_shape_size{s_._shape_size}{}
			shape(shape&& s_) : _shape{s_._shape},_shape_size{s_._shape_size}{
				s_._shape = shp_v{};
				s_._shape_size = 0;
			}
			shape& operator=(const shape& s_){
				this->_shape = s_._shape;
				this->_shape_size = s_._shape_size;
				return *this;
			}
			shape& operator=(shape&& s_){
				if (this!=&s_){
					this->_shape = s_._shape;
					this->_shape_size = s_._shape_size;
				}
				return *this;
			}
			shape_t operator[](shape_t i){ 
				if (_chck_shape_size(i)){
					// error handle (out_of_index)
				}
				return _shape[i];
			}
			shape_t operator()(shape_t i){
				if (_chck_shape_size(i)){
					// error handle (out_of_index)
				}
				return _shape[i];
			}
			shp_v operator()() const{ return _shape; }
			shape_size_t ndim() { return _shape_size; }
			std::string str(){
				std::string res{};
				res += "(";
				for (const auto& sp_ : _shape){
					res += std::to_string(sp_);
					if (&sp_ != &(_shape.back()))
						res += ",";
				}
				res += ")";
				return res;
			}
			shape_size_t size() {return std::accumulate(_shape.begin(),_shape.end(),1,[](int init,int v){ return init * v;});}

		private:
			shp_v 	       _shape;
			shape_size_t   _shape_size;
	
	}; // class shape

	std::ostream& operator<<(std::ostream&,shape);
	bool operator==(const shape&,const shape&);
	bool operator!=(const shape&,const shape&);

} // namespace _md

#endif // CORE_SHAPE_H
