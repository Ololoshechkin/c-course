//
// Created by Vadim on 30.04.17.
//

#ifndef HUFFMANLIBRARY_HUFFMAN_ARCHIVER_H
#define HUFFMANLIBRARY_HUFFMAN_ARCHIVER_H

#include "huffman_tree.h"
#include "binary_code.h"
#include <vector>

#define uchar unsigned char

class huffman_archiver
{
private:
	std::vector<uint64_t> letter_cnt;
	huffman_tree tree;
	uchar to_uchar(char);
	char to_char(uchar);
	std::vector<uchar> to_unsigned(const std::vector<char>&);
	std::vector<char> to_signed(const std::vector<uchar>&);
public:
	huffman_archiver();
	void inc_letter_cnt(char, uint64_t);
	uint64_t get_letter_cnt(char);
	void clear();
	std::vector<char> get_tree_code();
	std::vector<char> encrypt(std::vector<char>&);
	void set_tree_code(std::vector<char>&);
	std::vector<char> decrypt(size_t, std::vector<char>&);
};


#endif //HUFFMANLIBRARY_HUFFMAN_ARCHIVER_H
