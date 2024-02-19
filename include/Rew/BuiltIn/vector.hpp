#ifndef REW_BUILTIN_VECTOR_HPP
#define REW_BUILTIN_VECTOR_HPP

#include <vector> // vector

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// default allocator for vector
#include <Rew/BuiltIn/allocator.hpp>

// as function argument type
#include <Rew/BuiltIn/initializer_list.hpp>

// as function argument type
#include <Rew/BuiltIn/iterator.hpp>

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType>), std::vector<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::vector<" + NAMEOF(ValueType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ValueType, typename AllocatorType>), std::vector<ValueType, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::vector<" + NAMEOF(ValueType) + ", " + NAMEOF(AllocatorType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename ValueType, typename AllocatorType>), std::vector<ValueType, AllocatorType>
)
    FACTORY(R())
    FACTORY(R(typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::const_reference, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::const_reference))
    FACTORY(R(typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>))
    FACTORY(R(R const&,  typename R::allocator_type const&))
    FACTORY(R(R const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(operator=, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(assign, void(typename R::size_type, typename R::const_reference))
    FUNCTION(assign, void(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(assign, void(std::initializer_list<typename R::value_type>))
    FUNCTION(get_allocator)
    FUNCTION(at, typename R::const_reference(typename R::size_type) const)
    FUNCTION(at, typename R::reference(typename R::size_type))
    FUNCTION(operator[], typename R::const_reference(typename R::size_type) const)
    FUNCTION(operator[], typename R::reference(typename R::size_type))
    FUNCTION(front, typename R::const_reference() const)
    FUNCTION(front, typename R::reference())
    FUNCTION(back, typename R::const_reference() const)
    FUNCTION(back, typename R::reference())
    FUNCTION(data, typename R::const_pointer() const)
    FUNCTION(data, typename R::pointer())
    FUNCTION(begin, std_const_iterator<R>() const)
    FUNCTION(begin, std_iterator<R>())
    FUNCTION(cbegin, std_const_iterator<R>() const)
    FUNCTION(end, std_const_iterator<R>() const)
    FUNCTION(end, std_iterator<R>())
    FUNCTION(cend, std_const_iterator<R>() const)
    FUNCTION(rbegin, std_const_reverse_iterator<R>() const)
    FUNCTION(rbegin, std_reverse_iterator<R>())
    FUNCTION(crbegin, std_const_reverse_iterator<R>() const)
    FUNCTION(rend, std_const_reverse_iterator<R>() const)
    FUNCTION(rend, std_reverse_iterator<R>())
    FUNCTION(crend, std_const_reverse_iterator<R>() const)
    FUNCTION(empty)
    FUNCTION(size)
    FUNCTION(max_size)
    FUNCTION(capacity)
    FUNCTION(reserve)
    FUNCTION(shrink_to_fit)
    FUNCTION(clear)
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::const_reference))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::size_type, typename R::const_reference))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, std::initializer_list<typename R::value_type>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(push_back, void(typename R::const_reference))
    FUNCTION(pop_back)
    FUNCTION(resize, void(typename R::size_type))
    FUNCTION(resize, void(typename R::size_type, typename R::const_reference))
    FUNCTION(swap)
REFLECTABLE_INIT()

#endif // REW_BUILTIN_VECTOR_HPP
