#ifndef REW_HPP
#define REW_HPP

#include <functional>
#include <map>
#include <any>
#include <string>
#include <vector>

#define CORE_REFLECTABLE(reflection_core, ...)                                                          \
    template <>                                                                                         \
    struct rew::detail::reflection_registry_impl_t<__VA_ARGS__> {                                       \
        using registry = reflection_registry_t<__VA_ARGS__>;                                            \
        using type = __VA_ARGS__;                                                                       \
        inline static const auto reflection = &reflection_core;                                         \
        inline static const auto name = #__VA_ARGS__;                                                   \
        inline static const auto instance = reflection_core.add<type>(name)

#define CORE_REFLECTABLE(reflection_core, ...)                                                          \
    template <>                                                                                         \
    struct rew::detail::reflection_registry_impl_t<__VA_ARGS__> {                                       \
        using registry = reflection_registry_t<__VA_ARGS__>;                                            \
        using type = __VA_ARGS__;                                                                       \
        inline static const auto reflection = &reflection_core;                                         \
        inline static const auto name = #__VA_ARGS__;                                                   \
        inline static const auto instance = reflection_core.add<type>(name)

#define REFLECTABLE(...) CORE_REFLECTABLE(::rew::reflection, __VA_ARGS__)

#define PROPERTY(...)                                                                                   \
    ->add_property({                                                                                    \
        #__VA_ARGS__,                                                                                   \
        registry::property_get_handler(&type::__VA_ARGS__),                                             \
        registry::property_set_handler(&type::__VA_ARGS__)                                              \
    })

#define FUNCTION(...)                                                                                   \
    ->add_function({                                                                                    \
        #__VA_ARGS__,                                                                                   \
        registry::function_is_static(&type::__VA_ARGS__),                                               \
        registry::function_call_handler(&type::__VA_ARGS__)                                             \
    })

#define PARENT(...)                                                                                     \
    ->add_parent({                                                                                      \
        #__VA_ARGS__,                                                                                   \
        registry::parent_get_handler<__VA_ARGS__>(),                                                    \
        registry::parent_reflection_handler(#__VA_ARGS__, reflection)                                   \
    })

#define FACTORY(...)                                                                                    \
    ->register_factory({                                                                                \
        #__VA_ARGS__,                                                                                   \
        registry::factory_call_handler<__VA_ARGS__>()                                                   \
    })

#define META(name, ...)                                                                                 \
    ->register_meta(name, __VA_ARGS__)

#define REFLECTABLE_INIT()                                                                              \
    ->register_factory({                                                                                \
        name,                                                                                           \
        registry::factory_call_handler()                                                                \
    }); };

namespace rew
{

namespace detail
{

template <typename, typename enable = void>
struct is_complete : std::false_type {};

template <typename T>
struct is_complete<T, std::void_t<decltype(sizeof(T))>> : std::true_type {};

template <class ClassType>
class reflection_registry_impl_t;

} // namespace detail

class property_t
{
public:
    struct meta_t
    {
        const char *const name = nullptr;

        const std::function<void(void *const, std::any&)> get = nullptr;
        const std::function<void(void *const, const std::any&)> set = nullptr;
    };

    std::map<const char*, meta_t> all;

public:
    meta_t* find(const char* name)
    {
        auto it = all.find(name);
        return it != all.end() ? &it->second : nullptr;
    }

    bool add(const char* name, const meta_t& meta)
    {
        return all.emplace(name, meta).second;
    }

    bool remove(const char* name)
    {
        return all.erase(name)>0;
    }
};

class function_t
{
public:
    struct meta_t
    {
        const char *const name = nullptr;
        const bool is_static = false;

        const std::function<void(void *const, std::any&, std::initializer_list<std::any>)> call = nullptr;
    };

    std::map<const char*, meta_t> all;

public:
    meta_t* find(const char* name)
    {
        auto it = all.find(name);
        return it != all.end() ? &it->second : nullptr;
    }

    bool add(const char* name, const meta_t& meta)
    {
        return all.emplace(name, meta).second;
    }

    bool remove(const char* name)
    {
        return all.erase(name)>0;
    }
};

struct reflection_t;

class parent_t
{
public:
    struct meta_t
    {
        const char *const name = nullptr;

        const std::function<void*(void *const)> get = nullptr;
        const std::function<reflection_t*(void)> reflection = nullptr;
    };

    std::map<const char*, meta_t> all;

public:
    meta_t* find(const char* name)
    {
        auto it = all.find(name);
        return it != all.end() ? &it->second : nullptr;
    }

    bool add(const char* name, const meta_t& meta)
    {
        return all.emplace(name, meta).second;
    }

    bool remove(const char* name)
    {
        return all.erase(name)>0;
    }
};

class factory_t
{
public:
    struct meta_t
    {
        const char *const name = nullptr;

        const std::function<void*()> call = nullptr;
    };

    std::map<const char*, meta_t> all;

public:
    meta_t* find(const char* name)
    {
        auto it = all.find(name);
        return it != all.end() ? &it->second : nullptr;
    }

    bool add(const char* name, const meta_t& meta)
    {
        return all.emplace(name, meta).second;
    }

    bool remove(const char* name)
    {
        return all.erase(name)>0;
    }
};

class meta_t
{
public:
    std::map<const char*, std::any> all;

public:
    std::any* find(const char* name)
    {
        auto it = all.find(name);
        return it != all.end() ? &it->second : nullptr;
    }

    bool add(const char* name, const std::any& data)
    {
        return all.emplace(name, data).second;
    }

    bool remove(const char* name)
    {
        return all.erase(name)>0;
    }
};

struct reflection_t
{
    const char *const name = nullptr;

    parent_t parent;
    property_t property;
    function_t function;
    factory_t factory;
    meta_t meta;
};

template <class ClassType>
class reflection_registry_t;

class reflection_core_t
{
public:
    std::map<const char*, reflection_t*> all;
    std::map<const char*, reflection_t*> rtti_all;

public:
    ~reflection_core_t()
    {
        for (auto& [name, reflection] : all) delete reflection;
    }

public:
    reflection_t* find(const char* name)
    {
        auto it = all.find(name);
        return it != all.end() ? it->second : nullptr;
    }

    reflection_t* find(const std::any& object)
    {
        auto it = rtti_all.find(object.type().name());
        return it != rtti_all.end() ? it->second : nullptr;
    }

    template <class ClassType>
    reflection_t* find()
    {
        return get(detail::reflection_registry_impl_t<ClassType>::name);
    }

    template <class ClassType>
    reflection_registry_t<ClassType>* add(const char* name)
    {
        auto reflection = new reflection_t{name};
        all.emplace(name, reflection);
        rtti_all.emplace(typeid(ClassType).name(), reflection);

        return std::launder(reinterpret_cast<reflection_registry_t<ClassType>*>(reflection));
    }
};

reflection_core_t reflection;

struct register_t : reflection_t
{
    template <typename PropertyType>
    void property(const property_t::meta_t& meta)
    {
        reflection_t::property.add(meta.name, meta);
    }

    template <typename FunctionType>
    void function(const function_t::meta_t& meta)
    {
        reflection_t::function.add(meta.name, meta);
    }

    template <class BaseClassType, class DerivedClassType>
    void parent(const parent_t::meta_t& meta)
    {
        reflection_t::parent.add(meta.name, meta);
    }

    // TODO with args
    template <class OtherClassType>
    void factory(const factory_t::meta_t& meta)
    {
        reflection_t::factory.add(meta.name, meta);
    }

    template <typename MetaType>
    void meta(const char* name, const std::any& data)
    {
        reflection_t::meta.add(name, data);
    }
};

template <class ClassType>
class reflection_registry_t : public reflection_t
{
public:
    template <typename PropertyType>
    static auto property_get_handler(PropertyType ClassType::* property)
    {
        return [property](void *const self, std::any& result)
        {
            result = static_cast<ClassType*>(self)->*property;
        };
    }

    template <typename PropertyType>
    static auto property_set_handler(PropertyType ClassType::* property)
    {
        return [property](void *const self, const std::any& value)
        {
            static_cast<ClassType*>(self)->*property = std::any_cast<const PropertyType&>(value);
        };
    }

    reflection_registry_t* add_property(const property_t::meta_t& meta)
    {
        this->property.add(meta.name, meta);
        //register_t::property<PropertyType>(meta);
        return this;
    }

public:
    template <typename ReturnType, typename... ArgumentTypes>
    static auto function_call_handler(ReturnType (ClassType::* function)(ArgumentTypes...))
    {
        return function_call_handler_impl(function, std::make_index_sequence<sizeof...(ArgumentTypes)>{});
    }

    template <typename ReturnType, typename... ArgumentTypes>
    static auto function_call_handler(ReturnType (*function)(ArgumentTypes...))
    {
        return function_call_handler_impl(function, std::make_index_sequence<sizeof...(ArgumentTypes)>{});
    }

    template <typename ReturnType, typename... ArgumentTypes>
    static auto function_is_static(ReturnType (ClassType::* function)(ArgumentTypes...))
    {
        return false;
    }

    template <typename ReturnType, typename... ArgumentTypes>
    static auto function_is_static(ReturnType (*function)(ArgumentTypes...))
    {
        return true;
    }

    reflection_registry_t* add_function(const function_t::meta_t& meta)
    {
        this->function.add(meta.name, meta);
        //register_t::function<FunctionType>(meta);
        return this;
    }

private:
    template <typename ReturnType, typename... ArgumentTypes, std::size_t... I>
    static auto function_call_handler_impl(ReturnType (ClassType::* function)(ArgumentTypes...), std::index_sequence<I...>)
    {
        return [function](void *const self, std::any& result, std::initializer_list<std::any> arguments)
        {
            result = (static_cast<ClassType*>(self)->*function)(std::any_cast<ArgumentTypes>(arguments.begin()[I])...);
        };
    }

    template <typename... ArgumentTypes, std::size_t... I>
    static auto function_call_handler_impl(void (ClassType::* function)(ArgumentTypes...), std::index_sequence<I...>)
    {
        return [function](void *const self, std::any& result, std::initializer_list<std::any> arguments)
        {
            (static_cast<ClassType*>(self)->*function)(std::any_cast<ArgumentTypes>(arguments.begin()[I])...);
            result.reset();
        };
    }

    template <typename ReturnType, typename... ArgumentTypes, std::size_t... I>
    static auto function_call_handler_impl(ReturnType (*function)(ArgumentTypes...), std::index_sequence<I...>)
    {
        return [function](void *const self, std::any& result, std::initializer_list<std::any> arguments)
        {
            result = function(std::any_cast<ArgumentTypes>(arguments.begin()[I])...);
        };
    }

    template <typename... ArgumentTypes, std::size_t... I>
    static auto function_call_handler_impl(void (*function)(ArgumentTypes...), std::index_sequence<I...>)
    {
        return [function](void *const self, std::any& result, std::initializer_list<std::any> arguments)
        {
            function(std::any_cast<ArgumentTypes>(arguments.begin()[I])...);
            result.reset();
        };
    }

public:
    template <class ParentClassType>
    static auto parent_get_handler()
    {
        return [](void *const self)
        {
            return static_cast<ParentClassType*>(static_cast<ClassType*>(self));
        };
    }

    static auto parent_reflection_handler(const char* name, reflection_core_t* reflection)
    {
        return [name, reflection](void)
        {
            return reflection->find(name);
        };
    }

    reflection_registry_t* add_parent(const parent_t::meta_t& meta)
    {
        this->parent.add(meta.name, meta);
        //register_t::parent<OtherClassType, ClassType>(meta);
        return this;
    }

public:
    template <class OtherClassType = ClassType>
    static auto factory_call_handler()
    {
        return [](void)
        {
            return static_cast<void*>(new OtherClassType);
        };
    }

    reflection_registry_t* register_factory(const factory_t::meta_t& meta)
    {
        this->factory.add(meta.name, meta);
        //register_t::factory<OtherClassType>(meta);
        return this;
    }

public:
    reflection_registry_t* register_meta(const char* name, const std::any& data)
    {
        this->meta.add(name, data);
        //register_t::meta<MetaType>(meta);
        return this;
    }
};

} // namespace rew

#endif // REW_HPP
