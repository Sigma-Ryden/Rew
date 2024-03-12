#ifndef REW_UTILITY_HPP
#define REW_UTILITY_HPP

#include <string> // string
#include <any> // any, any_cast

#include <type_traits> // is_reference_v, is_void_v, decay_t

#include <Rew/Detail/Meta.hpp>

namespace rew
{

namespace utility
{

template <typename ValueType>
ValueType forward(const std::any& object)
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

template <typename ReflectableType, typename ParentReflectableType, typename ReturnType, typename... ArgumentTypes>
auto function_ptr(ReturnType (ParentReflectableType::* function)(ArgumentTypes...) const)
{
    struct __inner : protected ReflectableType
    {
        static auto get(ReturnType (ParentReflectableType::* function)(ArgumentTypes...) const)
        {
            return static_cast<ReturnType (ReflectableType::*)(ArgumentTypes...) const>(function);
        }
    };
    return __inner::get(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename ReturnType, typename... ArgumentTypes>
auto function_ptr(ReturnType (ParentReflectableType::* function)(ArgumentTypes...) const&)
{
    struct __inner : protected ReflectableType
    {
        static auto get(ReturnType (ParentReflectableType::* function)(ArgumentTypes...) const&)
        {
            return static_cast<ReturnType (ReflectableType::*)(ArgumentTypes...) const&>(function);
        }
    };
    return __inner::get(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename ReturnType, typename... ArgumentTypes>
auto function_ptr(ReturnType (ParentReflectableType::* function)(ArgumentTypes...))
{
    struct __inner : protected ReflectableType
    {
        static auto get(ReturnType (ParentReflectableType::* function)(ArgumentTypes...))
        {
            return static_cast<ReturnType (ReflectableType::*)(ArgumentTypes...)>(function);
        }
    };
    return __inner::get(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename ReturnType, typename... ArgumentTypes>
auto function_ptr(ReturnType (ParentReflectableType::* function)(ArgumentTypes...) &)
{
    struct __inner : protected ReflectableType
    {
        static auto get(ReturnType (ParentReflectableType::* function)(ArgumentTypes...) &)
        {
            return static_cast<ReturnType (ReflectableType::*)(ArgumentTypes...) &>(function);
        }
    };
    return __inner::get(function);
}

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto function_ptr(ReturnType (*function)(ArgumentTypes...))
{
    return function;
}

template <typename ReflectableType, typename ParentReflectableType, typename ValueType>
auto property_ptr(ValueType ParentReflectableType::* property)
{
    struct __inner : protected ReflectableType
    {
        static auto get(ValueType ParentReflectableType::* property)
        {
            return static_cast<ValueType ReflectableType::*>(property);
        }
    };
    return __inner::get(property);
}

template <typename ReflectableType, typename ParentReflectableType, typename PropertyType>
auto property_get_ptr(PropertyType ParentReflectableType::* property)
{
    return property_ptr<ReflectableType>(property);
}

template <typename ReflectableType, typename ParentReflectableType, typename PropertyType>
auto property_get_ptr(PropertyType (ParentReflectableType::* function)(void) const)
{
    return function_ptr<ReflectableType>(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename PropertyType>
auto property_get_ptr(PropertyType (ParentReflectableType::* function)(void) const&)
{
    return function_ptr<ReflectableType>(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename PropertyType>
auto property_get_ptr(PropertyType (ParentReflectableType::* function)(void))
{
    return function_ptr<ReflectableType>(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename PropertyType>
auto property_get_ptr(PropertyType (ParentReflectableType::* function)(void) &)
{
    return function_ptr<ReflectableType>(function);
}

template <typename ReflectableType, typename PropertyType>
auto property_get_ptr(PropertyType (*function)(void))
{
    return function;
}

template <typename ReflectableType, typename ParentReflectableType, typename PropertyType>
auto property_set_ptr(PropertyType ParentReflectableType::* property)
{
    return property_ptr<ReflectableType>(property);
}

template <typename ReflectableType, typename ParentReflectableType, typename PropertyType>
auto property_set_ptr(void (ParentReflectableType::* function)(PropertyType))
{
    return function_ptr<ReflectableType>(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename PropertyType>
auto property_set_ptr(void (ParentReflectableType::* function)(PropertyType) &)
{
    return function_ptr<ReflectableType>(function);
}

template <typename ReflectableType, typename PropertyType>
auto property_set_ptr(void (*function)(PropertyType))
{
    return function;
}

} // namespace utility

} // namespace rew

#endif // REW_UTILITY_HPP
