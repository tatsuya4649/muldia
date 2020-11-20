// <tensor.h> header that defines an alias that uses the interface to omit namespace specification
//

#ifndef TENSOR_H
#define TENSOR_H

#include <tensor/_parent_impl.h>

template <typename T = int,typename Allocator = std::allocator<T>>
using tensor = _md::_ten::_parent_tensor<T,Allocator>;

#endif // TENSOR_H
