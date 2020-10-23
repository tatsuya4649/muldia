// <src/shape.cpp> define muldia::shape class member function.
#include <core/shape.h>

namespace __md{
	shape::shape(__shape_t _t,__shape_size_t _ts) : _shape_size{_ts}{
		for (;_ts!=0;--_ts){
			_shape.push_back(_t);
		}
	}

	shape::shape(std::vector<__shape_t> _vt) : _shape{_vt},_shape_size{static_cast<__shape_size_t>(_vt.size())}{}

	shape::shape(__shape_t* _pt,__shape_size_t _ts) : _shape_size{_ts}{
		for (__shape_size_t i=0;i!=_ts;++i){
			_shape.push_back(*(_pt+i));
		}
	}

	shape::shape(const shape& __s) : _shape{__s._shape},_shape_size{__s._shape_size}{}

	shape::shape(shape&& __s) : _shape{__s._shape},_shape_size{__s._shape_size}{
		__s._shape = std::vector<__shape_t>{};
		__s._shape_size = 0;
	}

	shape& shape::operator=(const shape& __s){
		this->_shape = __s._shape;
		this->_shape_size = __s._shape_size;
		return *this;
	}

	shape& shape::operator=(shape&& __s){
		if (this != &__s){
			this->_shape = __s._shape;
			this->_shape_size = __s._shape_size;
			__s._shape = std::vector<__shape_t>{};
			__s._shape_size = 0;
		}
		return *this;
	}

} // __md
