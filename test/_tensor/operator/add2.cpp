#include <tensor.h>

int main(){
	tensor<> a{{10,3,10},0};
	tensor<> b{{3,10},1};
	(a+b);
}
