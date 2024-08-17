# Rew - Simple reflection library 

`Rew` is a flexible and extensible C++ library with many features, that will allow you to easily reflects your code.
The library has a small code base, but enough to use it. 

Use macros for code generation or read the documentation and write your own code. 

Is a header-only library implemented purely in C++17. 

See last stable library version [here](https://github.com/Sigma-Ryden/SerializationFixture/tree/master/package). 

## Functional: 

### Reflection of common types:
- void
- std::nullptr_t
- bool
- char, wchar_t, char8_t (since C++20), char16_t, char32_t
- signed char, unsigned char, int, unsigned int, long, unsigned long, long long, unsigned long long, float, double, long double
- std::size_t, std::ptrdiff_t
- pointer 

### Reflection declaration (only) of special types:
- reference, const, const reference
- static array
- function 

### Reflection of standard library types:
- C++11:
Containers: vector, array, basic_string, list, forward_list, set, unorganized_set, map, unordered_map, deque, initializer_list
Adapters: stack, queue, priority_queue
Smart pointers: unique_ptr, shared_ptr, weak_ptr
Other: pair, tuple, allocator, bitset, complex, reference_wrapper, char_traits
RTTI: typeinfo, typeindex
Functional: hash, equal_to, less, greater, function
Iterators: const_iterator, iterator, const_reverse_iterator, reverse_iterator, const_local_iterator, local_iterator
- C++17:
Functional: any, optional, variant
Compare: partial_ordering, weak_ordering, strong_ordering 

See full list [here](https://github.com/Sigma-Ryden/Rew/tree/master/include/Rew/BuiltIn). 

### Reflection of custom types:
- struct, class, union
- enum, scoped enum 

### Reflection of attributes:
- Parent
- Factory
- Function
- Property
- Meta 

## Auto Tests:
See library testing [here](https://github.com/Sigma-Ryden/Rew/tree/master/test). 

## License:
This library is an open source project licensed under: [MIT](https://opensource.org/licenses/MIT).