// TODO: add support of functions, for reflect apply() function
#ifndef REW_BUILTIN_VALARRAY_HPP
#define REW_BUILTIN_VALARRAY_HPP

#include <valarray> // valarray

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// as function argument type
#include <Rew/BuiltIn/initializer_list.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ValueType>), (std::valarray<ValueType>),
    std::valarray<CLEANOF(ValueType)>
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType>), std::valarray<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::valarray<" + NAMEOF(ValueType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType>), std::valarray<ValueType>)
    FACTORY(R())
    FACTORY(R(std::size_t))
    FACTORY(R(ValueType const&, std::size_t))
    FACTORY(R(ValueType const*, std::size_t))
    FACTORY(R(R const&))
    FACTORY(R(std::slice_array<ValueType> const&))
    FACTORY(R(std::gslice_array<ValueType> const&))
    FACTORY(R(std::mask_array<ValueType> const&))
    FACTORY(R(std::indirect_array<ValueType> const&))
    FACTORY(R(std::initializer_list<ValueType>))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(operator=, R&(std::slice_array<ValueType> const&))
    FUNCTION(operator=, R&(std::gslice_array<ValueType> const&))
    FUNCTION(operator=, R&(std::mask_array<ValueType> const&))
    FUNCTION(operator=, R&(std::indirect_array<ValueType> const&))
    FUNCTION(operator=, R&(std::initializer_list<ValueType>))
    FUNCTION(operator[], ValueType const&(std::size_t) const)
    FUNCTION(operator[], ValueType&(std::size_t))
    FUNCTION(operator[], R(std::slice) const)
    FUNCTION(operator[], std::slice_array<ValueType>(std::slice))
    FUNCTION(operator[], R(std::gslice const&) const)
    FUNCTION(operator[], std::gslice_array<ValueType>(std::gslice const&))
    FUNCTION(operator[], R(std::valarray<bool> const&) const)
    FUNCTION(operator[], std::mask_array<ValueType>(std::valarray<bool> const&))
    FUNCTION(operator[], R(std::valarray<std::size_t> const&) const)
    FUNCTION(operator[], std::indirect_array<ValueType>(std::valarray<std::size_t> const&))
    FUNCTION(operator+)
    FUNCTION(operator-)
    FUNCTION(operator~)
    FUNCTION(operator!)
    FUNCTION(operator+=, R&(R const&))
    FUNCTION(operator-=, R&(R const&))
    FUNCTION(operator*=, R&(R const&))
    FUNCTION(operator/=, R&(R const&))
    FUNCTION(operator%=, R&(R const&))
    FUNCTION(operator&=, R&(R const&))
    FUNCTION(operator|=, R&(R const&))
    FUNCTION(operator^=, R&(R const&))
    FUNCTION(operator<<=, R&(R const&))
    FUNCTION(operator>>=, R&(R const&))
    FUNCTION(operator+=, R&(ValueType const&))
    FUNCTION(operator-=, R&(ValueType const&))
    FUNCTION(operator*=, R&(ValueType const&))
    FUNCTION(operator/=, R&(ValueType const&))
    FUNCTION(operator%=, R&(ValueType const&))
    FUNCTION(operator&=, R&(ValueType const&))
    FUNCTION(operator|=, R&(ValueType const&))
    FUNCTION(operator^=, R&(ValueType const&))
    FUNCTION(operator<<=, R&(ValueType const&))
    FUNCTION(operator>>=, R&(ValueType const&))
    FUNCTION(swap)
    FUNCTION(size)
    FUNCTION(resize)
    FUNCTION(sum)
    FUNCTION(min)
    FUNCTION(max)
    FUNCTION(shift)
    FUNCTION(cshift)
REFLECTABLE_INIT()


REFLECTABLE_DECLARATION(std::slice)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(std::slice)
    FACTORY(R())
    FACTORY(R(std::size_t, std::size_t, std::size_t))
    FACTORY(R(R const&))
    FUNCTION(start)
    FUNCTION(size)
    FUNCTION(stride)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType>), std::slice_array<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::slice_array<" + NAMEOF(ValueType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType>), std::slice_array<ValueType>)
REFLECTABLE_INIT()


REFLECTABLE_DECLARATION(std::gslice)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(std::gslice)
    FACTORY(R())
    FACTORY(R(std::size_t, std::valarray<std::size_t> const&, std::valarray<std::size_t> const&))
    FACTORY(R(R const&))
    FUNCTION(start)
    FUNCTION(size)
    FUNCTION(stride)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType>), std::gslice_array<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::gslice_array<" + NAMEOF(ValueType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType>), std::gslice_array<ValueType>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType>), std::mask_array<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::mask_array<" + NAMEOF(ValueType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType>), std::mask_array<ValueType>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType>), std::indirect_array<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::indirect_array<" + NAMEOF(ValueType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType>), std::mask_array<ValueType>)
REFLECTABLE_INIT()

#endif // REW_BUILTIN_VALARRAY_HPP
