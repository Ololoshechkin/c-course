//
// Created by Vadim on 30.04.17.
//

#ifndef HUFFMANLIBRARY_HUFFMAN_ARCHIVER_H
#define HUFFMANLIBRARY_HUFFMAN_ARCHIVER_H

#include "huffman_tree.h"
#include "binary_code.h"
#include <vector>

class huffman_archiver
{
private:
	std::vector<uint64_t> letter_cnt;
	huffman_tree tree;
public:
	typedef unsigned char uchar;
	huffman_archiver();
	void inc_letter_cnt(uchar, uint64_t);
	uint64_t get_letter_cnt(uchar);
	void clear();
	std::vector<uchar> get_tree_code();
	std::vector<uchar> encrypt(std::vector<uchar>&);
	void set_tree_code(std::vector<uchar>&);
	std::vector<uchar> decrypt(std::vector<uchar>&);
};


#endif //HUFFMANLIBRARY_HUFFMAN_ARCHIVER_H
