//
// Created by Vadim on 30.04.17.
//

#ifndef HUFFMANLIBRARY_HUFFMAN_ARCHIVER_H
#define HUFFMANLIBRARY_HUFFMAN_ARCHIVER_H

#include "huffman_tree.h"
#include "binary_code.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <exception>
#include "huffman_data.h"

class huffman_archiver
{
private:
	std::vector<uint64_t> letter_cnt;
	huffman_tree tree;
	uint8_t to_uint8_t(char) const;
	char to_char(uint8_t) const;
	std::vector<uint8_t> to_unsigned(const std::vector<char>&) const;
	std::vector<char> to_signed(const std::vector<uint8_t>&) const;
public:
	huffman_archiver();
	void inc_letter_cnt(char, uint64_t);
	uint64_t get_letter_cnt(char);
	void clear();
	tree_code_t get_tree_code();
	huffman_data encrypt(std::vector<char> const&) const;
	void set_tree_code(tree_code_t&);
	std::vector<char> decrypt(huffman_data&) const;
	~huffman_archiver();
};


#endif //HUFFMANLIBRARY_HUFFMAN_ARCHIVER_H
