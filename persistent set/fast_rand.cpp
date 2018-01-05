//
// Created by jetbrains on 05/01/2018.
//

#include "fast_rand.h"

int g_seed = 239 * 2 + 1;
int last_result = 0;
int cur_bit = 0;
const int MAX_BIT = 16;
const int K = 214013, B = 2531011;
const int AND = 0x7FFF;

inline void fastrand()
{
	g_seed = (K * g_seed + B);
	last_result = (g_seed >> MAX_BIT) & AND;
}

bool rand_bit()
{
	if (cur_bit == MAX_BIT)
		cur_bit = 0, fastrand();
	return (last_result >> cur_bit) & 1;
}