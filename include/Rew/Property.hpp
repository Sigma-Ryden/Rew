#ifndef REW_PROPERTY_HPP
#define REW_PROPERTY_HPP

#include <string> // string
#include <any> // any

#include <utility> // pair
#include <functional> // function
#include <memory> // addressof

#include <type_traits> // is_reference_v

#include <Rew/Attribute.hpp>
#include <Rew/Meta.hpp>

#include <Rew/Utility.hpp>

#include <Rew/Detail/Macro.hpp>

// .property<R,type>(name, &R::get, &R::set)
#define NAMED_PROPERTY(name_str, get, set, ...)                                                         \
    {                                                                                                   \
        using xxaccess = typename rew::meta::access_traits<CleanR>::template property<__VA_ARGS__>;     \
        auto [xxget, xxset] = xxaccess::of(&CleanR::REW_DEPAREN(get), &CleanR::REW_DEPAREN(set));       \
        auto xxmeta = rew::find_or_add_property<__VA_ARGS__>(xxreflection, name_str, xxget, xxset);     \
        injection.template property<CleanR, decltype(xxget), decltype(xxset)>(*xxmeta);                 \
    }

#define PROPERTY(name, ...) NAMED_PROPERTY(REW_TO_STRING(name), name, name, __VA_ARGS__)

// .property<type>(name, &get, &set)
#define NAMED_FREE_PROPERTY(name_str, get, set, ...)                                                    \
    {                                                                                                   \
        using xxaccess = typename rew::meta::access_traits<>::template property<__VA_ARGS__>;           \
        auto [xxget, xxset] = xxaccess::of(&REW_DEPAREN(get), &REW_DEPAREN(set));                       \
        auto xxmeta = rew::find_or_add_property<__VA_ARGS__>(xxreflection, name_str, xxget, xxset);     \
        injection.template property<CleanR, decltype(xxget), decltype(xxset)>(*xxmeta);                 \
    }

#define FREE_PROPERTY(name, ...) NAMED_FREE_PROPERTY(REW_TO_STRING(name), name, name, __VA_ARGS__)

namespace rew
{

struct type_t;

struct property_t
{
    std::string const name;
    type_t *const type = nullptr;
    std::function<void(std::any const& context, std::any& result)> const get = nullptr;
    std::function<void(std::any const& context, std::any const& value)> const set = nullptr;
    std::function<std::any(std::any const& outer_context)> const context = nullptr;
    std::pair<std::any, std::any> const pointer;
    attribute_t<std::any> meta;
};

namespace detail
{

template <typename ReflectableType, typename GetterType>
auto handler_property_get_impl(GetterType getter)
{
    return [getter](std::any const& context, std::any& value)
    {
        using type = typename meta::property_traits<GetterType>::type;

        value = utility::backward<type>
        (
            (std::any_cast<ReflectableType*>(context)->*getter)()
        );
    };
}

} // namespace detail

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType ReflectableType::* property)
{
    return [property](std::any const& context, std::any& result)
    {
        result = utility::forward<PropertyType>
        (
            std::any_cast<ReflectableType*>(context)->*property
        );
    };
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* getter)(void) const)
{
    return detail::handler_property_get_impl<ReflectableType>(getter);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* getter)(void) const&)
{
    return detail::handler_property_get_impl<ReflectableType>(getter);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* getter)(void))
{
    return detail::handler_property_get_impl<ReflectableType>(getter);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* getter)(void)&)
{
    return detail::handler_property_get_impl<ReflectableType>(getter);
}

template <typename PropertyType>
auto handler_property_get(PropertyType* property)
{
    return [property](std::any const&, std::any& result)
    {
        result = utility::forward<PropertyType>(*property);
    };
}

template <typename PropertyType>
auto handler_property_get(PropertyType(*getter)(void))
{
    return [getter](std::any const&, std::any& result)
    {
        result = utility::backward<PropertyType>(getter());
    };
}

namespace detail
{

template <typename ReflectableType, typename SetterType>
auto handler_property_set_impl(SetterType setter)
{
    return [setter](std::any const& context, std::any const& value)
    {
        using type = typename meta::property_traits<SetterType>::type;

        (std::any_cast<ReflectableType*>(context)->*setter)(utility::forward<type>(value));
    };
}

} // namespace detail

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType ReflectableType::* property)
{
    return [property](std::any const& context, std::any const& value)
    {
        std::any_cast<ReflectableType*>(context)->*property = utility::forward<PropertyType>(value);
    };
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType const ReflectableType::* property)
{
    return nullptr;
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(void(ReflectableType::* setter)(PropertyType))
{
    return detail::handler_property_set_impl<ReflectableType>(setter);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(void(ReflectableType::* setter)(PropertyType)&)
{
    return detail::handler_property_set_impl<ReflectableType>(setter);
}

template <typename PropertyType>
auto handler_property_set(PropertyType* property)
{
    return [property](std::any const&, std::any const& value)
    {
        *property = utility::forward<PropertyType>(value);
    };
}

template <typename PropertyType>
auto handler_property_set(PropertyType const* property)
{
    return nullptr;
}

template <typename PropertyType>
auto handler_property_set(void(*setter)(PropertyType))
{
    return [setter](std::any const&, std::any const& value)
    {
        setter(utility::forward<PropertyType>(value));
    };
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType(ReflectableType::* getter)(void) const)
{
    return nullptr;
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType(ReflectableType::* getter)(void) const&)
{
    return nullptr;
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType(ReflectableType::* getter)(void))
{
    return nullptr;
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType(ReflectableType::* getter)(void)&)
{
    return nullptr;
}

template <typename PropertyType>
auto handler_property_set(PropertyType(*getter)(void))
{
    return nullptr;
}

namespace detail
{

template <typename ReflectableType, typename GetterType>
auto handler_property_context_impl(GetterType getter)
{
    using type = typename meta::property_traits<GetterType>::type;
    if constexpr (std::is_reference_v<type>)
    {
        return [getter](std::any const& outer_context) -> std::any
        {
            return const_cast<typename meta::to_reflectable_reference<type>::type>
            (
                std::addressof((std::any_cast<ReflectableType*>(outer_context)->*getter)())
            );
        };
    }
    else
    {
        return nullptr;
    }
}

} // namespace detail

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType ReflectableType::* property)
{
    return [property](std::any const& outer_context) -> std::any
    {
        return const_cast<typename meta::to_reflectable_object<PropertyType>::type*>
        (
            std::addressof(std::any_cast<ReflectableType*>(outer_context)->*property)
        );
    };
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* getter)(void) const)
{
    return detail::handler_property_context_impl<ReflectableType>(getter);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* getter)(void) const&)
{
    return detail::handler_property_context_impl<ReflectableType>(getter);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* getter)(void))
{
    return detail::handler_property_context_impl<ReflectableType>(getter);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* getter)(void)&)
{
    return detail::handler_property_context_impl<ReflectableType>(getter);
}

template <typename PropertyType>
auto handler_property_context(PropertyType* property)
{
    return [property](std::any const&) -> std::any
    {
        return const_cast<typename meta::to_reflectable_object<PropertyType>::type*>(property);
    };
}

template <typename PropertyType>
auto handler_property_context(PropertyType(*getter)(void))
{
    if constexpr (std::is_reference_v<PropertyType>)
    {
        return [getter](std::any const&) -> std::any
        {
            return const_cast<typename meta::to_reflectable_reference<PropertyType>::type>
            (
                std::addressof(getter())
            );
        };
    }
    else
    {
        return nullptr;
    }
}

template <typename GetterType, typename SetterType>
constexpr auto property_pointer(GetterType get, SetterType set)
{
    return std::make_pair(get, set);
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType const ReflectableType::* get, PropertyType const ReflectableType::* set)
{
    return std::make_pair(get, std::any{});
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* get)(void) const, PropertyType(ReflectableType::* set)(void) const)
{
    return std::make_pair(get, std::any{});
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* get)(void) const&, PropertyType(ReflectableType::* set)(void) const&)
{
    return std::make_pair(get, std::any{});
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* get)(void), PropertyType(ReflectableType::* set)(void))
{
    return std::make_pair(get, std::any{});
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* get)(void)&, PropertyType(ReflectableType::* set)(void)&)
{
    return std::make_pair(get, std::any{});
}

template <typename PropertyType>
constexpr auto property_pointer(PropertyType(*get)(void), PropertyType(*set)(void))
{
    return std::make_pair(get, std::any{});
}

template <typename PropertyType>
constexpr auto property_pointer(PropertyType const* get, PropertyType const* set)
{
    return std::make_pair(get, std::any{});
}

} // namespace rew

#endif // REW_PROPERTY_HPP
