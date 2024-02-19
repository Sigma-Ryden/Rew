#ifndef REW_PARENT_HPP
#define REW_PARENT_HPP

#include <string> // string

#include <functional> // function

#include <Rew/Attribute.hpp>
#include <Rew/Meta.hpp>
#include <Rew/Utility.hpp>

#define RAW_PARENT(...)                                                                                 \
    {                                                                                                   \
        using __type = __VA_ARGS__;                                                                     \
        auto __meta = ::rew::find_or_add_parent<R, __type>(__reflection);                               \
        injection.template parent<R, __type>(*__meta);                                                  \
    }

#define PARENT(...) RAW_PARENT(__VA_ARGS__)

namespace rew
{

struct type_t;

struct parent_t
{
    const std::string name;
    type_t *const type = nullptr;
    const std::function<std::any(std::any& child_context)> cast = nullptr;
    attribute_t<std::any> meta;
};

namespace handler
{

template <typename ReflectableType, typename ParentReflectableType>
auto parent_cast()
{
    return [](std::any& child_context) -> std::any
    {
        return static_cast<ParentReflectableType*>(std::any_cast<ReflectableType*>(child_context));
    };
}

} // namespace handler

} // namespace rew

#endif // REW_PARENT_HPP
