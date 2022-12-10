#include "QuickSort.h"
#include <random>
#include "gtest/gtest.h"

std::default_random_engine randGenerator;

TEST(QuickSort, ElementSort) {
    randGenerator.seed(time(NULL));
    const int size = 6;
    int array[size] = { 6, 7, 1, 3, 8, 4 };

    QuickSort(array, array + size - 1, [](int a, int b) { return a < b; });

    for (int i = 0; i < size - 1; ++i)
        ASSERT_LE(array[i], array[i + 1]);
}

TEST(QuickSort, BigSizeSort) {
    randGenerator.seed(time(NULL));
    const int size = 100;
    int array[size]{};
    std::uniform_int_distribution<int> randNumber(1, 100);

    for (int i = 0; i < size; i++)
        array[i] = randNumber(randGenerator);

    QuickSort(array, array + size - 1, [](int a, int b) { return a < b; });

    for (int i = 0; i < size - 1; ++i)
        ASSERT_LE(array[i], array[i + 1]);
}

TEST(QuickAndInsertionSort, ElementSort) {
    randGenerator.seed(time(NULL));
    const int size = 6;
    int array[size] = { 6, 7, 1, 3, 8, 4 };

    QuickAndInsertionSort(array, array + size - 1, [](int a, int b) { return a < b; });

    for (int i = 0; i < size - 1; ++i)
        ASSERT_LE(array[i], array[i + 1]);
}

TEST(QuickSort, BigSizeSortString) {
    randGenerator.seed(time(NULL));
    const int size = 100;
    std::string array[size]{};
    std::uniform_int_distribution<int> randNumber(1, 100);

    for (int i = 0; i < size; i++)
        array[i] = std::to_string(randNumber(randGenerator));

    QuickSort(array, array + size - 1, [](std::string a, std::string b) { return a < b; });

    for (int i = 0; i < size - 1; ++i)
        ASSERT_LE(array[i], array[i + 1]);
}

TEST(QuickAndInsertionSort, BigSizeSortString) {
    randGenerator.seed(time(NULL));
    const int size = 35;
    std::string array[size]{};
    std::uniform_int_distribution<int> randNumber(1, 100);

    for (int i = 0; i < size; i++)
        array[i] = std::to_string(randNumber(randGenerator));

    QuickAndInsertionSort(array, array + size - 1, [](std::string a, std::string b) { return a < b; });

    for (int i = 0; i < size - 1; ++i)
        ASSERT_LE(array[i], array[i + 1]);
}
