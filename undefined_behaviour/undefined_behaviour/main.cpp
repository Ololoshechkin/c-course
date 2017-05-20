//
//  main.cpp
//  undefined_behaviour
//
//  Created by Vadim on 06.05.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>

/*
 without "restrict" it is possible to 'res' to be intersected with one of elements' pointers
 => in order to implement our code compiler says "read res, put into some register A,
                                                    read elem to B,
                                                    add B to A
                                                    put A to res"
void sum(float*  res,
         float const* elements,
         size_t size)
{
    *res = 0.f;
    for (size_t i = 0; i != size; ++i)
        *res += elements[i];
}
*/


/*
 and now - register keyword is an indicator that res is unique pointer
 so, we can implement such an assembly code:
 res += elem;
*/
void sum(float* __restrict res,
         float const* __restrict elements,
         size_t size)
{
    *res = 0.f;
    for (size_t i = 0; i != size; ++i)
        *res += elements[i];
}

/*
 this code would be optimized to 
 "call memcpy"
 since there is __restrict keyword
*/
void my_memcpy(char* __restrict dst, char const* __restrict src, size_t n)
{
    for (size_t i = 0; i != n; ++i)
        dst[i] = src[i];
}


float sum(float const* __restrict a,
          float const* __restrict b,
          size_t size)
{
    a = (float const*)__builtin_assume_aligned(a, 16); // purpose : for compiler to know that a
    b = (float const*)__builtin_assume_aligned(b, 16); // is aligned by 16 bytes
    if ((size % 16) != 0)
        __builtin_unreachable(); // make compiler assume that size % 16 === 0
    float result = 0.f;
    for (size_t i = 0; i != size; ++i)
        result += a[i] * b[i];
    return result;
}
// NB : in order to make programme optimized by compiler ((a + b) + c != a + (b + c) for floats,
// but we say it to think that (a + b) + c === a + (b + c)) compile it with flag !!!FAST_MATH!!!
// Now compiler compresses 4 floats into one SSE-vector (128bit)
// --- auto-vectorization

bool undefined_always_returns_true(int a)
{
    if (a < a + 1)
        return true;
    return false;
}

float f(int* a,float* b)
{
    *b = 1.f;
    *a = 5;
    return *b;
}

int main(int argc, const char * argv[]) {
    std::cout << (1 << 100) << '\n';
    int a[17];
    std::cout << a[18];
    return 0;
}
