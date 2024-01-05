#ifndef REW_REFLECTABLE_HPP
#define REW_REFLECTABLE_HPP

#include <Rew/Registry.hpp>
#include <Rew/Detail/Meta.hpp>

#define CORE_REFLECTABLE_BODY(...)                                                                      \
        struct eval_t {                                                                                 \
            template <class VisitorType> eval_t(VisitorType&& visitor) {                                \
                using reflectable = typename traits_t::type;                                            \
                static auto name = traits_t::name();                                                    \
                static auto registry = traits_t::registry();                                            \
                auto type = registry->all[name];                                                        \
                if (type == nullptr) type = registry->template add<reflectable>(name);                  \
                auto reflection = type->reflection;                                                     \
                visitor.template type<reflectable>(*type);

#define CORE_REFLECTABLE_DECLARATION(reflection_registry, ...)                                          \
    namespace rew { namespace meta {                                                                    \
        template <> struct reflectable_name_t<__VA_ARGS__> {                                            \
            static std::string get() { return #__VA_ARGS__; }                                           \
        };                                                                                              \
        template <> struct reflectable_traits_t<__VA_ARGS__> {                                          \
            using type = __VA_ARGS__;                                                                   \
            static constexpr auto conditional = false;                                                  \
            static const auto name() { return reflectable_name_t<type>::get(); }                        \
            static const auto registry() { return &reflection_registry; }                               \
        };                                                                                              \
    }}

#define CORE_CONDITIONAL_REFLECTABLE_DECLARATION(reflection_registry, ...)                              \
    namespace rew { namespace meta {                                                                    \
        template <typename T> struct reflectable_traits_t<T, std::enable_if_t<__VA_ARGS__>> {           \
            using type = T;                                                                             \
            static constexpr auto conditional = true;                                                   \
            static const auto name() { return reflectable_name_t<type>::get(); }                        \
            static const auto registry() { return &reflection_registry; }                               \
        };                                                                                              \
    }}

#define CORE_REFLECTABLE(reflection_registry, ...)                                                      \
    CORE_REFLECTABLE_DECLARATION(reflection_registry, __VA_ARGS__)                                      \
    template <> struct rew_reflection_registry_t<__VA_ARGS__> {                                         \
        using traits_t = ::rew::meta::reflectable_traits_t<__VA_ARGS__>;                                \
        CORE_REFLECTABLE_BODY(__VA_ARGS__)

#define CORE_CONDITIONAL_REFLECTABLE(reflection_registry, ...)                                          \
    CORE_CONDITIONAL_REFLECTABLE_DECLARATION(reflection_registry, __VA_ARGS__)                          \
    template <typename T> struct rew_reflection_registry_t<T, std::enable_if_t<__VA_ARGS__>> {          \
        using traits_t = ::rew::meta::reflectable_traits_t<T>;                                          \
        CORE_REFLECTABLE_BODY(__VA_ARGS__)

#define CORE_REFLECTABLE_INIT(...)                                                                      \
            }                                                                                           \
        };                                                                                              \
    private:                                                                                            \
        inline static auto _ = eval_t(::rew::visitor_t{});                                              \
    };                                                                                                  \

#define REFLECTABLE_ACCESS(...)                                                                         \
    template <typename, typename> friend struct rew_reflection_registry_t;

#ifndef REFLECTABLE_DECLARATION
    #define REFLECTABLE_DECLARATION(...)                                                                \
        CORE_REFLECTABLE_DECLARATION(::rew::global, __VA_ARGS__)
#endif // REFLECTABLE_DECLARATION

#ifndef REFLECTABLE
    #define REFLECTABLE(...)                                                                            \
        CORE_REFLECTABLE(::rew::global, __VA_ARGS__)
#endif // REFLECTABLE

#ifndef CONDITIONAL_REFLECTABLE
    #define CONDITIONAL_REFLECTABLE(...)                                                                \
        CORE_CONDITIONAL_REFLECTABLE(::rew::global, __VA_ARGS__)
#endif // REFLECTABLE

#ifndef REFLECTABLE_INIT
    #define REFLECTABLE_INIT(...)                                                                       \
        CORE_REFLECTABLE_INIT(__VA_RGS__)
#endif // REFLECTABLE_INIT

#endif // REW_REFLECTABLE_HPP
