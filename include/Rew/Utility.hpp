#ifndef REW_UTILITY_HPP
#define REW_UTILITY_HPP

#include <any> // any
#include <memory> // addressof

#include <Rew/Detail/Meta.hpp>

namespace rew
{

inline namespace utility
{

template <typename ValueType>
ValueType forward(std::any const& object)
{
    if constexpr (std::is_reference_v<ValueType>)
    {
        return *std::any_cast<meta::to_reflectable_reference_t<ValueType>>(object);
    }
    else if constexpr (std::is_pointer_v<ValueType>)
    {
        return std::any_cast<meta::to_reflectable_pointer_t<ValueType>>(object);
    }
    else
    {
        return std::any_cast<meta::to_reflectable_object_t<ValueType>>(object);
    }
}

template <typename ValueType>
std::any backward(ValueType&& result)
{
    if constexpr (std::is_reference_v<ValueType>)
    {
        return const_cast<meta::to_reflectable_reference_t<ValueType>>(std::addressof(result));
    }
    else if constexpr (std::is_pointer_v<ValueType>)
    {
        return const_cast<meta::to_reflectable_pointer_t<ValueType>>(result);
    }
    else
    {
        return result;
    }
}

} // inline namespace utility

} // namespace rew

#endif // REW_UTILITY_HPP
