#ifndef REW_PARENT_HPP
#define REW_PARENT_HPP

#include <string> // string
#include <any> // any

#include <functional> // function

#include <Rew/Attribute.hpp>
#include <Rew/Meta.hpp>

#define RAW_PARENT(...)                                                                                 \
    {                                                                                                   \
        auto __meta = rew::find_or_add_parent<R, __VA_ARGS__>(__reflection);                            \
        injection.template parent<R, __VA_ARGS__>(*__meta);                                             \
    }

#define PARENT(...) RAW_PARENT(__VA_ARGS__)

namespace rew
{

struct type_t;

struct parent_t
{
    const std::string name;
    type_t *const type = nullptr;
    const std::function<std::any(const std::any& child_context)> cast = nullptr;
    attribute_t<std::any> meta;
};

template <typename ReflectableType, typename ParentReflectableType>
auto handler_parent_cast()
{
    return [](const std::any& child_context) -> std::any
    {
        return static_cast<ParentReflectableType*>(std::any_cast<ReflectableType*>(child_context));
    };
}

} // namespace rew

#endif // REW_PARENT_HPP
