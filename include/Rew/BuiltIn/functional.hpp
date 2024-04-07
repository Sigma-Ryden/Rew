#ifndef REW_BUILTIN_FUNCTIONAL_HPP
#define REW_BUILTIN_FUNCTIONAL_HPP

#include <functional> // hash

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename KeyType>), (std::hash<KeyType>),
    std::hash<CLEANOF(KeyType)>
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename KeyType>), std::hash<KeyType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::hash<" + NAMEOF(KeyType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename KeyType>), std::hash<KeyType>)
    #ifndef REW_CORE_MINIMAL
    FACTORY(R())
    FACTORY(R(R const&))
    FUNCTION(operator())
    #endif // REW_CORE_MINIMAL
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_CLEAN((template <typename T>), (std::equal_to<T>), std::equal_to<CLEANOF(T)>)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename T>), std::equal_to<T>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::equal_to<" + NAMEOF(T) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename T>), std::equal_to<T>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_CLEAN((template <typename T>), (std::less<T>), std::less<CLEANOF(T)>)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename T>), std::less<T>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::less<" + NAMEOF(T) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename T>), std::less<T>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_CLEAN((template <typename T>), (std::greater<T>), std::greater<CLEANOF(T)>)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename T>), std::greater<T>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::greater<" + NAMEOF(T) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename T>), std::greater<T>)
REFLECTABLE_INIT()

#endif // REW_BUILTIN_FUNCTIONAL_HPP
