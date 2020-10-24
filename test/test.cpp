#include <core/shape.h>
#include <iostream>

int main()
{
	__md::shape a{5};
	__md::shape b{3,10};
	__md::shape c{std::vector<unsigned int>{1,3,512,512}};
	unsigned int e[3] = {10,12,31};
	__md::shape d{e,3};
	__md::shape f{std::initializer_list<unsigned int>{1,3,512,512}};
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cout << f << std::endl;
}
