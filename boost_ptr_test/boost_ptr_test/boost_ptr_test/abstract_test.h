//
//  abstract_test.h
//  boost_ptr_test
//
//  Created by Vadim on 18/11/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef abstract_test_h
#define abstract_test_h

#include <ctime>
#include <vector>

constexpr int BIG_CONST = 500000;

template <template<typename> class smart_ptr, typename T>
struct abstract_test {
    static constexpr int TEST_COUNT = 10;
    static constexpr double TIME_SCALE = 1e6;
    std::vector<double> get_benchmark() {
        std::vector<double> bench;
        for (int i = 0; i < TEST_COUNT; ++i)
            bench.push_back(test(i));
        return bench;
    }
protected:
    virtual void test_impl(int) = 0;
private:
    double test(int test_number) {
        double st_time = clock();
        test_impl(test_number);
        return (clock() - st_time) / TIME_SCALE;
    }
};

#endif /* abstract_test_h */
