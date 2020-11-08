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
	//tensor[0];
	//tensor[1].info();
	_md::_ten::_tensor<int> a{_ten_int,{2,2,2}};
	a = tensor[0];
}
