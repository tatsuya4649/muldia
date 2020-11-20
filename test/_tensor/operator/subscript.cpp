#include <iostream>
#include <tensor/tensor.h>

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
}
