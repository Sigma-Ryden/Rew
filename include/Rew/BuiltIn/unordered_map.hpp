#ifndef REW_BUILTIN_UNORDERED_MAP_HPP
#define REW_BUILTIN_UNORDERED_MAP_HPP

#include <unordered_map> // unordered_map, unordered_multimap

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// default allocator for unordered_map, unordered_multimap
#include <Rew/BuiltIn/allocator.hpp>

// as function argument type
#include <Rew/BuiltIn/initializer_list.hpp>
#include <Rew/BuiltIn/iterator.hpp>

// as value type
#include <Rew/BuiltIn/pair.hpp>

// hash - as hasher
// equal_to - as comparator
#include <Rew/BuiltIn/functional.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename KeyType, typename ValueType, typename Hasher, typename Comparator, typename AllocatorType>),
    (std::unordered_map<KeyType, ValueType, Hasher, Comparator, AllocatorType>),
    std::unordered_map<CLEANOF(KeyType), CLEANOF(ValueType), CLEANOF(Hasher), CLEANOF(Comparator), CLEANOF(AllocatorType)>
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename KeyType, typename ValueType>), std::unordered_map<KeyType, ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::unordered_map<" + NAMEOF(KeyType) + ", " + NAMEOF(ValueType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename Hasher>),
    std::unordered_map<KeyType, ValueType, Hasher>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::unordered_map<" + NAMEOF(KeyType) + ", " + NAMEOF(ValueType) + ", " + NAMEOF(Hasher) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename Hasher, typename Comparator>),
    std::unordered_map<KeyType, ValueType, Hasher, Comparator>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::unordered_map<" + NAMEOF(KeyType) + ", " + NAMEOF(ValueType) + ", "
                              + NAMEOF(Comparator) + ", " + NAMEOF(Hasher) + ">"
    )
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename Hasher, typename Comparator, typename AllocatorType>),
    std::unordered_map<KeyType, ValueType, Hasher, Comparator, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::unordered_map<" + NAMEOF(KeyType) + ", " + NAMEOF(ValueType) + ", " + NAMEOF(Hasher) + ", "
                              + NAMEOF(Comparator) + ", " + NAMEOF(AllocatorType) + ">"
    )
REFLECTABLE_DECLARATION_INIT()


TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename KeyType, typename ValueType, typename Hasher, typename Comparator, typename AllocatorType>),
    (std::unordered_multimap<KeyType, ValueType, Hasher, Comparator, AllocatorType>),
    std::unordered_multimap<CLEANOF(KeyType), CLEANOF(ValueType), CLEANOF(Hasher), CLEANOF(Comparator), CLEANOF(AllocatorType)>
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename KeyType, typename ValueType>), std::unordered_multimap<KeyType, ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::unordered_multimap<" + NAMEOF(KeyType) + ", " + NAMEOF(ValueType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename Hasher>),
    std::unordered_multimap<KeyType, ValueType, Hasher>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::unordered_multimap<" + NAMEOF(KeyType) + ", " + NAMEOF(ValueType) + ", " + NAMEOF(Hasher) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename Hasher, typename Comparator>),
    std::unordered_multimap<KeyType, ValueType, Hasher, Comparator>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::unordered_multimap<" + NAMEOF(KeyType) + ", " + NAMEOF(ValueType) + ", "
                                   + NAMEOF(Comparator) + ", " + NAMEOF(Hasher) + ">"
    )
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename Hasher, typename Comparator, typename AllocatorType>),
    std::unordered_multimap<KeyType, ValueType, Hasher, Comparator, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::unordered_multimap<" + NAMEOF(KeyType) + ", " + NAMEOF(ValueType) + ", " + NAMEOF(Hasher) + ", "
                                   + NAMEOF(Comparator) + ", " + NAMEOF(AllocatorType) + ">"
    )
REFLECTABLE_DECLARATION_INIT()


template <typename> struct __rew_is_any_std_unordered_map : std::false_type {};

template <typename KeyType, typename Hasher, typename Comparator, typename AllocatorType>
struct __rew_is_any_std_unordered_map<std::unordered_map<KeyType, Hasher, Comparator, AllocatorType>> : std::true_type {};

template <typename KeyType, typename Hasher, typename Comparator, typename AllocatorType>
struct __rew_is_any_std_unordered_map<std::unordered_multimap<KeyType, Hasher, Comparator, AllocatorType>> : std::true_type {};

CONDITIONAL_REFLECTABLE(__rew_is_any_std_unordered_map<R>::value)
    FACTORY(R())
    FACTORY(R(typename R::size_type, typename R::hasher const&, typename R::key_equal const&, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::hasher const&, typename R::key_equal const&))
    FACTORY(R(typename R::size_type, typename R::hasher const&))
    FACTORY(R(typename R::size_type))
    FACTORY(R(typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::hasher const&, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::hasher const&, typename R::key_equal const&, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::hasher const&, typename R::key_equal const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::hasher const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::hasher const&, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type, typename R::hasher const&, typename R::key_equal const&, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type, typename R::hasher const&, typename R::key_equal const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type, typename R::hasher const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type, typename R::hasher const&, typename R::allocator_type const&))
    FUNCTION(get_allocator)
    FUNCTION(begin, std_const_iterator<R>() const)
    FUNCTION(begin, std_iterator<R>())
    FUNCTION(cbegin, std_const_iterator<R>() const)
    FUNCTION(end, std_const_iterator<R>() const)
    FUNCTION(end, std_iterator<R>())
    FUNCTION(cend, std_const_iterator<R>() const)
    FUNCTION(empty)
    FUNCTION(size)
    FUNCTION(max_size)
    FUNCTION(clear)
    FUNCTION(insert, std::pair<std_iterator<R>, bool>(typename R::const_reference))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::const_reference))
    FUNCTION(insert, void(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(insert, void(std::initializer_list<typename R::value_type>))
    FUNCTION(erase, std_iterator<R>(std_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(swap)
//  FUNCTION(extract, typename R::node_type(std_const_iterator<R>))
//  FUNCTION(extract, typename R::node_type(typename R::key_type const&))
    FUNCTION(merge, void(R&))
    FUNCTION(at, typename R::mapped_type&(typename R::key_type const&))
    FUNCTION(at, typename R::mapped_type const&(typename R::key_type const&) const)
    FUNCTION(operator[], typename R::mapped_type&(typename R::key_type const&))
    FUNCTION(count, typename R::size_type(typename R::key_type const&) const)
    FUNCTION(find, std_iterator<R>(typename R::key_type const&))
    FUNCTION(find, std_const_iterator<R>(typename R::key_type const&) const)
#if __cplusplus >= 202002L
    FUNCTION(contains, bool(typename R::key_type const&) const)
#endif // if
    FUNCTION(equal_range, std::pair<std_iterator<R>, std_iterator<R>>(typename R::key_type const&))
    FUNCTION(equal_range, std::pair<std_const_iterator<R>, std_const_iterator<R>>(typename R::key_type const&) const)
    FUNCTION(begin, std_const_local_iterator<R>(typename R::size_type) const)
    FUNCTION(begin, std_local_iterator<R>(typename R::size_type))
    FUNCTION(cbegin, std_const_local_iterator<R>(typename R::size_type) const)
    FUNCTION(end, std_const_local_iterator<R>(typename R::size_type) const)
    FUNCTION(end, std_local_iterator<R>(typename R::size_type))
    FUNCTION(cend, std_const_local_iterator<R>(typename R::size_type) const)
    FUNCTION(bucket_count)
    FUNCTION(max_bucket_count)
    FUNCTION(bucket_size)
    FUNCTION(bucket, typename R::size_type(typename R::key_type const&) const)
    FUNCTION(load_factor)
    FUNCTION(max_load_factor, float() const)
    FUNCTION(max_load_factor, void(float))
    FUNCTION(rehash)
    FUNCTION(reserve)
//  FUNCTION(hash_function)
//  FUNCTION(key_eq)
REFLECTABLE_INIT()

#endif // REW_BUILTIN_UNORDERED_MAP_HPP
