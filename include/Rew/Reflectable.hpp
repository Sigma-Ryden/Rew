#ifndef REW_REFLECTABLE_HPP
#define REW_REFLECTABLE_HPP

#include <cstddef> // size_t

#include <Rew/Registry.hpp>
#include <Rew/Injection.hpp>

#include <Rew/Detail/Meta.hpp>
#include <Rew/Detail/Macro.hpp>

#define CUSTOM_TEMPLATE_REFLECTABLE_DECLARATION(template_header, ...)                                   \
    REW_DEPAREN(template_header) struct xxrew_traits<__VA_ARGS__> {                                     \
        using R = typename ::xxrew_alias<__VA_ARGS__>::R;

#define CUSTOM_CONDITIONAL_REFLECTABLE_DECLARATION(...)                                                 \
    template <typename DirtyR> struct xxrew_traits<DirtyR, std::enable_if_t<__VA_ARGS__>> {             \
        using R = typename ::xxrew_alias<DirtyR>::R;

#define CUSTOM_REFLECTABLE_DECLARATION(...)                                                             \
    template <> struct xxrew_traits<__VA_ARGS__> {                                                      \
        using R = typename ::xxrew_alias<__VA_ARGS__>::R;

#define TEMPLATE_REFLECTABLE_DECLARATION(template_header, ...)                                          \
    CUSTOM_TEMPLATE_REFLECTABLE_DECLARATION(template_header, __VA_ARGS__)                               \
        LAZY_REFLECTABLE()                                                                              \
        REFLECTABLE_REGISTRY(&rew::global)

#define CONDITIONAL_REFLECTABLE_DECLARATION(...)                                                        \
    CUSTOM_CONDITIONAL_REFLECTABLE_DECLARATION(__VA_ARGS__)                                             \
        LAZY_REFLECTABLE()                                                                              \
        REFLECTABLE_REGISTRY(&rew::global)

#define REFLECTABLE_DECLARATION(...)                                                                    \
    CUSTOM_REFLECTABLE_DECLARATION(__VA_ARGS__)                                                         \
        REFLECTABLE_REGISTRY(&rew::global)                                                              \
        REFLECTABLE_NAME(#__VA_ARGS__)

#define REFLECTABLE_REGISTRY(...)  static auto registry() { return __VA_ARGS__; }
#define REFLECTABLE_NAME(...) static auto name() { return __VA_ARGS__; }
#define LAZY_REFLECTABLE(...) static auto lazy() { __VA_ARGS__ }
#define BUILTIN_REFLECTABLE(...) static auto builtin() { __VA_ARGS__ }

#define REFLECTABLE_DECLARATION_INIT(...)                                                               \
        };


#define TEMPLATE_REFLECTABLE(template_header, ...)                                                      \
    REW_DEPAREN(template_header) struct xxrew<__VA_ARGS__> {                                            \
        using R = __VA_ARGS__;                                                                          \
        using CleanR = typename ::xxrew_alias<R>::R;                                                    \
        REW_REFLECTABLE_BODY()

#define CONDITIONAL_REFLECTABLE(...)                                                                    \
    template <typename R> struct xxrew<R, std::enable_if_t<__VA_ARGS__>> {                              \
        using CleanR = typename ::xxrew_alias<R>::R;                                                    \
        REW_REFLECTABLE_BODY()

#define REFLECTABLE(...)                                                                                \
    template <> struct xxrew<__VA_ARGS__> {                                                             \
        using R = __VA_ARGS__;                                                                          \
        using CleanR = typename ::xxrew_alias<R>::R;                                                    \
        REW_REFLECTABLE_BODY()

#define REW_REFLECTABLE_BODY()                                                                          \
    template <class InjectionType> static void evaluate(InjectionType&& injection) {                    \
        auto xxtype = rew::find_or_add_type<R>();                                                       \
        rew::add_default_injection_set<R>(xxtype);                                                      \
        auto xxreflection = xxtype->reflection; (void)xxreflection;                                     \
        injection.template type<R>(*xxtype);

#ifdef REW_DISABLE_AUTOGENERATION
    #define REFLECTABLE_INIT(...)                                                                       \
            }                                                                                           \
            inline static auto xxautogenerated = false;                                                 \
        };
#else
    #define REFLECTABLE_INIT(...)                                                                       \
            }                                                                                           \
            inline static auto xxautogenerated = (evaluate(rew::injectable_t{}), true);                 \
        };
#endif // REW_DISABLE_AUTOGENERATION


#define CUSTOM_REFLECTABLE_INJECTION_DECLARATION(injection_index, ...)                                  \
    template <> struct xxrew_injection<injection_index> { using R = __VA_ARGS__; };                     \
    CUSTOM_REFLECTABLE_DECLARATION(__VA_ARGS__)

#define REFLECTABLE_INJECTION_DECLARATION(injection_index, ...)                                         \
    CUSTOM_REFLECTABLE_INJECTION_DECLARATION(injection_index, __VA_ARGS__)                              \
        REFLECTABLE_NAME(#__VA_ARGS__)


#define TEMPLATE_REFLECTABLE_CLEAN(template_header, type, ...)                                          \
    REW_DEPAREN(template_header) struct xxrew_alias<REW_DEPAREN(type)> { using R = __VA_ARGS__; };

#define REFLECTABLE_CLEAN(type, ...)                                                                    \
    template <> struct xxrew_alias<type> { using R = __VA_ARGS__; };

#define TEMPLATE_REFLECTABLE_USING(template_header, alias, alias_full, ...)                             \
    REW_DEPAREN(template_header) struct alias : rew::meta::inherits<__VA_ARGS__> {};                    \
    TEMPLATE_REFLECTABLE_CLEAN(template_header, alias_full, __VA_ARGS__)

#define REFLECTABLE_USING(alias, ...)                                                                   \
    struct alias : rew::meta::inherits<__VA_ARGS__> {};                                                 \
    REFLECTABLE_CLEAN(alias, __VA_ARGS__)


#define REFLECTABLE_ACCESS(...) template <typename, typename> friend struct xxrew;

namespace rew
{

template <typename ReflectableType>
std::string nameof()
{
    return ::xxrew_traits<ReflectableType>::name();
}

template <typename ReflectableType>
using cleanof = typename ::xxrew_alias<ReflectableType>::R;

template <typename ReflectableType>
void reflectable()
{
    static auto locked = false;
    if (!locked)
    {
        locked = true;
        ::xxrew<ReflectableType>::evaluate(injectable_t{});
    }
}

template <typename ReflectableType>
ReflectableType&& reflectable(ReflectableType&& object)
{
    reflectable<std::decay_t<ReflectableType>>();
    return std::forward<ReflectableType>(object);
}

template <typename DirtyReflectableType>
type_t* find_or_add_type()
{
    using dirty_reflectable_type = typename std::conditional_t
    <
        std::is_reference_v<DirtyReflectableType>,
        meta::to_reflectable_reference<DirtyReflectableType>,
        std::conditional_t
        <
            std::is_pointer_v<DirtyReflectableType>,
            meta::to_reflectable_pointer<DirtyReflectableType>,
            meta::to_reflectable_object<DirtyReflectableType>
        >
    >::type;

    using reflectable_type = typename ::xxrew_alias<dirty_reflectable_type>::R;
    using reflectable_traits = ::xxrew_traits<dirty_reflectable_type>;

    if constexpr (meta::is_lazy<dirty_reflectable_type>::value)
    {
        reflectable<dirty_reflectable_type>();
    }

    auto xxname = reflectable_traits::name();
    auto xxregistry = reflectable_traits::registry();

    auto xxtype = xxregistry->all[xxname];
    if (xxtype == nullptr)
    {
        xxtype = xxregistry->template add<reflectable_type, dirty_reflectable_type>(xxname);
    }

    return xxtype;
}

template <typename ReflectableType, typename ParentReflectableType>
parent_t* find_or_add_parent(reflection_t* reflection)
{
    static_assert(std::is_base_of_v<ParentReflectableType, ReflectableType>);

    auto xxname = ::xxrew_traits<ParentReflectableType>::name();

    auto xxmeta = reflection->parent.find(xxname);
    if (xxmeta == nullptr) xxmeta = &reflection->parent.add
    (
        xxname,
        {
            xxname,
            find_or_add_type<ParentReflectableType>(),
            handler_parent_cast<ReflectableType, ParentReflectableType>()
        }
    );

    return xxmeta;
}

namespace detail
{

template <typename... ArgumentTypes, typename ReturnType>
auto function_argument_types(ReturnType(*unused)(ArgumentTypes...))
{
    return std::vector<type_t*>({ find_or_add_type<ArgumentTypes>()... });
}

template <typename... ArgumentTypes, typename ReturnType>
auto function_return_type(ReturnType(*unused)(ArgumentTypes...))
{
    return find_or_add_type<ReturnType>();
}

} // namespace detail

template <typename DirtyFactoryType>
factory_t* find_or_add_factory(reflection_t* reflection)
{
    using function_traits = meta::function_traits<DirtyFactoryType>;
    using dirty_type = typename function_traits::dirty_type;
    using dirty_pointer = typename function_traits::dirty_pointer;
    using pointer = typename function_traits::pointer;

    auto xxname = ::xxrew_traits<dirty_type>::name();

    auto xxmeta = reflection->factory.find(xxname);
    if (xxmeta == nullptr) xxmeta = &reflection->factory.add
    (
        xxname,
        {
            xxname,
            handler_factory_call(pointer{}),
            detail::function_argument_types(dirty_pointer{}),
            detail::function_return_type(dirty_pointer{})
        }
    );

    return xxmeta;
}

template <typename DirtyFunctionType = void, typename FunctionType>
function_t* find_or_add_function(reflection_t* reflection, std::string const& name, FunctionType ptr)
{
    using function_traits = meta::function_traits
    <
        typename std::conditional_t
        <
            std::is_void_v<DirtyFunctionType>,
            meta::type_identity<FunctionType>,
            meta::mark_dirty<FunctionType, DirtyFunctionType>
        >::type
    >;

    using dirty_type = typename function_traits::dirty_type;
    using dirty_pointer = typename function_traits::dirty_pointer;

    auto xxfunction = reflection->function.find(name);
    if (xxfunction == nullptr) xxfunction = &reflection->function.add(name, {});

    auto xxoverload = ::xxrew_traits<dirty_type>::name();

    auto xxmeta = xxfunction->find(xxoverload);
    if (xxmeta == nullptr) xxmeta = &xxfunction->add
    (
        xxoverload,
        {
            xxoverload,
            handler_function_call(ptr),
            detail::function_argument_types(dirty_pointer{}),
            detail::function_return_type(dirty_pointer{}),
            ptr
        }
    );

    return xxmeta;
}

template <typename DirtyPropertyType = void, typename GetterType, typename SetterType>
property_t* find_or_add_property(reflection_t* reflection, std::string const& name,
                                 GetterType getter, SetterType setter)
{
    using property_traits = meta::property_traits
    <
        typename std::conditional_t
        <
            std::is_void_v<DirtyPropertyType>,
            meta::type_identity<GetterType>,
            meta::mark_dirty<GetterType, DirtyPropertyType>
        >::type
    >;

    using dirty_type = typename property_traits::type;

    auto xxmeta = reflection->property.find(name);
    if (xxmeta == nullptr) xxmeta = &reflection->property.add
    (
        name,
        {
            name,
            find_or_add_type<dirty_type>(),
            handler_property_get(getter),
            handler_property_set(setter),
            handler_property_context(getter),
            property_pointer(getter, setter)
        }
    );

    return xxmeta;
}

template <typename MetaType>
std::any* find_or_add_meta(reflection_t* reflection, std::string const& name, const MetaType& data)
{
    auto xxmeta = reflection->meta.find(name);
    if (xxmeta == nullptr) xxmeta = &reflection->meta.add(name, data);

    return xxmeta;
}

template <typename ReflectableType, class InjectionType>
injection_t* find_or_add_injection(type_t* type)
{
    static_assert(std::is_base_of_v<injectable_t, InjectionType>);

    auto xxname = ::xxrew_traits<InjectionType>::name();

    auto xxmeta = type->injection.find(xxname);
    if (xxmeta == nullptr) xxmeta = &type->injection.add
    (
        xxname,
        {
            xxname,
            handler_injection_call<ReflectableType, InjectionType>()
        }
    );

    return xxmeta;
}

template <typename ReflectableType, std::size_t CurrentKey = 0, std::size_t MaxKey = 4>
void add_default_injection_set(type_t* type)
{
    using reflectable_traits = ::xxrew_injection<CurrentKey>;
    if constexpr (meta::is_complete<reflectable_traits>::value)
    {
        find_or_add_injection<ReflectableType, typename reflectable_traits::R>(type);
        if constexpr (CurrentKey < MaxKey)
        {
            add_default_injection_set<ReflectableType, CurrentKey + 1>(type);
        }
    }
}

} // namespace rew

#endif // REW_REFLECTABLE_HPP
