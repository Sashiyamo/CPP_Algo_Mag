#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include "QuickSort.h"
#include <gtest/gtest.h>

typedef std::chrono::nanoseconds ns;
typedef std::chrono::system_clock::time_point type_;
typedef std::chrono::high_resolution_clock time_;

int main() {
//    ::testing::InitGoogleTest();
//    return RUN_ALL_TESTS();

    std::default_random_engine gen;
    std::uniform_int_distribution<int> rand(1, 100);
    gen.seed(time(NULL));

    std::ofstream f("time.txt");

    for(int size = 5; size <= 80; ++size)
    {
        ns time1 = std::chrono::nanoseconds(0);
        ns time2 = std::chrono::nanoseconds(0);

        for (int j = 0; j < 100; ++j)
        {

            int* array1 = new int [size];
            int* array2 = new int [size];

            for (int i = 0; i < size; ++i)
                array1[i] = rand(gen);

            for (int i = size - 1, k = 1; i >= 0; i--, k++)
                array2[i] = k;

            type_ start, end;

            start = time_::now();
            QuickSort(array1, array1 + size - 1, [](int a, int b) { return a < b; });
            end = time_::now();

            time1 += (end - start);

            start = time_::now();
            InsertionSort(array2, array2 + size - 1, [](int a, int b) { return a < b; });
            end = time_::now();

            time2 += (end - start);

            delete[] array1;
            delete[] array2;
        }

        time1 /= 1000;
        time2 /= 1000;

        if (f.is_open())
            f << size << " ; " << time1.count() << " ; " << time2.count() << "\n";
    }

    f.close();
    return 0;
}