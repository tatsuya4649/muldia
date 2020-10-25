#include <core/shape.h>

namespace _md{
	std::ostream& operator<<(std::ostream& os,shape s_){
		os << s_.str();
		return os;	
	}
	bool operator==(const shape& s1_,const shape& s2_){
		return (s1_() == s2_());
	}
	bool operator!=(const shape& s1_,const shape& s2_){
		return !(s1_() == s2_());
	}
} // namespace _md
