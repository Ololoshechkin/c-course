//
// Created by Vadim on 30.04.17.
//

#include "binary_code.h"

binary_code::binary_code() 
		: data(vector<bool>())
		, pos(0)
{}

void binary_code::insert_symbol(uchar c)
{
	bool code_started = false;
	for (int i = 7; i >= 0; --i)
		if (code_started)
			data.push_back((c & (1 << i)) != 0);
		else if (c & (1 << i))
			code_started = true;
}

void binary_code::build(std::vector<uchar>& symbols)
{
	data.clear();
	for (uchar c : symbols)
		insert_symbol(c);
}

std::vector<uchar> binary_code::get_code()
{
	std::vector <uchar> code;
	uchar max_deg = (uchar)(1 << 7), cur_deg = max_deg, cur = 0;
	for (bool x : data) {
		if (x)
			cur += cur_deg;
		cur_deg >>= 1;
		if (!cur_deg)
			code.push_back((uchar) cur), cur_deg = max_deg, cur = 0;
	}
	if ((data.size() & 7) != 0)
		data.push_back((uchar) cur);
	return code;
}

bool binary_code::get_next_data() 
{
	return data[pos++];
}

bool binary_code::empty() 
{
	return pos >= data.size();
}

binary_code::~binary_code() 
{
	data.clear();
}