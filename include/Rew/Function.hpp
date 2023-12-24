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

#define CORE_FUNCTION(function_call_handler, name, ...)                                                 \
    {                                                                                                   \
        auto __function = ::rew::function_overload<__VA_ARGS__>(&info_t::type::name);                   \
        using __type = decltype(__function);                                                            \
        auto __name = #name+std::string(*(#__VA_ARGS__) ? ", " #__VA_ARGS__ : "");                      \
        auto __meta = reflection->function.find(__name);                                                \
        if (__meta == nullptr) __meta = &reflection->function.add(                                      \
            __name,                                                                                     \
            { __name, function_call_handler(__function), ::rew::function_args_count(__function) }       \
        );                                                                                              \
        visitor.template function<info_t::type, __type>(*__meta);                                       \
    }

#define FUNCTION(name, ...)                                                                             \
    CORE_FUNCTION(::rew::function_call_handler, name, __VA_ARGS__)

namespace rew
{

struct function_meta_t
{
    const std::string name;
    const std::function<void(void* context, std::any& result, const std::vector<std::any>& args)> call = nullptr;
    const std::size_t arg_count = 0;
    meta_t meta;
};

using function_t = attribute_t<function_meta_t>;

template <typename ReflectableType, typename... ArgumentTypes, typename FunctionType, std::size_t... I>
auto function_call_handler_void_impl(FunctionType function, std::index_sequence<I...>)
{
    return [function](void* context, std::any& result, const std::vector<std::any>& arguments)
    {
        (static_cast<ReflectableType*>(context)->*function)(argument_cast<ArgumentTypes>(arguments[I])...);
        result.reset();
    };
}

template <typename ReflectableType, typename... ArgumentTypes, typename FunctionType, std::size_t... I>
auto function_call_handler_return_impl(FunctionType function, std::index_sequence<I...>)
{
    return [function](void* context, std::any& result, const std::vector<std::any>& arguments)
    {
        result = (static_cast<ReflectableType*>(context)->*function)(argument_cast<ArgumentTypes>(arguments[I])...);
    };
}

template <typename... ArgumentTypes, std::size_t... I>
auto function_call_handler_void_impl(void (*function)(ArgumentTypes...), std::index_sequence<I...>)
{
    return [function](void* context, std::any& result, const std::vector<std::any>& arguments)
    {
        function(argument_cast<ArgumentTypes>(arguments[I])...);
        result.reset();
    };
}

template <typename ReturnType, typename... ArgumentTypes, std::size_t... I>
auto function_call_handler_return_impl(ReturnType (*function)(ArgumentTypes...), std::index_sequence<I...>)
{
    return [function](void* context, std::any& result, const std::vector<std::any>& arguments)
    {
        result = function(argument_cast<ArgumentTypes>(arguments[I])...);
    };
}

template <typename ReflectableType, typename... ArgumentTypes>
auto function_call_handler(void (ReflectableType::* function)(ArgumentTypes...) const)
{
    return function_call_handler_void_impl<ReflectableType, ArgumentTypes...>(function, std::index_sequence_for<ArgumentTypes...>{});
}

template <typename ReflectableType, typename... ArgumentTypes>
auto function_call_handler(void (ReflectableType::* function)(ArgumentTypes...))
{
    return function_call_handler_void_impl<ReflectableType, ArgumentTypes...>(function, std::index_sequence_for<ArgumentTypes...>{});
}

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto function_call_handler(ReturnType (ReflectableType::* function)(ArgumentTypes...) const)
{
    return function_call_handler_return_impl<ReflectableType, ArgumentTypes...>(function, std::index_sequence_for<ArgumentTypes...>{});
}

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto function_call_handler(ReturnType (ReflectableType::* function)(ArgumentTypes...))
{
    return function_call_handler_return_impl<ReflectableType, ArgumentTypes...>(function, std::index_sequence_for<ArgumentTypes...>{});
}

template <typename... ArgumentTypes>
auto function_call_handler(void (*function)(ArgumentTypes...))
{
    return function_call_handler_void_impl(function, std::index_sequence_for<ArgumentTypes...>{});
}

template <typename ReturnType, typename... ArgumentTypes>
auto function_call_handler(ReturnType (*function)(ArgumentTypes...))
{
    return function_call_handler_return_impl(function, std::index_sequence_for<ArgumentTypes...>{});
}

} // namespace rew

#endif // REW_FUNCTION_HPP
