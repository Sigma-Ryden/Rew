#ifndef REW_INJECTION_HPP
#define REW_INJECTION_HPP

#include <string> // string
#include <any> // any

#include <functional> // function

#include <Rew/Reflection.hpp>

namespace rew
{

struct type_t;
struct parent_t;
struct factory_t;
struct function_t;
struct property_t;

struct injectable_t
{
    virtual ~injectable_t() = default;

    template <typename ReflectableType>
    void type(rew::type_t& type) {}

    template <typename ReflectableType, typename ParentReflectableType>
    void parent(rew::parent_t& parent) {}

    template <typename ReflectableType, typename FunctionType>
    void factory(rew::factory_t& factory) {}

    template <typename ReflectableType, typename FunctionType>
    void function(rew::function_t& function) {}

    template <typename ReflectableType, typename PropertyType>
    void property(rew::property_t& property) {}

    template <typename ReflectableType, typename MetaType>
    void meta(const std::string& name, std::any& meta) {}
};

namespace meta
{

template <std::size_t InjectionIndex> struct injection_traits;

} // namespace meta

struct injection_t
{
    const std::string name;
    const std::function<void(injectable_t& injection)> call = nullptr;
};

template <typename ReflectionType, class InjectionType>
auto handler_injection_call()
{
    return [](injectable_t& injection)
    {
        using reflection_registry = rew_reflection_registry_t<ReflectionType>;
        reflection_registry::evaluate(dynamic_cast<InjectionType&>(injection));
    };
}

} // namespace rew

#endif // REW_INJECTION_HPP
