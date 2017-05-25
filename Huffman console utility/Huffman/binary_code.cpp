//
// Created by Vadim on 30.04.17.
//

#include <iostream>
#include "binary_code.h"

binary_code::binary_code() 
		: data(std::vector<bool>())
		, pos(0)
{}

void binary_code::insert_symbol(uchar c)
{
	bool code_started = false;
	for (int i = 7; i >= 0; --i) 
	{
		if (c & (1 << i))
			code_started = true;
		if (code_started)
			data.push_back((c & (1 << i)) != 0);
	}
	if (!code_started)
		data.push_back(0);
}

void binary_code::build(std::vector<uchar>& symbols, size_t length)
{
	data.clear();
	for (size_t i = 0; i < symbols.size(); ++i)
		insert_symbol(symbols[i]);
	while (data.size() > length) data.pop_back();
}

std::vector<uchar> binary_code::get_code()
{
	std::vector <uchar> code;
	uchar max_deg = (uchar)(1 << 7);
	uchar cur_deg = max_deg;
	uchar cur = 0;
	while (pos & 7) ++pos;
	for (; pos < data.size(); ++pos) {
		bool x = data[pos];
		std::cout << "bool : " << x << '\n';
		if (x)
			cur += cur_deg;
		cur_deg >>= 1;
		if (!cur_deg) 
		{
			code.push_back(cur);
			cur_deg = max_deg;
			cur = 0;
		}
	}
	uchar cnt = (uchar) (7 - (data.size() & 7));
	if (cnt)
		code.push_back(cur);
	return code;
}

void binary_code::start_encoding()
{
	pos = 0;
}

bool binary_code::get_next_data() 
{
	return data[pos++];
}

bool binary_code::get_cur_data()
{
	return data[pos];
}

bool binary_code::empty() 
{
	return pos >= data.size();
}

void binary_code::insert_bool(bool bit) 
{
	data.push_back(bit);
}

size_t binary_code::get_size() {
	return data.size();
}

binary_code::~binary_code() 
{
	data.clear();
}