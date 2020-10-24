#include <core/shape.h>

namespace __md{
	std::ostream& operator<<(std::ostream& os,shape __s){
		os << __s.str();
		return os;	
	}
	bool operator==(const shape& __s1,const shape& __s2){
		return (__s1() == __s2());
	}
	bool operator!=(const shape& __s1,const shape& __s2){
		return !(__s1() == __s2());
	}
} // namespace __md
