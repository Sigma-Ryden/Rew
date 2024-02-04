#ifndef REW_BUILTIN_STRING_HPP
#define REW_BUILTIN_STRING_HPP

#include <string> // basic_string

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// default allocator for basic_string
#include <Rew/BuiltIn/allocator.hpp>

// as function argument type
#include <Rew/BuiltIn/initializer_list.hpp>

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename CharType, typename Traits, typename AllocatorType>),
    std::basic_string<CharType, Traits, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::basic_string<" + NAMEOF(CharType) + ", " + NAMEOF(Traits) + ", " + NAMEOF(AllocatorType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION((template <>), (std::string))
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::string")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION((template <>), (std::wstring))
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::wstring")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename CharType, typename Traits, typename AllocatorType>),
    std::basic_string<CharType, Traits, AllocatorType>
)
    FACTORY(R())
    FACTORY(R(typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::value_type, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::value_type))
    FACTORY(R(R const&, typename R::size_type, typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(R const&, typename R::size_type, typename R::size_type))
    FACTORY(R(typename R::value_type const*, typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(typename R::value_type const*, typename R::size_type))
    FACTORY(R(typename R::value_type const*, typename R::allocator_type const&))
    FACTORY(R(typename R::value_type const*))
    FACTORY(R(typename R::const_iterator, typename R::const_iterator, typename R::allocator_type const&))
    FACTORY(R(typename R::const_iterator, typename R::const_iterator))
    FACTORY(R(R const&, typename R::allocator_type const&))
    FACTORY(R(R const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(operator=, R&(typename R::value_type const*))
    FUNCTION(operator=, R&(typename R::value_type))
    FUNCTION(operator=, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(assign, R&(typename R::size_type, typename R::value_type))
    FUNCTION(assign, R&(R const&))
    FUNCTION(assign, R&(R const&, typename R::size_type, typename R::size_type))
    FUNCTION(assign, R&(typename R::value_type const*, typename R::size_type))
    FUNCTION(assign, R&(typename R::value_type const*))
    FUNCTION(assign, R&(typename R::const_iterator, typename R::const_iterator))
    FUNCTION(assign, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(get_allocator)
    FUNCTION(at, typename R::reference(typename R::size_type))
    FUNCTION(at, typename R::const_reference(typename R::size_type) const)
    FUNCTION(operator[], typename R::reference(typename R::size_type))
    FUNCTION(operator[], typename R::const_reference(typename R::size_type) const)
    FUNCTION(front, typename R::reference())
    FUNCTION(front, typename R::const_reference() const)
    FUNCTION(back, typename R::reference())
    FUNCTION(back, typename R::const_reference() const)
    FUNCTION(data, typename R::value_type const*() const)
#if __cplusplus >= 201703L
    FUNCTION(data, typename R::value_type*())
#endif // if
    FUNCTION(c_str)
    FUNCTION(begin, typename R::const_iterator() const)
    FUNCTION(begin, typename R::iterator())
    FUNCTION(cbegin)
    FUNCTION(end, typename R::const_iterator() const)
    FUNCTION(end, typename R::iterator())
    FUNCTION(cend)
    FUNCTION(rbegin, typename R::const_reverse_iterator() const)
    FUNCTION(rbegin, typename R::reverse_iterator())
    FUNCTION(crbegin)
    FUNCTION(rend, typename R::const_reverse_iterator() const)
    FUNCTION(rend, typename R::reverse_iterator())
    FUNCTION(crend)
    FUNCTION(empty)
    FUNCTION(size)
    FUNCTION(length)
    FUNCTION(max_size)
    FUNCTION(reserve, void(typename R::size_type))
    FUNCTION(capacity)
    FUNCTION(shrink_to_fit)
    FUNCTION(clear)
    FUNCTION(insert, R&(typename R::size_type, typename R::size_type, typename R::value_type))
    FUNCTION(insert, R&(typename R::size_type, typename R::value_type const*))
    FUNCTION(insert, R&(typename R::size_type, typename R::value_type const*, typename R::size_type))
    FUNCTION(insert, R&(typename R::size_type, R const&))
    FUNCTION(insert, R&(typename R::size_type, R const&, typename R::size_type, typename R::size_type))
    FUNCTION(insert, typename R::iterator(typename R::const_iterator, typename R::value_type))
    FUNCTION(insert, typename R::iterator(typename R::const_iterator, typename R::size_type, typename R::value_type))
    FUNCTION(insert, typename R::iterator(typename R::const_iterator, std::initializer_list<typename R::value_type>))
    FUNCTION(erase, R&(typename R::size_type, typename R::size_type))
    FUNCTION(erase, typename R::iterator(typename R::const_iterator))
    FUNCTION(erase, typename R::iterator(typename R::const_iterator, typename R::const_iterator))
    FUNCTION(push_back)
    FUNCTION(pop_back)
    FUNCTION(append, R&(typename R::size_type, typename R::value_type))
    FUNCTION(append, R&(R const&))
    FUNCTION(append, R&(R const&, typename R::size_type, typename R::size_type))
    FUNCTION(append, R&(typename R::value_type const*, typename R::size_type))
    FUNCTION(append, R&(typename R::value_type const*))
    FUNCTION(append, R&(typename R::const_iterator, typename R::const_iterator))
    FUNCTION(append, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(operator+=, R&(R const&))
    FUNCTION(operator+=, R&(typename R::value_type))
    FUNCTION(operator+=, R&(typename R::value_type const*))
    FUNCTION(operator+=, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, R const&))
    FUNCTION(replace, R&(typename R::const_iterator, typename R::const_iterator, R const&))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, R const&, typename R::size_type, typename R::size_type))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, typename R::value_type const*, typename R::size_type))
    FUNCTION(replace, R&(typename R::const_iterator, typename R::const_iterator, typename R::value_type const*, typename R::size_type))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, typename R::value_type const*))
    FUNCTION(replace, R&(typename R::const_iterator, typename R::const_iterator, typename R::value_type const*))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, typename R::size_type, typename R::value_type))
    FUNCTION(replace, R&(typename R::const_iterator, typename R::const_iterator, typename R::size_type, typename R::value_type))
    FUNCTION(replace, R&(typename R::const_iterator, typename R::const_iterator, typename R::const_iterator, typename R::const_iterator))
    FUNCTION(replace, R&(typename R::const_iterator, typename R::const_iterator, std::initializer_list<typename R::value_type>))
    FUNCTION(copy)
    FUNCTION(resize, void(typename R::size_type))
    FUNCTION(resize, void(typename R::size_type, typename R::value_type))
    FUNCTION(swap)
    FUNCTION(find, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(rfind, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(rfind, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(rfind, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(rfind, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(find_first_of, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find_first_of, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find_first_of, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find_first_of, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(find_first_not_of, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find_first_not_of, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find_first_not_of, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find_first_not_of, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(find_last_of, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find_last_of, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find_last_of, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find_last_of, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(find_last_not_of, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find_last_not_of, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find_last_not_of, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find_last_not_of, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(compare, int(R const&) const)
    FUNCTION(compare, int(typename R::size_type, typename R::size_type, R const&) const)
    FUNCTION(compare, int(typename R::size_type, typename R::size_type, R const&, typename R::size_type, typename R::size_type) const)
    FUNCTION(compare, int(typename R::value_type const*) const)
    FUNCTION(compare, int(typename R::size_type, typename R::size_type, typename R::value_type const*) const)
    FUNCTION(compare, int(typename R::size_type, typename R::size_type, typename R::value_type const*, typename R::size_type) const)
#if __cplusplus >= 202002L
    FUNCTION(starts_with, bool(typename R::value_type) const)
    FUNCTION(starts_with, bool(typename R::value_tyoe const*) const)
    FUNCTION(ends_wtih, bool(typename R::value_type) const)
    FUNCTION(ends_with, bool(typename R::value_tyoe const*) const)
#endif // if
    FUNCTION(substr, R(typename R::size_type, typename R::size_type) const)
REFLECTABLE_INIT()

#endif // REW_BUILTIN_STRING_HPP
