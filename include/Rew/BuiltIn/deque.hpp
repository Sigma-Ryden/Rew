#ifndef REW_BUILTIN_DEQUE_HPP
#define REW_BUILTIN_DEQUE_HPP

#include <deque> // deque

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// default allocator for deque
#include <Rew/BuiltIn/allocator.hpp>

#ifndef RWW_CORE_MINIMAL
// as function argument type
#include <Rew/BuiltIn/initializer_list.hpp>
#include <Rew/BuiltIn/iterator.hpp>
#endif // REW_CORE_MINIMAL

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ValueType, typename AllocatorType>),
    (std::deque<ValueType, AllocatorType>), std::deque<rew::cleanof<ValueType>, rew::cleanof<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::deque<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::deque<" + rew::nameof<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType, typename AllocatorType>), std::deque<ValueType, AllocatorType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::deque<" + rew::nameof<ValueType>() + ", " + rew::nameof<AllocatorType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType, typename AllocatorType>), std::deque<ValueType, AllocatorType>)
    FACTORY(R())

    #ifndef REW_CORE_MINIMAL
    FACTORY(R(typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::const_reference, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::const_reference))
    FACTORY(R(typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>))
    FACTORY(R(R const&, typename R::allocator_type const&))
    #endif // REW_CORE_MINIMAL

    FACTORY(R(R const&))

    #ifndef REW_CORE_MINIMAL
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>))
    #endif // REW_CORE_MINIMAL

    FUNCTION(operator=, R&(R const&))

    #ifndef REW_CORE_MINIMAL
    FUNCTION(operator=, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(assign, void(typename R::size_type, typename R::const_reference))
    FUNCTION(assign, void(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(assign, void(std::initializer_list<typename R::value_type>))
    FUNCTION(get_allocator)
    FUNCTION(at, typename R::const_reference(typename R::size_type) const)
    FUNCTION(at, typename R::reference(typename R::size_type))
    #endif // REW_CORE_MINIMAL

    FUNCTION(operator[], typename R::const_reference(typename R::size_type) const)
    FUNCTION(operator[], typename R::reference(typename R::size_type))

    #ifndef REW_CORE_MINIMAL
    FUNCTION(front, typename R::const_reference() const)
    FUNCTION(front, typename R::reference())
    FUNCTION(back, typename R::const_reference() const)
    FUNCTION(back, typename R::reference())
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
    #endif // REW_CORE_MINIMAL

    FUNCTION(empty)
    FUNCTION(size)

    #ifndef REW_CORE_MINIMAL
    FUNCTION(max_size)
    FUNCTION(shrink_to_fit)
    #endif // REW_CORE_MINIMAL

    FUNCTION(clear)

    #ifndef REW_CORE_MINIMAL
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::const_reference))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::size_type, typename R::const_reference))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, std::initializer_list<typename R::value_type>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>))
    #endif // REW_CORE_MINIMAL

    FUNCTION(push_back, void(typename R::const_reference))
    FUNCTION(push_front, void(typename R::const_reference))
    FUNCTION(pop_back)
    FUNCTION(pop_front)
    FUNCTION(resize, void(typename R::size_type))

    #ifndef REW_CORE_MINIMAL
    FUNCTION(resize, void(typename R::size_type, typename R::const_reference))
    FUNCTION(swap)
    #endif // REW_CORE_MINIMAL
REFLECTABLE_INIT()

#endif // REW_BUILTIN_DEQUE_HPP
