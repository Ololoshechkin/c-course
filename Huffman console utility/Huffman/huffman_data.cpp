//
// Created by Vadim on 26.05.17.
//

#include "huffman_data.h"
#include "exceptions.h"

const size_t max_block_size = 128 * 1024 * 8 * 3;

huffman_data::huffman_data() 
	: huffman_data::huffman_data(binary_code())
{}

huffman_data::huffman_data(size_t size, const binary_code& bin)
		: size(size)
		, bin(bin)
{}

huffman_data::huffman_data(const binary_code& bin) 
	: huffman_data::huffman_data(bin.get_size(), bin)
{}

size_t huffman_data::get_size(my_buffered_reader& fin)
{
	size = 0;
	char c;
	while (fin.get(c)) {
		if (c == ' ')
			break;
		size = 10 * size + (c - '0');
		if (size > max_block_size) {
			throw bad_file_format_exception("incorrect block size");
		}
	}
	return size;
}

void huffman_data::read(my_buffered_reader& fin)
{
	size = 0;
	bin = binary_code();
	get_size(fin);
	size_t rest = (size & 7);
	char c;
	while (bin.get_size() < size - rest && fin.get(c)) {
		bin.insert_symbol((uint8_t) (((int)c) + 128));
	}
	if (rest && fin.get(c)) {
		uint8_t uc = (uint8_t)(((int) c) + 128);
		for (size_t i = 7; i > 7 - rest; --i) 
			bin.insert_bool((uc & (1 << i)) != 0);
	}
	if (bin.get_size() < size) {
		throw bad_file_format_exception();
	}
}

void huffman_data::print(my_buffered_writer& fout) const
{
	huffman_data code = *this;
	fout.put(code.size);
	fout.put(' ');
	auto uint8_code = code.bin.get_code();
	std::string string_code;
	for (uint8_t c : uint8_code) {
		string_code.push_back((char) (((int) c) - 128));
	}
	fout.put(string_code);
}

tree_code_t::tree_code_t()
	: tree_code_t::tree_code_t(huffman_data(), huffman_data())
{}

tree_code_t::tree_code_t(huffman_data const& f, huffman_data const& s)
		: first(f)
		, second(s)
{}

void tree_code_t::read(my_buffered_reader& fin) 
{
	first.read(fin);
	second.read(fin);
}

void tree_code_t::print(my_buffered_writer& fout) const
{
	first.print(fout);
	second.print(fout);
}
