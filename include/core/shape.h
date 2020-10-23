// <core/shape.h> header is to define Muldia shape.
// store shape as an array using vector library.
//
#ifndef CORE_SHAPE_H
#define CORE_SHAPE_H

#include <name.h>
#include <vector>
#include <type_traits>
#include <initializer_list>

namespace __md{
	using __shape_t = unsigned int;
	using __shape_size_t = unsigned int;
	class shape{
		private:
			std::vector<__shape_t> _shape;
			__shape_size_t   _shape_size;
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
			shape(__shape_t,__shape_size_t=1);
			shape(std::vector<__shape_t>);
			shape(__shape_t*,__shape_size_t=1);
			shape(const shape&);
			shape(shape&&);
			shape& operator=(const shape&);
			shape& operator=(shape&&);
	
	}; // class shape
} // namespace __md

#endif // CORE_SHAPE_H
