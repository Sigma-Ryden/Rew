#ifndef REW_REFLECTABLE_HPP
#define REW_REFLECTABLE_HPP

#include <Rew/Registry.hpp>
#include <Rew/Detail/Meta.hpp>

#define __REW_EXPAND(...) __VA_ARGS__

#define NAMEOF(...) (::rew::meta::reflectable_traits<__VA_ARGS__>::name())

#define CORE_REFLECTABLE_BODY(...)                                                                      \
    struct eval_t {                                                                                     \
        template <class VisitorType>                                                                    \
        eval_t(VisitorType&& visitor) {                                                                 \
            using __reflectable_traits = __VA_ARGS__;                                                   \
            using __reflectable_type = typename __reflectable_traits::type;                             \
            static auto __reflectable_name = __reflectable_traits::name();                              \
            static auto __reflectable_registry = __reflectable_traits::registry();                      \
            auto __type = __reflectable_registry->all[__reflectable_name];                              \
            if (__type == nullptr) __type = __reflectable_registry->template add<__reflectable_type>(   \
                __reflectable_name                                                                      \
            );                                                                                          \
            auto __reflection = __type->reflection;                                                     \
            visitor.template type<__reflectable_type>(*__type);

#define CORE_TEMPLATE_REFLECTABLE_DECLARATION(template_header, reflectable_type)                        \
    namespace rew { namespace meta {                                                                    \
        __REW_EXPAND template_header                                                                    \
        struct reflectable_traits<__REW_EXPAND reflectable_type> : conditional_reflectable_traits {     \
            using type = __REW_EXPAND reflectable_type;                                                 \
            using R = type;

#define CORE_CONDITIONAL_REFLECTABLE_DECLARATION(...)                                                   \
    namespace rew { namespace meta {                                                                    \
        template <typename R>                                                                           \
        struct reflectable_traits<R, std::enable_if_t<__VA_ARGS__>> : conditional_reflectable_traits {  \
            using type = R;

#define CORE_REFLECTABLE_DECLARATION(...)                                                               \
    namespace rew { namespace meta {                                                                    \
        template <> struct reflectable_traits<__VA_ARGS__> : base_reflectable_traits {                  \
            using type = __VA_ARGS__;                                                                   \
            using R = type;

#define REFLECTABLE_REGISTRY(...)                                                                       \
    static const auto registry() { return __VA_ARGS__; }                                                \

#define REFLECTABLE_NAME(...)                                                                           \
    static const std::string name() { return __VA_ARGS__; }

#define BUILTIN_REFLECTABLE(...)                                                                        \
    static auto builtin() { __VA_ARGS__ }

#define REFLECTABLE_DECLARATION_INIT(...)                                                               \
        };                                                                                              \
    }}

#define CORE_TEMPLATE_REFLECTABLE(template_header, reflectable_type)                                    \
    __REW_EXPAND template_header                                                                        \
    struct rew_reflection_registry_t<__REW_EXPAND reflectable_type> {                                   \
        using R = __REW_EXPAND reflectable_type;                                                        \
        CORE_REFLECTABLE_BODY(::rew::meta::reflectable_traits<R>)

#define CORE_CONDITIONAL_REFLECTABLE(...)                                                               \
    template <typename R>                                                                               \
    struct rew_reflection_registry_t<R, std::enable_if_t<__VA_ARGS__>> {                                \
        CORE_REFLECTABLE_BODY(::rew::meta::reflectable_traits<R>)

#define CORE_REFLECTABLE(...)                                                                           \
    template <> struct rew_reflection_registry_t<__VA_ARGS__> {                                         \
        using R = __VA_ARGS__;                                                                          \
        CORE_REFLECTABLE_BODY(::rew::meta::reflectable_traits<R>)

#define CORE_REFLECTABLE_INIT(...)                                                                      \
            }                                                                                           \
        };                                                                                              \
    private:                                                                                            \
        inline static auto _ = eval_t(::rew::visitor_t{});                                              \
    };                                                                                                  \

#define REFLECTABLE_ACCESS(...)                                                                         \
    template <typename, typename> friend struct rew_reflection_registry_t;

#ifndef TEMPLATE_REFLECTABLE_DECLARATION
    #define TEMPLATE_REFLECTABLE_DECLARATION(template_header, reflectable_type)                         \
        CORE_TEMPLATE_REFLECTABLE_DECLARATION(template_header, reflectable_type)                        \
        REFLECTABLE_REGISTRY(&::rew::global)
#endif // CONDITIONAL_REFLECTABLE_DECLARATION

#ifndef CONDITIONAL_REFLECTABLE_DECLARATION
    #define CONDITIONAL_REFLECTABLE_DECLARATION(...)                                                    \
        CORE_CONDITIONAL_REFLECTABLE_DECLARATION(__VA_ARGS__)                                           \
        REFLECTABLE_REGISTRY(&::rew::global)
#endif // CONDITIONAL_REFLECTABLE_DECLARATION

#ifndef REFLECTABLE_DECLARATION
    #define REFLECTABLE_DECLARATION(...)                                                                \
        CORE_REFLECTABLE_DECLARATION(__VA_ARGS__)                                                       \
        REFLECTABLE_REGISTRY(&::rew::global)                                                            \
        REFLECTABLE_NAME(#__VA_ARGS__)
#endif // REFLECTABLE_DECLARATION

#ifndef TEMPLATE_REFLECTABLE
    #define TEMPLATE_REFLECTABLE(template_header, reflectable_type)                                     \
        CORE_TEMPLATE_REFLECTABLE(template_header, reflectable_type)
#endif // CONDITIONAL_REFLECTABLE

#ifndef CONDITIONAL_REFLECTABLE
    #define CONDITIONAL_REFLECTABLE(...) CORE_CONDITIONAL_REFLECTABLE(__VA_ARGS__)
#endif // CONDITIONAL_REFLECTABLE

#ifndef REFLECTABLE
    #define REFLECTABLE(...) CORE_REFLECTABLE(__VA_ARGS__)
#endif // REFLECTABLE

#ifndef REFLECTABLE_INIT
    #define REFLECTABLE_INIT(...) CORE_REFLECTABLE_INIT(__VA_RGS__)
#endif // REFLECTABLE_INIT

namespace rew
{

template <typename ReflectableType>
void reflectable()
{
    if constexpr (std::is_base_of_v<meta::conditional_reflectable_traits,
                                    meta::reflectable_traits<ReflectableType>>)
    {
        (void)::rew_reflection_registry_t<ReflectableType>{}; // explicit instancing
    }
}

template <typename ReflectableType>
ReflectableType&& reflectable(ReflectableType&& object)
{
    reflectable<std::decay_t<ReflectableType>>();
    return std::forward<ReflectableType>(object);
}

template <typename ReflectableType, typename ParentReflectableType>
parent_t* find_or_add_parent(reflection_t* reflection)
{
    using traits = meta::reflectable_traits<ParentReflectableType>;

    static_assert(std::is_base_of_v<ParentReflectableType, ReflectableType>);
    reflectable<ParentReflectableType>();

    auto __name = traits::name();

    auto __meta = reflection->parent.find(__name);
    if (__meta == nullptr) __meta = &reflection->parent.add
    (
        __name,
        {
            __name,
            traits::registry()->all[__name],
            handler::parent_cast<ReflectableType, ParentReflectableType>()
        }
    );

    return __meta;
}

template <typename FactoryType>
factory_t* find_or_add_factory(reflection_t* reflection)
{
    using traits = meta::function_traits<FactoryType>;
    using function_type = typename traits::function_type;
    using return_type = typename traits::return_type;

    reflectable<return_type>();

    auto __name = utility::full_factory_name(function_type{});

    auto __meta = reflection->factory.find(__name);
    if (__meta == nullptr) __meta = &reflection->factory.add
    (
        __name,
        {
            __name,
            handler::factory_call(function_type{}),
            utility::function_arg_count(function_type{}),
        }
    );

    return __meta;
}

template <typename FunctionType>
function_t* find_or_add_function(reflection_t* reflection, const std::string& name, FunctionType ptr)
{
    auto __name = utility::full_function_name(name, ptr);

    auto __meta = reflection->function.find(__name);
    if (__meta == nullptr) __meta = &reflection->function.add
    (
        __name,
        {
            __name,
            handler::function_call(ptr),
            utility::function_arg_count(ptr)
        }
    );

    return __meta;
}

template <typename PropertyGetterType, typename PropertySetterType>
property_t* find_or_add_property(reflection_t* reflection, const std::string& name, PropertyGetterType getter, PropertySetterType setter)
{
    using type = typename meta::property_traits<decltype(getter)>::property_type;
    using traits = meta::reflectable_traits<type>;

    reflectable<type>();

    auto __meta = reflection->property.find(name);
    if (__meta == nullptr) __meta = &reflection->property.add
    (
        name,
        {
            name,
            traits::registry()->all[traits::name()],
            handler::property_get(getter),
            handler::property_set(setter),
            handler::property_ptr(getter)
        }
    );

    return __meta;
}

template <typename MetaType>
std::any* find_or_add_meta(reflection_t* reflection, const std::string& name, MetaType& data)
{
    auto __meta = reflection->meta.find(name);
    if (__meta == nullptr) __meta = &reflection->meta.add(name, data);

    return __meta;
}

} // namespace rew

#endif // REW_REFLECTABLE_HPP
