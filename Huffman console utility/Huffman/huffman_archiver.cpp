//
// Created by Vadim on 30.04.17.
//

#include <iostream>
#include "huffman_archiver.h"

huffman_archiver::huffman_archiver()
		: letter_cnt(std::vector<uint64_t>(UCHAR_MAX, 0))
		, tree(letter_cnt)
{}

void huffman_archiver::inc_letter_cnt(char c, uint64_t delta) 
{
	letter_cnt[c - CHAR_MIN] += delta;
}

uint64_t huffman_archiver::get_letter_cnt(huffman_archiver::uchar c)
{
	return letter_cnt[c];
}

void huffman_archiver::clear()
{
	letter_cnt.assign(UCHAR_MAX, 0);
}

std::vector<huffman_archiver::uchar> huffman_archiver::get_tree_code()
{
	std::cout << "gonna build tree\n";
	tree.build();
	std::cout << "tree is built\n";
	return tree.get_code();
}

std::vector<huffman_archiver::uchar> huffman_archiver::encrypt(std::vector<huffman_archiver::uchar>& data) 
{
	return tree.encode(data);
}

void huffman_archiver::set_tree_code(std::vector<huffman_archiver::uchar>& tree_code)
{
	tree.build_from_code(tree_code);
}

std::vector<huffman_archiver::uchar> huffman_archiver::decrypt(std::vector<huffman_archiver::uchar>& code_block) 
{
	return tree.decode(code_block);
}