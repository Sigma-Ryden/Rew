#include <RewTestingBase.hpp>

TEST(TestLibrary, TestConst)
{
    EXPECT("type", rew::global.find("int const") == nullptr);
    EXPECT("type-name", rew::meta::reflectable_traits<const int>::name() == "int const");
}

TEST(TestLibrary, TestRef)
{
    EXPECT("type", rew::global.find<int&>() == nullptr);
    EXPECT("type-name", rew::meta::reflectable_traits<int&>::name() == "int&");
}

TEST(TestLibrary, TestConstRef)
{
    EXPECT("type", rew::global.find<const int&>() == nullptr);
    EXPECT("type-name", rew::meta::reflectable_traits<const int&>::name() == "int const&");
}

TEST(TestLibrary, TestRawFunction)
{
    EXPECT("type-name", rew::meta::reflectable_traits<void() const>::name() == "void() const");
}

// REFLECTABLE_USING(std_size_t, std::size_t)

// RAW_REFLECTABLE_DECLARATION(std_size_t)
//     REFLECTABLE_REGISTRY(&rew::global)
//     REFLECTABLE_NAME("std::size_t")
// REFLECTABLE_DECLARATION_INIT()

// REFLECTABLE(std_size_t)
// REFLECTABLE_INIT()

// TEST_SPACE()
// {

// struct X
// {
//     int f() { return 0; }
//     void f(int) {}

//     const int g() { return 0; }

//     const int i = 0;
// };

// } // TEST_SPACE

// REFLECTABLE_DECLARATION(X)
// REFLECTABLE_DECLARATION_INIT()

// REFLECTABLE(X)
//     PROPERTY(f)
//     PROPERTY(g, const int)
//     PROPERTY(i)
// REFLECTABLE_INIT()
