#ifndef REW_COMMON_HPP
#define REW_COMMON_HPP

#include <Rew/Reflectable.hpp>

// incomplete type
REFLECTABLE_DECLARATION(void)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(void)
REFLECTABLE_INIT()

// pointer type
TEMPLATE_REFLECTABLE_CLEAN((template <typename ElementType>), (ElementType*), CLEANOF(ElementType)*)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ElementType>), ElementType*)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(NAMEOF(ElementType) + "*")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ElementType>), ElementType*)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

// qualified types
TEMPLATE_REFLECTABLE_CLEAN((template <typename ElementType>), (ElementType&), CLEANOF(ElementType)&)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ElementType>), ElementType&)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(NAMEOF(ElementType) + "&")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_CLEAN((template <typename ElementType>), (ElementType const), CLEANOF(ElementType) const)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ElementType>), ElementType const)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(NAMEOF(ElementType) + " const")
REFLECTABLE_DECLARATION_INIT()
// ~ qualified types

// boolean type
REFLECTABLE_DECLARATION(bool)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(bool)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
// ~ boolean type

// char types
REFLECTABLE_DECLARATION(char)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(char)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(wchar_t)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(wchar_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
// ~ char types

// integral types
REFLECTABLE_DECLARATION(signed char)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(signed char)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(unsigned char)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(unsigned char)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(int)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(int)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(unsigned int)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(unsigned int)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(long)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(long)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(unsigned long)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(unsigned long)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(long long)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(long long)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(unsigned long long)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(unsigned long long)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
// ~ integral types

// floating point types
REFLECTABLE_DECLARATION(float)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(float)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(double)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(double)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
// ~ floating point types

#endif // REW_COMMON_HPP
