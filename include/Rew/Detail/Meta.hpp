#ifndef REW_DETAIL_META_HPP
#define REW_DETAIL_META_HPP

#include <cstddef> // size_t

#include <string> // string
#include <any> // any, any_cast

#include <type_traits> // decay_t, enable_if_t, is_pointer_v, void_t, false_type, true_type

template <typename ReflectableType, typename enable = void>
struct rew_reflection_registry_t;

namespace rew
{

namespace meta
{

template <typename... Bn> using all = std::conjunction<Bn...>;
template <typename... Bn> using one = std::disjunction<Bn...>;

template <typename T> struct is_reference : std::false_type {};
template <typename T> struct is_reference<T&> : std::true_type {};
template <typename T> struct is_reference<const T&> : std::true_type {};

struct base_reflectable_traits {};
struct conditional_reflectable_traits : base_reflectable_traits {};

template <typename T, typename enable = void>
struct reflectable_traits { static std::string name() { return "auto"; } };

namespace detail
{

template <typename T, typename enable = void> struct has_builtin : std::false_type {};
template <typename T> struct has_builtin<T, std::void_t<decltype(&T::builtin)>> : std::true_type {};

} // namespace detail

template <typename T> struct is_reflectable : std::is_base_of<base_reflectable_traits, T> {};
template <typename T> struct is_builtin_reflectable : all<is_reflectable<T>, detail::has_builtin<T>> {};
template <typename T> struct is_custom_reflectable : all<is_reflectable<T>, std::negation<is_builtin_reflectable<T>>> {};

template <typename...>
struct function_traits;

template <typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ArgumentTypes...)>
{
    using return_type = ReturnType;
    using function_type = ReturnType(*)(ArgumentTypes...);
};

template <typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(*)(ArgumentTypes...)>
{
    using return_type = ReturnType;
    using function_type = ReturnType(*)(ArgumentTypes...);
};

template <typename>
struct property_traits;

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType ReflectableType::*>
{
    using property_type = PropertyType;
};

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType (ReflectableType::*)(void) const>
{
    using property_type = PropertyType;
};

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType (ReflectableType::*)(void)>
{
    using property_type = PropertyType;
};

template <class ClassType>
struct member_function_traits
{
    template <typename...>
    struct overload
    {
        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType (ClassType::* function)(ArgumentTypes...) const) { return function; }
        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType (ClassType::* function)(ArgumentTypes...) const&) { return function; }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType (ClassType::* function)(ArgumentTypes...)) { return function; }
        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType (ClassType::* function)(ArgumentTypes...) &) { return function; }

        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType (ParentClassType::* function)(ArgumentTypes...) const) { return function; }
        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType (ParentClassType::* function)(ArgumentTypes...) const&) { return function; }

        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType (ParentClassType::* function)(ArgumentTypes...)) { return function; }
        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType (ParentClassType::* function)(ArgumentTypes...) &) { return function; }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType (*function)(ArgumentTypes...)) { return function; }
    };

    template <typename ReturnType, typename... ArgumentTypes>
    struct overload<ReturnType(ArgumentTypes...) const>
    {
        static constexpr auto of(ReturnType (ClassType::* function)(ArgumentTypes...) const) { return function; }
        static constexpr auto of(ReturnType (ClassType::* function)(ArgumentTypes...) const&) { return function; }

        template <class ParentClassType>
        static constexpr auto of(ReturnType (ParentClassType::* function)(ArgumentTypes...) const) { return function; }
        template <class ParentClassType>
        static constexpr auto of(ReturnType (ParentClassType::* function)(ArgumentTypes...) const&) { return function; }

        static constexpr auto of(ReturnType (*function)(ArgumentTypes...)) { return function; }
    };

    template <typename ReturnType, typename... ArgumentTypes>
    struct overload<ReturnType(ArgumentTypes...)>
    {
        static constexpr auto of(ReturnType (ClassType::* function)(ArgumentTypes...)) { return function; }
        static constexpr auto of(ReturnType (ClassType::* function)(ArgumentTypes...) &) { return function; }

        template <class ParentClassType>
        static constexpr auto of(ReturnType (ParentClassType::* function)(ArgumentTypes...)) { return function; }
        template <class ParentClassType>
        static constexpr auto of(ReturnType (ParentClassType::* function)(ArgumentTypes...) &) { return function; }

        static constexpr auto of(ReturnType (*function)(ArgumentTypes...)) { return function; }
    };
};

} // namespace meta

} // namespace rew

#endif // REW_DETAIL_META_HPP
