#include <gtest/gtest.h>
#include <vector>
#include "../src/shared_ptr.hh"

TEST(SharedPtr, initAndDestroySinglePtr)
{
    SharedPtr<int> var(new int(10));
}

TEST(SharedPtr, initAndGet)
{
    // GIVEN
    int* data = new int(10);
    // WHEN
    SharedPtr<int> var(data);
    // THEN
    ASSERT_EQ(data, var.get());
}

TEST(SharedPtr, initAndOperatorStar)
{
    // GIVEN
    int* data = new int(10);
    // WHEN
    SharedPtr<int> var(data);
    // THEN
    ASSERT_EQ(*data, *var);
}

TEST(SharedPtr, initAndOperatorArrow)
{
    // GIVEN
    auto data = new std::vector<int>{1, 2, 3};
    // WHEN
    SharedPtr<std::vector<int>> var(data);
    // THEN
    ASSERT_EQ(data->size(), var->size());
}

TEST(SharedPtr, refCountSingleRef)
{
    // GIVEN
    int* data = new int(10);
    // WHEN
    SharedPtr<int> var(data);
    // THEN
    ASSERT_EQ(1, var.ref_count_get());
}

TEST(SharedPtr, copyCtorCheckPtr)
{
    // GIVEN
    int* data = new int(10);
    SharedPtr<int> var(data);
    // WHEN
    SharedPtr<int> var_copy(var);
    // THEN
    ASSERT_EQ(data, var.get());
    ASSERT_EQ(data, var_copy.get());
}

TEST(SharedPtr, copyCtorCheckRefCount)
{
    // GIVEN
    int* data = new int(10);
    SharedPtr<int> var(data);
    // WHEN
    SharedPtr<int> var_copy(var);
    // THEN
    ASSERT_EQ(2, var.ref_count_get());
    ASSERT_EQ(2, var_copy.ref_count_get());
}

TEST(SharedPtr, copyCtorCheckRefCountAfterDeletingOriginal)
{
    // GIVEN
    int* data = new int(10);
    SharedPtr<int> var(data);
    // WHEN
    {
        SharedPtr<int> var_copy(var);
        // THEN
        ASSERT_EQ(2, var.ref_count_get());
        ASSERT_EQ(2, var_copy.ref_count_get());
    }
    // THEN
    ASSERT_EQ(1, var.ref_count_get());
}

TEST(SharedPtr, testMakeShared)
{
    // GIVEN
    int arg = 10;
    // WHEN
    SharedPtr<int> var = SharedPtr<int>::make_shared(arg);
    // THEN
    ASSERT_EQ(arg, *var);
}

TEST(SharedPtr, testMakeSharedStruct)
{
    // GIVEN
    struct test
    {
        test(int a, int b, int c) : a(a), b(b), c(c) {}
        test(test&) = delete;
        test(test&&) = delete;
        int a, b, c;
    };
    // WHEN
    SharedPtr<test> var = SharedPtr<test>::make_shared(1, 2, 3);
    // THEN
    ASSERT_EQ(1, var->a);
    ASSERT_EQ(2, var->b);
    ASSERT_EQ(3, var->c);
}
