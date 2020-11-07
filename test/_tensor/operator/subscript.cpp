#include <iostream>
#include <tensor/_tensor.h>

int main()
{
	int _ten_int[2][2][2] = {
		{
			{2,2},
			{2,2}
		},
		{
			{2,2},
			{2,2}
		}};
	_md::_ten::_tensor<int> tensor{_ten_int,{2,2,2}};
}
