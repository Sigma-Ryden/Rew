#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/string.hpp>
#include <Rew/BuiltIn/any.hpp>
#include <Rew/BuiltIn/function.hpp>
#include <Rew/BuiltIn/vector.hpp>
#include <Rew/BuiltIn/unordered_map.hpp>
#include <Rew/BuiltIn/typeindex.hpp>

TEMPLATE_REFLECTABLE_DECLARATION((template <typename MetaType>), rew::attribute_t<MetaType>)
    REFLECTABLE_NAME("rew::attribute_t<" + NAMEOF(MetaType) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename MetaType>), rew::attribute_t<MetaType>)
    FUNCTION(find)
    FUNCTION(add)
    FUNCTION(remove)
    PROPERTY(all)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(rew::type_t)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(rew::parent_t)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(rew::parent_t)
    PROPERTY(name)
    PROPERTY(type)
    PROPERTY(cast)
    PROPERTY(meta)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(rew::function_t)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(rew::function_t)
    PROPERTY(name)
    PROPERTY(call)
    PROPERTY(arguments)
    PROPERTY(result)
    PROPERTY(pointer)
    PROPERTY(meta)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(rew::factory_t)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(rew::factory_t)
    PROPERTY(name)
    PROPERTY(call)
    PROPERTY(arguments)
    PROPERTY(meta)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(rew::property_t)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(rew::property_t)
    PROPERTY(name)
    PROPERTY(type)
    PROPERTY(get)
    PROPERTY(set)
    PROPERTY(context)
    PROPERTY(meta)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(rew::reflection_t)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(rew::reflection_t)
    PROPERTY(name)
    PROPERTY(parent)
    PROPERTY(function)
    PROPERTY(factory)
    PROPERTY(property)
    PROPERTY(meta)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(rew::injection_t)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(rew::type_t)
    PROPERTY(name)
    PROPERTY(reflection)
    PROPERTY(size)
    PROPERTY(context)
    PROPERTY(injection)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(rew::registry_t)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(rew::registry_t)
    FACTORY(rew::registry_t())
    FUNCTION(find, rew::type_t*(const std::string&) const)
    FUNCTION(find, rew::type_t*(std::type_index) const)
    FUNCTION(find, rew::type_t*(std::any&) const)
    PROPERTY(all)
    PROPERTY(rtti_all)
REFLECTABLE_INIT()

TEST(TestReflection, TestSelfReflection)
{
}

struct TestReflectionProperty
{
    int f() { return 0; }
    void f(int) {}

    const int g() { return 0; }

    const int i = 0;

    int j = 0;
};

REFLECTABLE_DECLARATION(TestReflectionProperty)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestReflectionProperty)
    PROPERTY(f)
    PROPERTY(g)
    PROPERTY(i)
    PROPERTY(j)
REFLECTABLE_INIT()

TEST(TestReflection, TestProperty)
{
}
