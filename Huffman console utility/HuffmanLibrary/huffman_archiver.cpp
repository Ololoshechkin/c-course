//
// Created by Vadim on 30.04.17.
//

#include "huffman_archiver.h"

huffman_archiver::huffman_archiver()
		: letter_cnt(new uint64_t[256])
		, tree(huffman_tree(letter_cnt))
{}

void huffman_archiver::inc_letter_cnt(uchar c, uint64_t delta) 
{
	letter_cnt[c] += delta;
}

uint64_t huffman_archiver::get_letter_cnt(uchar c)
{
	return letter_cnt[c];
}

void huffman_archiver::clear()
{
	memset(letter_cnt, 0, sizeof(letter_cnt));
}

std::vector<uchar> huffman_archiver::get_tree_code()
{
	return tree.get_code();
}

std::vector<uchar> huffman_archiver::encrypt(std::vector<uchar>& data) 
{
	return tree.encode(data);
}

void huffman_archiver::set_tree_code(std::vector<uchar>& tree_code)
{
	tree.build_from_code(tree_code);
}

std::vector<uchar> huffman_archiver::decrypt(std::vector<uchar>& code_block) 
{
	return tree.decode(code_block);
}

