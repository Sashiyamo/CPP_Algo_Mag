#include "Array.h"
#include "gtest/gtest.h"

using namespace std;

TEST(ArrayClassTest, Constructor)
{
    Array<int> test;
    ASSERT_EQ(test.size(), 0);
    ASSERT_EQ(test.capacity_(), 16);
}

TEST(ArrayClassTest, ValueConstructor)
{
    Array<int> test{13};
    ASSERT_EQ(test.size(), 0);
    ASSERT_EQ(test.capacity_(), 13);
}

TEST(ArrayClassTest, CopyConstructor)
{
    Array<int> copy{};
    copy.insert(1);
    copy.insert(5);
    copy.insert(9);

    Array<int> test{copy};

    ASSERT_EQ(copy.size(), test.size());
    ASSERT_EQ(copy.capacity_(), test.capacity_());
    for (int i = 0; i < copy.size(); ++i)
    {
        ASSERT_EQ(copy[i], test[i]);
    }
}

TEST(ArrayClassTest, ArrayCopy)
{
    Array<int> copy{};
    copy.insert(1);
    copy.insert(5);
    copy.insert(9);

    Array<int> test{};
    test = copy;

    ASSERT_EQ(copy.size(), test.size());
    ASSERT_EQ(copy.capacity_(), test.capacity_());
    for (int i = 0; i < copy.size(); ++i)
    {
        ASSERT_EQ(copy[i], test[i]);
    }
}

TEST(ArrayClassTest, Insert)
{
    Array<int> test{};
    test.insert(9);

    ASSERT_EQ(test.size(), 1);
    ASSERT_EQ(test[0], 9);
}

TEST(ArrayClassTest, IdxInsert)
{
    Array<int> test{};
    test.insert(1);
    test.insert(2);
    test.insert(3);
    test.insert(1, 4);

    ASSERT_EQ(test.size(), 4);
    ASSERT_EQ(test[1], 4);
}

TEST(ArrayClassTest, RemoveHead)
{
    Array<int> test{};
    test.insert(1);
    test.insert(5);
    test.insert(9);

    test.remove(0);

    ASSERT_EQ(test.size(), 2);
    ASSERT_EQ(test[0], 5);
    ASSERT_EQ(test[1], 9);
}

TEST(ArrayClassTest, RemoveBody)
{
    Array<int> test{};
    test.insert(1);
    test.insert(5);
    test.insert(9);

    test.remove(1);

    ASSERT_EQ(test.size(), 2);
    ASSERT_EQ(test[0], 1);
    ASSERT_EQ(test[1], 9);
}

TEST(ArrayClassTest, Size)
{
    Array<int> test{};
    test.insert(1);
    test.insert(5);
    test.remove(0);

    ASSERT_EQ(test.size(), 1);
}

TEST(ArrayClassTest, CapIncrease)
{
    Array<int> test{};
    ASSERT_EQ(test.capacity_(), 16);

    for (int i = 0; i < 20; ++i)
        test.insert(1);

    ASSERT_EQ(test.capacity_(), 32);
}

TEST(ArrayClassTest, Iterator)
{
    Array<int> test{};
    test.insert(1);
    test.insert(5);
    test.insert(9);

    int val = 1;

    for (auto it = test.iterator(); it.hasNext(); it.next()) {
        ASSERT_EQ(it.get(), val);
        val += 4;
    }
}

TEST(ArrayClassTest, ReverseIterator)
{
    Array<int> test{};
    test.insert(1);
    test.insert(5);
    test.insert(9);

    int val = 9;

    for (auto it = test.reverseIterator(); it.hasNext(); it.next()) {
        ASSERT_EQ(it.get(), val);
        val -= 4;
    }

}

TEST(ArrayClassTest, IterSetGet)
{
    Array<int> test{};
    test.insert(1);
    test.insert(5);
    test.insert(9);

    for (auto it = test.iterator(); it.hasNext(); it.next()) {
        it.set(3);
    }
    for (auto it = test.iterator(); it.hasNext(); it.next())
        ASSERT_EQ(it.get(), 3);
}

TEST(ArrayClassTest, SimpleWork)
{
    Array<int> test;
    for (int i = 0; i < 10; ++i)
        test.insert(i + 1);

    for (int i = 0; i < test.size(); ++i)
        test[i] *= 2;

    int idx = 1;
    for (auto it = test.iterator(); it.hasNext(); it.next())
        ASSERT_EQ(it.get(), 2 * idx++);
}