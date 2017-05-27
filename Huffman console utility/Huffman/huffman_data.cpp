//
// Created by Vadim on 26.05.17.
//

#include "huffman_data.h"
#include "exceptions.h"

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

size_t huffman_data::get_size(std::ifstream& fin)
{
	size = 0;
	char c;
	while (fin.get(c)) {
		if (c == ' ')
			break;
		size = 10 * size + (c - '0');
	}
	return size;
}

std::ifstream& operator>>(std::ifstream& fin, huffman_data& code)
{
	code.get_size(fin);
	size_t rest = (code.size & 7);
	char c;
	while (code.bin.get_size() < code.size - rest && fin.get(c)) {
		code.bin.insert_symbol((uint8_t) (((int)c) + 128));
	}
	if (rest && fin.get(c)) {
		std::cout << "suffix(read) : ";
		for (size_t i = 7; i > 7 - rest; --i) {
			bool bit = (c & (1 << i)) != 0;
			code.bin.insert_bool(bit);
			std::cout << bit << ' ';
		}
		std::cout << '\n';
	}
	if (code.bin.get_size() < code.size) {
		throw bad_file_format_exception();
	}
	return fin;
}

std::ofstream& operator<<(std::ofstream& fout, huffman_data const& code_)
{
	huffman_data code = code_;
	std::cout << code.size << " : ";
	for (bool bit : code.bin.get_data())
		std::cout << bit << ' ';
	std::cout << '\n';
	fout << code.size << ' ';
	auto uint8_ts_code = code.bin.get_code();
	std::string string_code;
	for (uint8_t c : uint8_ts_code) {
		string_code.push_back((char) (((int) c) - 128));
	}
	fout << string_code;// << '\n';
	return fout;
}

tree_code_t::tree_code_t()
	: tree_code_t::tree_code_t(huffman_data(), huffman_data())
{}

tree_code_t::tree_code_t(huffman_data const& f, huffman_data const& s)
		: first(f)
		, second(s)
{}

std::ifstream& operator>>(std::ifstream& fin, tree_code_t& t) 
{
	fin >> t.first >> t.second;
	std::cout << "tree code : \n";
	std::cout << "size : " << t.first.size << "\ncode : ";
	for (bool bit : t.first.bin.get_data())
		std::cout << bit << ' ';
	std::cout << '\n';
	return fin;
}

std::ofstream& operator<<(std::ofstream& fout, tree_code_t const& t_)
{
	std::cout << "tree_code : \n";
	tree_code_t t = t_;
	fout << t.first << t.second;// << '\n';
	binary_code DEBUG = t_.second.bin;
	std::vector<uint8_t> letters = DEBUG.get_code();
	for (uint8_t c : letters)
		std::cout << (char) (((int) c) - 128);
	std::cout << "\ntree_code ENDED : \n";
	return fout;
}