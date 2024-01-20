#ifndef REW_BUILT_IN_OPTIONAL_HPP
#define REW_BUILT_IN_OPTIONAL_HPP

#include <optional> // optional, nullopt_t

#include <Rew/Reflectable.hpp>

REFLECTABLE_DECLARATION(std::nullopt_t)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType>), (std::optional<ValueType>))
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::optional<" + NAMEOF(ValueType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType>), (std::optional<ValueType>))
    FACTORY(R())
    FACTORY(R(std::nullopt_t))
    FACTORY(R(R const&))
    FACTORY(R(typename R::value_type const&))
    FUNCTION(operator=, R&(std::nullopt_t))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(operator=, R&(typename R::value_type const&))
    FUNCTION(operator->, typename R::value_type const*() const)
    FUNCTION(operator->, typename R::value_type const*())
    FUNCTION(operator*, typename R::value_type const&())
    FUNCTION(operator*, typename R::value_type&())
    FUNCTION(operator bool)
    FUNCTION(has_value)
    FUNCTION(value, typename R::value_type&())
    FUNCTION(value, typename R::value_type const&() const)
    FUNCTION(value_or, typename R::value_type(typename R::value_type const&) const)
    FUNCTION(swap)
    FUNCTION(reset)
    FUNCTION(emplace, void(typename R::value_type const&))
REFLECTABLE_INIT()

#endif // REW_BUILT_IN_OPTIONAL_HPP
