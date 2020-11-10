// <tensor.h> header that defines an alias that uses the interface to omit namespace specification
//

#ifndef TENSOR_H
#define TENSOR_H

#include <tensor/_tensor.h>
#include <memory>

template <typename T = int,typename Allocator = std::allocator<T>>
using tensor = _md::_ten::_tensor<T,Allocator>;

#endif // TENSOR_H
