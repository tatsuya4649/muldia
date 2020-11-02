#include <core/shape.h>

namespace _md{
	std::ostream& operator<<(std::ostream& os,_shape s_){
		os << s_.str();
		return os;	
	}
	bool operator==(const _shape& s1_,const _shape& s2_){
		return (s1_() == s2_());
	}
	bool operator!=(const _shape& s1_,const _shape& s2_){
		return !(s1_() == s2_());
	}
} // namespace _md
