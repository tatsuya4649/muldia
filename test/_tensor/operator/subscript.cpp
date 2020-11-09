#include <iostream>
#include <tensor/_tensor.h>

int main()
{
	int _ten_int[2][2][2] = {
		{
			{1,2},
			{3,4}
		},
		{
			{5,6},
			{7,8}
		}};
	_md::_ten::_tensor<int> tensor{_ten_int,{2,2,2}};
	_md::_ten::_tensor<int> a;
	try{
		a[0];
	}catch(muldia::err::shape_subscript_error& e){
		std::cout << e.what() << std::endl;
	}
}
