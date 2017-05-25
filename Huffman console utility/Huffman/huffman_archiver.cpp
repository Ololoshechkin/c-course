//
// Created by Vadim on 30.04.17.
//

#include <iostream>
#include <string>
#include "huffman_archiver.h"

uchar huffman_archiver::to_uchar(char c) {
	return (uchar) (c - CHAR_MIN);
}

char huffman_archiver::to_char(uchar c) {
	return (char) ((int) c + CHAR_MIN);
}

std::vector<uchar> huffman_archiver::to_unsigned(const std::vector<char>& chars) {
	std::vector<uchar> unsigned_chars;
	for (char c : chars) {
		unsigned_chars.push_back(to_uchar(c));
	}
	return unsigned_chars;
}

std::vector<char> huffman_archiver::to_signed(const std::vector<uchar>& unsigned_chars) {
	std::vector<char> chars;
	for (uchar uc : unsigned_chars) {
		chars.push_back(to_char(uc));
	}
	return chars;
}

huffman_archiver::huffman_archiver()
		: letter_cnt(std::vector<uint64_t>(UCHAR_MAX, 0))
		, tree(letter_cnt)
{}

void huffman_archiver::inc_letter_cnt(char c, uint64_t delta) 
{
	letter_cnt[to_uchar(c)] += delta;
}

uint64_t huffman_archiver::get_letter_cnt(char c)
{
	return letter_cnt[to_uchar(c)];
}

void huffman_archiver::clear()
{
	letter_cnt.assign(UCHAR_MAX, 0);
}

std::vector<char> huffman_archiver::get_tree_code()
{
	std::cout << "gonna build tree\n";
	tree.build();
	std::cout << "tree is built\n";
	return to_signed(tree.get_code());
}

std::vector<char> huffman_archiver::encrypt(std::vector<char>& data) 
{
	std::vector<uchar> udata = to_unsigned(data);
	auto code = tree.encode(udata);
	std::string size = std::to_string(code.first);
	std::vector<char> encrypted;
	for (char c: size)
		encrypted.push_back(c);
	encrypted.push_back(' ');
	for (uchar uc : code.second)
		encrypted.push_back(to_char(uc));
	return encrypted;
}

void huffman_archiver::set_tree_code(std::vector<char>& tree_code)
{
	std::vector<uchar> code = to_unsigned(tree_code);
	tree.build_from_code(code);
}

std::vector<char> huffman_archiver::decrypt(size_t block_size, std::vector<char>& code_block) 
{
	std::vector<uchar> block = to_unsigned(code_block);
	return to_signed(tree.decode(block_size, block));
}