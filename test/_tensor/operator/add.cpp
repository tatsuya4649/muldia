#include <tensor/_tensor.h>

int main()
{
	std::cout << "initialize 0" << std::endl;
	_md::_ten::_tensor<int> a{{1,3,10},0};
	a.info();
	std::cout << "add 10" << std::endl;
	a+=10;
	a.info();
	std::cout << "minus 1" << std::endl;
	a-=1;
	a.info();
	std::cout << "multi 2" << std::endl;
	a*=2;
	a.info();
	std::cout << "++a" << std::endl;
	++a;
	a.info();
	std::cout << "a++" << std::endl;
	a++;
	a.info();
	std::cout << "--a" << std::endl;
	a--;
	a.info();
	std::cout << "a--" << std::endl;
	a--;
	a.info();
}
