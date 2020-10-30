#include <iostream>
#include <tensor/_tensor.h>

int main()
{
	int aaaa[2][3] = {{1,2,3},{4,5,6}};
	_md::_ten::_tensor<int,2> a{
		aaaa
	,{2,3}};
	a.begin();
	std::cout << a.size() << std::endl;
}
