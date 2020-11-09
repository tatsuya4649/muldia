
#include <tensor/_tensor.h>
#include <iostream>
#include <type_traits>

int main(){
	std::cout << "================= test start ====================" << std::endl;
	int aaa[2] = {2,4};
	_md::_ten::_tensor<int> tensor{aaa,{2}};
	std::vector<std::string>> c = {"vava","vavfa"};
	_md::_ten::_tensor<std::string> b{c};
	std::cout << "================= test end ====================" << std::endl;
}

