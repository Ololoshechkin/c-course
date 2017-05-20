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

void binary_code::build(std::vector<uchar>& symbols, bool last_is_cnt = false)
{
	data.clear();
	for (size_t i = 0; i < symbols.size() - 2; ++i)
		insert_symbol(symbols[i]);
	for (uchar i = 0; i < symbols.back(); ++i) 
		insert_bool(symbols[i - 2] & (1 << (7 - i)));
	std::cout << data.size() << std::endl;
}

std::vector<binary_code::uchar> binary_code::get_code(bool with_postinfo = false)
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
			code.push_back((uchar) cur);
			cur_deg = max_deg;
			cur = 0;
		}
	}
	uchar cnt = (uchar) (7 - (data.size() & 7));
	if (cnt)
		code.push_back((uchar) cur);
	if (with_postinfo)
		code.push_back(cnt);
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

binary_code::~binary_code() 
{
	data.clear();
}