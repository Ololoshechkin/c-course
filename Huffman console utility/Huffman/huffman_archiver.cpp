//
// Created by Vadim on 30.04.17.
//

#include <iostream>
#include <string>
#include "huffman_archiver.h"

uint8_t huffman_archiver::to_uint8_t(char c) const {
	return (uint8_t) (((int) c) + 128);
}

char huffman_archiver::to_char(uint8_t c) const {
	return (char) (((int) c) - 128);
}

std::vector<uint8_t> huffman_archiver::to_unsigned(const std::vector<char>& chars) const
{
	std::vector<uint8_t> unsigned_chars;
	for (char c : chars) {
		unsigned_chars.push_back(to_uint8_t(c));
	}
	return unsigned_chars;
}

std::vector<char> huffman_archiver::to_signed(const std::vector<uint8_t>& unsigned_chars) const
{
	std::vector<char> chars;
	for (uint8_t uc : unsigned_chars) {
		chars.push_back(to_char(uc));
	}
	return chars;
}

huffman_archiver::huffman_archiver()
		: letter_cnt(std::vector<uint64_t>(256, 0))
		, tree(letter_cnt)
{}

void huffman_archiver::inc_letter_cnt(char c, uint64_t delta) 
{
	letter_cnt[to_uint8_t(c)] += delta;
}

uint64_t huffman_archiver::get_letter_cnt(char c)
{
	return letter_cnt[to_uint8_t(c)];
}

void huffman_archiver::clear()
{
	letter_cnt.assign(256, 0);
}

tree_code_t huffman_archiver::get_tree_code()
{
	tree.build();
	return tree.get_code();
}

huffman_data huffman_archiver::encrypt(std::vector<char> const& data) const
{
	return tree.encode(to_unsigned(data));
}

void huffman_archiver::set_tree_code(tree_code_t& tree_code)
{
	tree.build_from_code(tree_code);
}

std::vector<char> huffman_archiver::decrypt(huffman_data& code) const
{
	return to_signed(tree.decode(code));
}