#ifndef REW_PARENT_HPP
#define REW_PARENT_HPP

#include <string> // string
#include <any> // any

#include <functional> // function

#include <Rew/Attribute.hpp>
#include <Rew/Meta.hpp>

// .parent<R, type>()
#define PARENT(...)                                                                                     \
    {                                                                                                   \
        auto __meta = rew::find_or_add_parent<CleanR, __VA_ARGS__>(__reflection);                       \
        injection.template parent<CleanR, __VA_ARGS__>(*__meta);                                        \
    }

namespace rew
{

struct type_t;

struct parent_t
{
    std::string const name;
    type_t *const type = nullptr;
    std::function<std::any(std::any const& child_context)> const cast = nullptr;
    attribute_t<std::any> meta;
};

template <typename ReflectableType, typename ParentReflectableType>
auto handler_parent_cast()
{
    return [](std::any const& child_context) -> std::any
    {
        return static_cast<ParentReflectableType*>(std::any_cast<ReflectableType*>(child_context));
    };
}

} // namespace rew

#endif // REW_PARENT_HPP
