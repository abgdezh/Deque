#include <deque>
#include <random>
#include <gtest/gtest.h>
#include "deque.h"

using std::deque;

TEST(push_pop_tests, time_of_poping_test) {
    for (double i = 1; i < 100000000; i *= 1.1) {
        Deque<int> testDeque;
        for (int j = 0; j < i; ++j)
            testDeque.push_back(0);
        double t = clock();
        while (testDeque.size())
            testDeque.pop_back();
        std::cout << static_cast<int>(i) << "\t" << (clock() - t) / CLOCKS_PER_SEC << '\n';
    }
}

TEST(push_pop_tests, time_of_pushing_test) {
    for (double i = 1; i < 100000000; i *= 1.1) {
        double t = clock();
        Deque<int> testDeque;
        for (int j = 0; j < i; ++j)
            testDeque.push_back(0);
        std::cout << static_cast<int>(i) << "\t" << (clock() - t) / CLOCKS_PER_SEC << '\n';
    }
}

TEST(constructor_tests, constructor_test) {
    const int numConstructions = 50000;
    const int numPushings = 1000;
    Deque<int> *arr = new Deque<int>[numConstructions];
    for (int i = 0; i < numConstructions; ++i) {
        arr[i] = Deque<int>();
        Deque<int> tmp;
        for (int j = 0; j < numPushings; ++j) {
            arr[i].push_back(rand());
            tmp.push_back(rand());
        }
        arr[i] = arr[i];
        tmp = arr[i];
        Deque<int> tmp1(arr[i]);
        for (int j = 0; j < numPushings; ++j) {
            ASSERT_EQ(arr[i][j], tmp[j]);
            ASSERT_EQ(arr[i][j], tmp1[j]);
        }
        arr[i] = Deque<int>();
        tmp = Deque<int>();
    }
    delete[] arr;
}

TEST(push_pop_tests, random_push_pop_test) {
    Deque<int> testDeque;
    deque<int> stdDeque;
    const int iteration_number = 50000000;

    for (int i = 0; i < iteration_number; ++i) {
        ASSERT_EQ(stdDeque.size(), testDeque.size());
        ASSERT_EQ(stdDeque.empty(), testDeque.empty());
        if (stdDeque.empty() || rand() % 2) {
            int value = rand();
            if (rand() % 2) {
                stdDeque.push_back(value);
                testDeque.push_back(value);
            } else {
                stdDeque.push_front(value);
                testDeque.push_front(value);
            }
        } else {
            if (rand() % 2) {
                ASSERT_EQ(stdDeque.front(), testDeque.front());
                stdDeque.pop_front();
                testDeque.pop_front();
            } else {
                ASSERT_EQ(stdDeque.back(), testDeque.back());
                stdDeque.pop_back();
                testDeque.pop_back();
            }
        }
    }
};

TEST(push_pop_tests, max_push_test) {
    Deque<int> testDeque;
    deque<int> stdDeque;
    const int iteration_number = 50000000;
    for (int i = 0; i < iteration_number; ++i) {
        int value = rand();
        if (rand() % 2) {
            stdDeque.push_back(value);
            testDeque.push_back(value);
        } else {
            stdDeque.push_front(value);
            testDeque.push_front(value);
        }
    }

    while (stdDeque.size()) {
        ASSERT_EQ(stdDeque.size(), testDeque.size());
        ASSERT_EQ(stdDeque.empty(), testDeque.empty());
        if (rand() % 2) {
            ASSERT_EQ(stdDeque.front(), testDeque.front());
            stdDeque.pop_front();
            testDeque.pop_front();
        } else {
            ASSERT_EQ(stdDeque.back(), testDeque.back());
            stdDeque.pop_back();
            testDeque.pop_back();
        }
    }
}

TEST(access_tests, random_access_test) {
    Deque<int> testDeque;
    deque<int> stdDeque;

    const int deque_size = 50000000;

    for (int i = 0; i < deque_size; ++i) {
        int value = rand();
        stdDeque.push_back(value);
        testDeque.push_back(value);
    }

    const int iteration_number = 50000000;
    for (int i = 0; i < iteration_number; ++i) {
        int index = rand() % deque_size;
        ASSERT_EQ(stdDeque[index], testDeque[index]);
    }
};

TEST(iterator_tests, iterator_test) {
    Deque<int> testDeque;
    deque<int> stdDeque;

    const int deque_size = 5000000;

    for (int i = 0; i < deque_size; ++i) {
        int value = rand();
        stdDeque.push_back(value);
        testDeque.push_back(value);
    }

    ASSERT_EQ(stdDeque.begin() - stdDeque.end(), testDeque.begin() - testDeque.end());
    ASSERT_EQ(stdDeque.rbegin() - stdDeque.rend(), testDeque.rbegin() - testDeque.rend());

    deque<int>::iterator stdIt = stdDeque.begin();
    Deque<int>::iterator testIt = testDeque.begin();

    while (stdIt < stdDeque.end()) {
        EXPECT_TRUE(testIt < testDeque.end());
        EXPECT_EQ(*stdIt, *testIt);
        int value = rand();
        *stdIt = value;
        *testIt = value;
        EXPECT_EQ(*stdIt, *testIt);
        ++stdIt;
        ++testIt;
    }

    do {
        --stdIt;
        --testIt;
        EXPECT_EQ(stdIt >= stdDeque.begin(), testIt >= testDeque.begin());
        EXPECT_EQ(*stdIt, *testIt);
    } while (stdIt != stdDeque.begin());

    deque<int>::reverse_iterator stdRIt = stdDeque.rbegin();
    Deque<int>::reverse_iterator testRIt = testDeque.rbegin();

    while (stdRIt < stdDeque.rend()) {
        EXPECT_TRUE(testRIt < testDeque.rend());
        EXPECT_EQ(*stdRIt, *testRIt);
        int value = rand();
        *stdRIt = value;
        *testRIt = value;
        EXPECT_EQ(*stdRIt, *testRIt);
        ++stdRIt;
        ++testRIt;
    }
    do {
        --stdRIt;
        --testRIt;
        EXPECT_EQ(stdRIt >= stdDeque.rbegin(), testRIt >= testDeque.rbegin());
        EXPECT_EQ(*stdRIt, *testRIt);
    } while (stdRIt != stdDeque.rbegin());
}

TEST(iterator_tests, const_iterator_test) {
    Deque<int> testDeque1;
    deque<int> stdDeque1;

    const int deque_size = 5000000;

    for (int i = 0; i < deque_size; ++i) {
        int value = rand();
        stdDeque1.push_back(value);
        testDeque1.push_back(value);
    }

    const Deque<int> testDeque = testDeque1;
    const deque<int> stdDeque = stdDeque1;

    deque<int>::const_iterator stdIt = stdDeque.begin();
    Deque<int>::const_iterator testIt = testDeque.begin();

    while (stdIt != stdDeque.end()) {
        EXPECT_TRUE(testIt < testDeque.end());
        EXPECT_EQ(*stdIt, *testIt);
        ++stdIt;
        ++testIt;
    }

    do {
        --stdIt;
        --testIt;
        EXPECT_EQ(stdIt >= stdDeque.begin(), testIt >= testDeque.begin());
        EXPECT_EQ(*stdIt, *testIt);
    } while (stdIt != stdDeque.begin());

    deque<int>::const_reverse_iterator stdRIt = stdDeque.rbegin();
    Deque<int>::const_reverse_iterator testRIt = testDeque.rbegin();

    while (stdRIt != stdDeque.rend()) {
        EXPECT_TRUE(testRIt < testDeque.rend());
        EXPECT_EQ(*stdRIt, *testRIt);
        ++stdRIt;
        ++testRIt;
    }

    do {
        --stdRIt;
        --testRIt;
        EXPECT_EQ(stdRIt >= stdDeque.rbegin(), testRIt >= testDeque.rbegin());
        EXPECT_EQ(*stdRIt, *testRIt);
    } while (stdRIt != stdDeque.rbegin());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}