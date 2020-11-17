#include <tensor/_parent_impl.h>

int main(){
	_md::_ten::_parent_tensor<double> parent(3,3,2);
	_md::_ten::_child_tensor<double> child{parent,1};
}
