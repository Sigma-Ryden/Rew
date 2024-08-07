#include <RewTestingBase.hpp>

TEST_SPACE()
{

struct TestReflectableDeclaratonOnlyStruct {};
struct TestReflectableDeclaratonOnlyWithUsingStruct {};

struct TestReflectableStruct
{
    void Foo(TestReflectableDeclaratonOnlyWithUsingStruct) {}
};

struct TestReflectableWithoutDeclarationStruct {};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestReflectableDeclaratonOnlyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(TestReflectableDeclaratonOnlyWithUsingStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(TestReflectableStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestReflectableStruct)
    FUNCTION(Foo) // will implicitly add TestReflectableDeclaratonOnlyWithUsingStruct to registry
REFLECTABLE_INIT()

// will not compile, since rrquires REFLECTABLE_DECLARATION(...), that contains xxrew_traits
//REFLECTABLE(TestReflectableWithoutDeclarationStruct)
//REFLECTABLE_INIT()

TEST(TestLibrary, TestReflectableRegistry)
{
    {
        // will not compile, since requires REFLECTABLE(...)
        //rew::reflectable<TestReflectableDeclaratonOnlyStruct>();

        auto type = rew::global.find("TestReflectableDeclaratonOnlyStruct");

        ASSERT("type", type == nullptr);
    }
    {
        // will explicitly add type to registry, no requires REFLECTABLE(...), since can add incomplete types
        rew::find_or_add_type<TestReflectableDeclaratonOnlyStruct>();

        auto type = rew::global.find("TestReflectableDeclaratonOnlyStruct");

        ASSERT("type", type != nullptr);
        EXPECT("reflection", type->reflection != nullptr);
    }
    {
        auto type = rew::global.find("TestReflectableDeclaratonOnlyWithUsingStruct");

        ASSERT("type", type != nullptr);
        EXPECT("reflection", type->reflection != nullptr);
    }
    {
        auto type = rew::global.find("TestReflectableStruct");

        ASSERT("type", type != nullptr);
        EXPECT("reflection", type->reflection != nullptr);
    }
}


TEST_SPACE()
{

struct TestDeparenStruct
{
    void Function() {}
    void FunctionWithParentheses(float) {}

    template <typename... Args>
    void Template() {}
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestDeparenStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestDeparenStruct)
    FUNCTION(Function)
    FUNCTION((FunctionWithParentheses))
    FUNCTION(Template<int>, void())
    FUNCTION((Template<float, bool>), void())
REFLECTABLE_INIT()

TEST(TestLibrary, TestDeparen)
{
    auto type = rew::global.find("TestDeparenStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    EXPECT("function", reflection->function.find("Function") != nullptr);
    EXPECT("function_with_parentheses", reflection->function.find("FunctionWithParentheses") != nullptr);
    EXPECT("template", reflection->function.find("Template<int>") != nullptr);
    EXPECT("template_with_parentheses", reflection->function.find("Template<float, bool>") != nullptr);
}


TEST_SPACE()
{

struct TestParentTopBaseStruct {};
struct TestParentBaseStruct : TestParentTopBaseStruct {};

struct TestParentInterface
{
    virtual void Foo() = 0;
};

struct TestParentDerivedStruct : TestParentBaseStruct, TestParentInterface
{
    void Foo() override {}
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestParentTopBaseStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestParentTopBaseStruct)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestParentBaseStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestParentBaseStruct)
    PARENT(TestParentTopBaseStruct)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestParentInterface)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestParentInterface)
    FUNCTION(Foo)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestParentDerivedStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestParentDerivedStruct)
    PARENT(TestParentBaseStruct)
    PARENT(TestParentInterface)
    FUNCTION(Foo)
REFLECTABLE_INIT()

TEST(TestLibrary, TestParent)
{
    auto type = rew::global.find("TestParentDerivedStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    auto base = reflection->parent.find("TestParentBaseStruct");

    ASSERT("base", base != nullptr);
    EXPECT("base-type", base->type == rew::global.find(base->name));

    auto base_base = base->type->reflection->parent.find("TestParentTopBaseStruct");

    ASSERT("base-base", base_base != nullptr);
    EXPECT("base-base-type", base_base->type == rew::global.find(base_base->name));
    EXPECT("non_directed_base", reflection->parent.find(base_base->name) == nullptr);

    auto interface = reflection->parent.find("TestParentInterface");

    ASSERT("interface", interface != nullptr);
    EXPECT("interface-type", interface->type == rew::global.find(interface->name));
}


TEST_SPACE()
{

struct TestMetaStruct {};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestMetaStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestMetaStruct)
REFLECTABLE_INIT()

TEST(TestLibrary, TestMeta)
{
    auto type = rew::global.find("TestMetaStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
}


TEST_SPACE()
{

struct TestCustomRegistryStruct {};

rew::registry_t CustomRegistry;

} // TEST_SPACE

// REFLECTABLE_DECLARATION use CUSTOM_REFLECTABLE_DECLARATION with
// REFLECTABLE_REGISTRY(&rew::global)
// REFLECTABLE_NAME(typename)
CUSTOM_REFLECTABLE_DECLARATION(TestCustomRegistryStruct)
    REFLECTABLE_REGISTRY(&CustomRegistry)
    REFLECTABLE_NAME("TestCustomRegistryStruct")
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestCustomRegistryStruct)
REFLECTABLE_INIT()

TEST(TestLibrary, TestCustomRegistry)
{
    auto registry = ::xxrew_traits<TestCustomRegistryStruct>::registry();

    ASSERT("registry", registry == &CustomRegistry);

    auto type = CustomRegistry.find("TestCustomRegistryStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    EXPECT("reflection", reflection != nullptr);
}


TEST_SPACE()
{

struct TestTypedPropertyStruct
{
    int& FunctionProperty() { return Property; }
    void FunctionProperty(int& value) { Property = value; }

    int& OtherFunctionProperty() { return Property; }
    int const& OtherFunctionProperty() const { return Property; }
    void OtherFunctionProperty(int& value) { Property = value; }

    template <typename T> T TemplateFunctionProperty() { return T(); }

    int Property = 0;
    static constexpr int ConstProperty = 0;
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestTypedPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestTypedPropertyStruct)
    PROPERTY(FunctionProperty, int&())
    PROPERTY(OtherFunctionProperty, int const&() const)
    PROPERTY(TemplateFunctionProperty<char>, char())
    PROPERTY(Property, int)
    PROPERTY(ConstProperty, int const)
REFLECTABLE_INIT()

TEST(TestLibrary, TestTypedProperty)
{
    auto type = rew::global.find("TestTypedPropertyStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    auto function_property = reflection->property.find("FunctionProperty");

    ASSERT("function_property", function_property != nullptr);
    EXPECT("function_property-get", function_property->get != nullptr);
    EXPECT("function_property-set", function_property->set != nullptr);
    EXPECT("function_property-context", function_property->context != nullptr);

    auto other_function_property = reflection->property.find("OtherFunctionProperty");

    ASSERT("other_function_property", other_function_property != nullptr);
    EXPECT("other_function_property-get", other_function_property->get != nullptr);
    EXPECT("other_function_property-set", other_function_property->set == nullptr);
    EXPECT("other_function_property-context", other_function_property->context != nullptr);

    auto template_function_property = reflection->property.find("TemplateFunctionProperty<char>");

    ASSERT("template_function_property", template_function_property != nullptr);
    EXPECT("template_function_property-get", template_function_property->get != nullptr);
    EXPECT("template_function_property-set", template_function_property->set == nullptr);
    EXPECT("template_function_property-context", template_function_property->context == nullptr);

    auto property = reflection->property.find("Property");

    ASSERT("property", property != nullptr);
    EXPECT("property-get", property->get != nullptr);
    EXPECT("property-set", property->set != nullptr);
    EXPECT("property-context", property->context != nullptr);

    auto const_property = reflection->property.find("ConstProperty");

    ASSERT("const_property", const_property != nullptr);
    EXPECT("const_property-get", const_property->get != nullptr);
    EXPECT("const_property-set", const_property->set == nullptr);
    EXPECT("const_property-context", const_property->context != nullptr);
}


TEST_SPACE()
{

struct TestNamedPropertyStruct
{
    bool IsActivated() const { return bIsActivated; }

    void Activate(bool yes)
    {
        bIsActivatedBuffer = bIsActivated;
        bIsActivated = yes;
    }

    bool bIsActivated = false;
    bool bIsActivatedBuffer = false;
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestNamedPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

// without macro using we can put function get and variable set to one or inverse,
// just if u want max flexibility, please, use no macro version
REFLECTABLE(TestNamedPropertyStruct)
    NAMED_PROPERTY("IsActivated", IsActivated, Activate)
    NAMED_PROPERTY("Flag", bIsActivated, bIsActivatedBuffer)
REFLECTABLE_INIT()

TEST(TestLibrary, TestNamedProperty)
{
    auto type = rew::global.find("TestNamedPropertyStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    auto function_property = reflection->property.find("IsActivated");

    ASSERT("function_property", function_property != nullptr);
    ASSERT("function_property-get", function_property->get != nullptr);
    ASSERT("function_property-set", function_property->set != nullptr);
    EXPECT("function_property-context", function_property->context == nullptr);

    auto [function_property_get_ptr, function_property_set_ptr] = function_property->pointer;

    EXPECT("function_property-get-pointer",
        std::any_cast<bool(TestNamedPropertyStruct::*)() const>(function_property_get_ptr) ==
        &TestNamedPropertyStruct::IsActivated
    );
    EXPECT("function_property-set-pointer",
        std::any_cast<void(TestNamedPropertyStruct::*)(bool)>(function_property_set_ptr) ==
        &TestNamedPropertyStruct::Activate
    );

    auto property = reflection->property.find("Flag");

    ASSERT("property", property != nullptr);
    ASSERT("property-get", property->get != nullptr);
    ASSERT("function_property-set", function_property->set != nullptr);
    EXPECT("property-context", property->context != nullptr);

    auto [property_get_ptr, property_set_ptr] = property->pointer;

    EXPECT("property-get-pointer",
        std::any_cast<bool TestNamedPropertyStruct::*>(property_get_ptr) ==
        &TestNamedPropertyStruct::bIsActivated
    );
    EXPECT("property-set-pointer",
        std::any_cast<bool TestNamedPropertyStruct::*>(property_set_ptr) ==
        &TestNamedPropertyStruct::bIsActivatedBuffer
    );
}


TEST_SPACE()
{

struct TestBaseWithReflection {};
struct TestWrongMediatorWithReflection : TestBaseWithReflection {};
struct TestRightMediatorWithReflection : TestBaseWithReflection {};

struct TestWrongDerivedWithReflection : TestWrongMediatorWithReflection {};
struct TestRightDerivedWithReflection : TestRightMediatorWithReflection {};

struct TestDerivedWithReflection
    : TestWrongMediatorWithReflection, TestRightMediatorWithReflection {};


bool is_parent_of(rew::type_t const* type, rew::type_t const* child)
{
    if (type == child)
    {
        return true;
    }
    for (auto& [name, parent] : child->reflection->parent.all)
    {
        if (is_parent_of(type, parent.type))
        {
            return true;
        }
    }
    return false;
}

bool is_child_of(rew::type_t const* child, rew::type_t const* type)
{
    return is_parent_of(type, child);
}

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestBaseWithReflection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestBaseWithReflection)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestWrongMediatorWithReflection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestWrongMediatorWithReflection)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestRightMediatorWithReflection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestRightMediatorWithReflection)
    PARENT(TestBaseWithReflection)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestWrongDerivedWithReflection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestWrongDerivedWithReflection)
    PARENT(TestWrongMediatorWithReflection)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestRightDerivedWithReflection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestRightDerivedWithReflection)
    PARENT(TestRightMediatorWithReflection)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestDerivedWithReflection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestDerivedWithReflection)
    PARENT(TestWrongMediatorWithReflection)
    PARENT(TestRightMediatorWithReflection)
REFLECTABLE_INIT()

TEST(TestLibrary, TestIsParentOf)
{
    auto base = rew::global.find("TestBaseWithReflection");

    ASSERT("base-type", base != nullptr);

    auto reflection = base->reflection;

    ASSERT("base-reflection", reflection != nullptr);

    {
        auto type = rew::global.find("TestRightMediatorWithReflection");

        ASSERT("right-mediator-type", type != nullptr);

        auto reflection = type->reflection;

        ASSERT("right-mediator-reflection", reflection != nullptr);
        EXPECT("right-mediator-is_child_of", is_child_of(type, base));
    }
    {
        auto type = rew::global.find("TestWrongMediatorWithReflection");

        ASSERT("wrong-mediator-type", type != nullptr);

        auto reflection = type->reflection;

        ASSERT("wrong-mediator-reflection", reflection != nullptr);
        EXPECT("wrong-mediator-is_child_of", !is_child_of(type, base));
    }
    {
        auto type = rew::global.find("TestWrongDerivedWithReflection");

        ASSERT("wrong-derived-type", type != nullptr);

        auto reflection = type->reflection;

        ASSERT("wrong-derived-reflection", reflection != nullptr);
        EXPECT("wrong-derived-is_child_of", !is_child_of(type, base));
    }
    {
        auto type = rew::global.find("TestRightDerivedWithReflection");

        ASSERT("right-derived-type", type != nullptr);

        auto reflection = type->reflection;

        ASSERT("right-derived-reflection", reflection != nullptr);
        EXPECT("right-derived-is_child_of", is_child_of(type, base));
    }
    {
        auto type = rew::global.find("TestDerivedWithReflection");

        ASSERT("derived-type", type != nullptr);

        auto reflection = type->reflection;

        ASSERT("derived-reflection", reflection != nullptr);
        EXPECT("derived-is_parent_of", is_parent_of(base, type));
    }
}


TEST_SPACE()
{

struct TestRTTIRegistryStruct {};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestRTTIRegistryStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestRTTIRegistryStruct)
REFLECTABLE_INIT()

TEST(TestLibrary, TestRTTIRegistry)
{
    auto type = rew::find_or_add_type<TestRTTIRegistryStruct>();
    auto const_type = rew::find_or_add_type<TestRTTIRegistryStruct const>();
    auto reference_type = rew::find_or_add_type<TestRTTIRegistryStruct&>(); // will break to TestRTTIRegistryStruct*
    auto const_reference_type = rew::find_or_add_type<TestRTTIRegistryStruct const&>(); // will break to TestRTTIRegistryStruct*
    auto pointer_type = rew::find_or_add_type<TestRTTIRegistryStruct*>();
    auto pointer_to_const_type = rew::find_or_add_type<TestRTTIRegistryStruct const*>(); // will break to TestRTTIRegistryStruct*
    auto const_pointer_to_const_type = rew::find_or_add_type<TestRTTIRegistryStruct const* const>(); // will break to TestRTTIRegistryStruct*
    auto pointer_type_reference = rew::find_or_add_type<TestRTTIRegistryStruct*&>();
    auto pointer_to_const_type_reference = rew::find_or_add_type<TestRTTIRegistryStruct const*&>(); // will break to TestRTTIRegistryStruct const**
    auto const_pointer_to_const_type_reference = rew::find_or_add_type<TestRTTIRegistryStruct const* const&>(); // will break to TestRTTIRegistryStruct*
    auto mixed_type = rew::find_or_add_type<TestRTTIRegistryStruct const** const&>();

    EXPECT("type-typeid", rew::global.find(typeid(TestRTTIRegistryStruct)) == type);
    EXPECT("const_type-typeid", rew::global.find(typeid(TestRTTIRegistryStruct const)) == const_type);
    EXPECT("reference_type-typeid", rew::global.find(typeid(TestRTTIRegistryStruct*)) == reference_type);
    EXPECT("const_reference_type-typeid", rew::global.find(typeid(TestRTTIRegistryStruct*)) == const_reference_type);
    EXPECT("pointer_type-typeid", rew::global.find(typeid(TestRTTIRegistryStruct*)) == pointer_type);
    EXPECT("pointer_to_const_type-typeid", rew::global.find(typeid(TestRTTIRegistryStruct*)) == pointer_to_const_type);
    EXPECT("const_pointer_to_const_type-typeid", rew::global.find(typeid(TestRTTIRegistryStruct*)) == const_pointer_to_const_type);
    EXPECT("pointer_type_reference-typeid", rew::global.find(typeid(TestRTTIRegistryStruct**)) == pointer_type_reference);
    EXPECT("pointer_to_const_type_reference-typeid", rew::global.find(typeid(TestRTTIRegistryStruct const**)) == pointer_to_const_type_reference);
    EXPECT("const_pointer_to_const_type_reference-typeid", rew::global.find(typeid(TestRTTIRegistryStruct const**)) == const_pointer_to_const_type_reference);
    EXPECT("mixed_type-typeid", rew::global.find(typeid(TestRTTIRegistryStruct const***)) == mixed_type);
}


TEST_SPACE()
{

struct TestImplicitRegistryStruct
{
    TestImplicitRegistryStruct** const* Data = nullptr;
    static TestImplicitRegistryStruct* Instance;
};

TestImplicitRegistryStruct* TestImplicitRegistryStruct::Instance = nullptr;

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestImplicitRegistryStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestImplicitRegistryStruct)
    PROPERTY(Data)
    PROPERTY(Instance)
REFLECTABLE_INIT()

TEST(TestLibrary, TestImplicitRegistry)
{
    EXPECT("type", rew::global.find("TestImplicitRegistryStruct") != nullptr);
    EXPECT("type-property0", rew::global.find("TestImplicitRegistryStruct***") != nullptr);
    EXPECT("type-property1", rew::global.find("TestImplicitRegistryStruct*") != nullptr);
}
