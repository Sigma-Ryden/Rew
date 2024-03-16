#ifndef REW_REGISTRY_HPP
#define REW_REGISTRY_HPP

#include <string> // string
#include <unordered_map> // unordered_map

#include <typeindex> // type_index

#include <Rew/Type.hpp>
#include <Rew/Reflection.hpp>

#define REW_REGISTRY_RESERVE_SIZE std::size_t(4096)

namespace rew
{

class registry_t
{
public:
    std::unordered_map<std::string, type_t*> all;
    std::unordered_map<std::type_index, type_t*> rtti_all;

public:
    registry_t()
    {
        all.reserve(REW_REGISTRY_RESERVE_SIZE);
    }

    ~registry_t()
    {
        for (auto& [name, meta] : all)
        {
            delete meta->reflection;
            delete meta;
        }
    }

    type_t* find(const std::string& name)
    {
        auto it = all.find(name);
        return it != all.end() ? it->second : nullptr;
    }

    type_t* find(std::type_index typeindex)
    {
        auto it = rtti_all.find(typeindex);
        return it != rtti_all.end() ? it->second : nullptr;
    }

    type_t* find(std::any& object)
    {
        return find(object.type());
    }

    template <typename ReflectableType>
    type_t* find()
    {
        return find(meta::reflectable_traits<ReflectableType>::name());
    }

private:
    template <typename ReflectableType>
    auto context()
    {
        return [](std::any& object)
    	{
	    return std::addressof(std::any_cast<ReflectableType&>(object));
    	};
    }

    template <typename ReflectableType>
    auto size()
    {
    	return sizeof(ReflectableType);
    }

public:
    template <typename ReflectableType, typename DirtyReflectableType = ReflectableType>
    type_t* add(const std::string& name)
    {
        auto& type = all[name];
        if (type != nullptr) return type;

        type = new type_t
        {
            name,
            new reflection_t { name },
            size<ReflectableType>(),
            context<ReflectableType>()
        };

        rtti_all.emplace(typeid(DirtyReflectableType), type);

        return type;
    }
};

template <>
inline auto registry_t::context<std::any>()
{
    return [](std::any& object)
    {
        return std::addressof(object);
    };
}

template <>
inline auto registry_t::context<void>()
{
    return nullptr;
}

template <>
inline auto registry_t::size<void>()
{
    return std::size_t(0);
}

inline registry_t global;

} // namespace rew

#endif // REW_REGISTRY_HPP
