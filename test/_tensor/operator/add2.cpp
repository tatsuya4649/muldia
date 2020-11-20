#include <tensor.h>

int main(){
	tensor<> a(3,2,3,4);
	tensor<> b(3,1,3,4);
	(a+b).info();
}
