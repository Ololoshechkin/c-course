//
// Created by Vadim on 30.04.17.
//

#include <iostream>
#include "binary_code.h"
#include "exceptions.h"

binary_code::binary_code() 
		: data(std::vector<bool>())
		, pos(0)
{}

void binary_code::insert_symbol(uint8_t c)
{
	for (int i = 7; i >= 0; --i) 
	{
		data.push_back((c & (1 << i)) != 0);
	}
}

void binary_code::build(std::vector<uint8_t>& symbols)
{
	data.clear();
	for (size_t i = 0; i < symbols.size(); ++i)
		insert_symbol(symbols[i]);
}

std::vector<uint8_t> binary_code::get_code()
{
	std::vector <uint8_t> code;
	uint8_t cur = 0;
	int deg = 7;
	for (bool bit : data) {
		cur += (((int) bit) << deg);
		--deg;
		if (deg < 0) 
			deg = 7, code.push_back(cur), cur = 0;
	}
	if (data.size() & 7) {
		code.push_back(cur);
		std::cout << "suffix : ";
		for (int i = 7; i > 0; --i) {
			std::cout << (int) (bool)(cur & (1 << i)) << ' ';
		}
		std::cout << '\n';
	}
	return code;
}

void binary_code::start_encoding()
{
	pos = 0;
}

bool binary_code::get_next_data() 
{
	if (pos == data.size())
		throw bad_file_format_exception();
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

size_t binary_code::get_size() const
{
	return data.size();
}

binary_code::~binary_code() 
{
	data.clear();
}