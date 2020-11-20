#include <tensor/_parent_impl.h>

int main(){
	_md::_ten::_parent_tensor<double> parent(3,3,2);
	_md::_ten::_child_tensor<double> child{parent,1};
	_md::_ten::_parent_tensor<double> a = parent;
	a.info();
	_md::_ten::_child_tensor<double> b = a[0];
	b.info();

}
