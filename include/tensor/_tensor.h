// <include/_tensor.h> header that declares and defines the most basic
// and versatile tensor tempalte class of muldia.
//
//

#include <name.h>
#include <memory>
#include <type_traits>
#include <tensor/_ctn.h>
#include <tensor/_c_ctn.h>


namespace __md{
	template<typename T,typename Allocator = std::allocator<T>>
	class __tensor{
		static_assert(std::is_same<T,Allocator::value_type>,"allocator value type is not matched tensor value type 'T'");
	private:
		using traits = std::allocator_trais<Allocator>;
		using iterator = __container;
		using const_iterator = __const_container;
	public:
		using value_type = T;
		using allocator_type = Allocator;
		using difference_type = allocator_type::difference_type;
		using size_type = allocator_type::size_type;
		using reference = T&;
		using const_reference = const T&;
		using pointer = typename traits::pointer;
		using const_pointer = typename traits::const_pointer;
	public:
		dtype __dtype;
	}; // __tensor
}; // namespace __md
