#ifndef REW_FUNCTION_HPP
#define REW_FUNCTION_HPP

#include <cstddef> // size_t

#include <string> // string
#include <vector> // vector
#include <any> // any

#include <functional> // function

#include <Rew/Attribute.hpp>
#include <Rew/Meta.hpp>
#include <Rew/Utility.hpp>

#include <Rew/Detail/Macro.hpp> // __REW_EXPAND

#define RAW_FUNCTION(name_str, name, ...)                                                               \
    {                                                                                                   \
        using __traits = typename rew::meta::member_function_traits<R>::template overload<__VA_ARGS__>; \
        auto __ptr = rew::utility::member_function_ptr<R>(__traits::of(&R::__REW_EXPAND name));         \
        auto __meta = rew::find_or_add_function<__VA_ARGS__>(__reflection, name_str, __ptr);            \
        injection.template function<R, decltype(__ptr)>(*__meta);                                       \
    }

#define FUNCTION(name, ...) RAW_FUNCTION(#name, (name), __VA_ARGS__)

#define RAW_FREE_FUNCTION(name_str, name, ...)                                                          \
    {                                                                                                   \
        auto __ptr = rew::meta::overload<__VA_ARGS__>::of(&__REW_EXPAND name);                          \
        auto __meta = rew::find_or_add_function<__VA_ARGS__>(__reflection, name_str, __ptr);            \
        injection.template function<R, decltype(__ptr)>(*__meta);                                       \
    }

#define FREE_FUNCTION(name, ...) RAW_FREE_FUNCTION(#name, (name), __VA_ARGS__)

namespace rew
{

struct type_t;

struct function_t
{
    const std::string name;
    const std::function<std::any(std::any& context, std::vector<std::any> args)> call = nullptr;
    const std::vector<type_t*> arguments;
    type_t *const result = nullptr;
    attribute_t<std::any> meta;
};

namespace detail
{

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
          typename FunctionType, std::size_t... I>
auto handler_member_function_call_impl(FunctionType function, std::index_sequence<I...>)
{
    return [function](std::any& context, std::vector<std::any> arguments) -> std::any
    {
        auto reflectable = std::any_cast<ReflectableType*>(context);
        if constexpr (std::is_void_v<ReturnType>)
        {
            (reflectable->*function)(utility::forward<ArgumentTypes>(arguments[I])...);
            return {};
        }
        else
        {
            return utility::backward
            (
                (reflectable->*function)(utility::forward<ArgumentTypes>(arguments[I])...)
            );
        }
    };
}

template <typename ReturnType, typename... ArgumentTypes, std::size_t... I>
auto handler_free_function_call_impl(ReturnType (*function)(ArgumentTypes...), std::index_sequence<I...>)
{
    return [function](std::any& context, std::vector<std::any> arguments) -> std::any
    {
        if constexpr (std::is_void_v<ReturnType>)
        {
            function(utility::forward<ArgumentTypes>(arguments[I])...);
            return {};
        }
        else
        {
            return utility::backward
            (
                function(utility::forward<ArgumentTypes>(arguments[I])...)
            );
        }
    };
}

} // namespace detail

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType (ReflectableType::* function)(ArgumentTypes...) const)
{
    return detail::handler_member_function_call_impl<ReflectableType, ReturnType, ArgumentTypes...>
    (
        function, std::index_sequence_for<ArgumentTypes...>{}
    );
}

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType (ReflectableType::* function)(ArgumentTypes...) const&)
{
    return detail::handler_member_function_call_impl<ReflectableType, ReturnType, ArgumentTypes...>
    (
        function, std::index_sequence_for<ArgumentTypes...>{}
    );
}

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType (ReflectableType::* function)(ArgumentTypes...))
{
    return detail::handler_member_function_call_impl<ReflectableType, ReturnType, ArgumentTypes...>
    (
        function, std::index_sequence_for<ArgumentTypes...>{}
    );
}

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType (ReflectableType::* function)(ArgumentTypes...) &)
{
    return detail::handler_member_function_call_impl<ReflectableType, ReturnType, ArgumentTypes...>
    (
        function, std::index_sequence_for<ArgumentTypes...>{}
    );
}

template <typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType (*function)(ArgumentTypes...))
{
    return detail::handler_free_function_call_impl(function, std::index_sequence_for<ArgumentTypes...>{});
}

} // namespace rew

#endif // REW_FUNCTION_HPP
