#include "Array.h"
#include "gtest/gtest.h"

using namespace std;

TEST(ArrayClassTestString, Constructor)
{
    Array<string> test;
    ASSERT_EQ(test.size(), 0);
    ASSERT_EQ(test.capacity_(), 16);
}

TEST(ArrayClassTestString, ValueConstructor)
{
    Array<string> test{13};
    ASSERT_EQ(test.size(), 0);
    ASSERT_EQ(test.capacity_(), 13);
}

TEST(ArrayClassTestString, CopyConstructor)
{
    Array<string> copy;
    copy.insert("one");
    copy.insert("five");
    copy.insert("nine");

    Array<string> test{copy};

    ASSERT_EQ(copy.size(), test.size());
    ASSERT_EQ(copy.capacity_(), test.capacity_());
    for (int i = 0; i < copy.size(); ++i)
    {
        ASSERT_EQ(copy[i], test[i]);
    }
}

TEST(ArrayClassTestString, ArrayCopy)
{
    Array<string> copy{};
    copy.insert("one");
    copy.insert("five");
    copy.insert("nine");

    Array<string> test{};
    test = copy;

    ASSERT_EQ(copy.size(), test.size());
    ASSERT_EQ(copy.capacity_(), test.capacity_());
    for (int i = 0; i < copy.size(); ++i)
    {
        ASSERT_EQ(copy[i], test[i]);
    }
}

TEST(ArrayClassTestString, Insert)
{
    Array<string> test{};
    test.insert("nine");

    ASSERT_EQ(test.size(), 1);
    ASSERT_EQ(test[0], "nine");
}

TEST(ArrayClassTestString, IdxInsert)
{
    Array<string> test{};
    test.insert("one");
    test.insert("two");
    test.insert("three");
    test.insert(1, "four");

    ASSERT_EQ(test.size(), 4);
    ASSERT_EQ(test[1], "four");
}

TEST(ArrayClassTestString, RemoveHead)
{
    Array<string> test{};
    test.insert("one");
    test.insert("five");
    test.insert("nine");

    test.remove(0);

    ASSERT_EQ(test.size(), 2);
    ASSERT_EQ(test[0], "five");
    ASSERT_EQ(test[1], "nine");
}

TEST(ArrayClassTestString, RemoveBody)
{
    Array<string> test{};
    test.insert("one");
    test.insert("five");
    test.insert("nine");

    test.remove(1);

    ASSERT_EQ(test.size(), 2);
    ASSERT_EQ(test[0], "one");
    ASSERT_EQ(test[1], "nine");
}

TEST(ArrayClassTestString, Size)
{
    Array<string> test{};
    test.insert("one");
    test.insert("five");
    test.remove(0);

    ASSERT_EQ(test.size(), 1);
}

TEST(ArrayClassTestString, CapIncrease)
{
    Array<string> test{};
    ASSERT_EQ(test.capacity_(), 16);

    for (int i = 0; i < 20; ++i)
        test.insert("one");

    ASSERT_EQ(test.capacity_(), 32);
}

TEST(ArrayClassTestString, Iterator)
{
    Array<string> test{};
    test.insert("1");
    test.insert("5");
    test.insert("9");

    int val = 1;

    for (auto it = test.iterator(); it.hasNext(); it.next()) {
        ASSERT_EQ(stoi(it.get()), val);
        val += 4;
    }
}

TEST(ArrayClassTestString, ReverseIterator)
{
    Array<string> test{};
    test.insert("1");
    test.insert("5");
    test.insert("9");

    int val = 9;

    for (auto it = test.reverseIterator(); it.hasNext(); it.next()) {
        ASSERT_EQ(stoi(it.get()), val);
        val -= 4;
    }

}

TEST(ArrayClassTestString, IterSetGet)
{
    Array<string> test{};
    test.insert("one");
    test.insert("five");
    test.insert("nine");

    for (auto it = test.iterator(); it.hasNext(); it.next()) {
        it.set("three");
    }
    for (auto it = test.iterator(); it.hasNext(); it.next())
        ASSERT_EQ(it.get(), "three");
}