#ifndef REW_BUILTIN_VARIANT_HPP
#define REW_BUILTIN_VARIANT_HPP

#include <variant> // variant, monostate

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

REFLECTABLE_DECLARATION(std::monostate)
REFLECTABLE_DECLARATION_INIT()


TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ArgumentType, typename... ArgumentTypes>),
    (std::variant<ArgumentType, ArgumentTypes...>), std::variant<rew::cleanof<ArgumentType>, rew::cleanof<ArgumentTypes>...>
)

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ArgumentType, typename... ArgumentTypes>),
    std::variant<ArgumentType, ArgumentTypes...>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::variant<" + ( rew::nameof<ArgumentType>() + ... + (", " + rew::nameof<ArgumentTypes>()) ) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename ArgumentType, typename... ArgumentTypes>),
    std::variant<ArgumentType, ArgumentTypes...>
)
    FACTORY(R())
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(index)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(valueless_by_exception)
    FUNCTION(swap)
    #endif // REW_FULLY_ENABLE
REFLECTABLE_INIT()

#endif // REW_BUILTIN_VARIANT_HPP
