#include <tensor/_tensor.h>
#include <tensor/_inst.h>
#include <iostream>

int main()
{
	_md::TEN::tensor_<int,1> a{1,2,3,4,5};
	a.info();

	std::vector<int> q = {1,2,3,4};
	std::vector<int>* t = &q;
	//std::cout << *t <<  std::endl;
	//std::cout << *(t+1) <<  std::endl;
	//std::cout << *(t+2) <<  std::endl;
	//std::cout << *(t+3) <<  std::endl;
}
