//
// Created by Vadim on 26.05.17.
//

#ifndef HUFFMAN_HUFFMAN_DATA_H
#define HUFFMAN_HUFFMAN_DATA_H


#include <cstdio>
#include <iostream>
#include <fstream>
#include "binary_code.h"

class huffman_data {
private:
	size_t get_size(std::ifstream&);
public:
	size_t size;
	binary_code bin;
	huffman_data();
	huffman_data(size_t, const binary_code&);
	huffman_data(const binary_code&);
	friend std::ifstream& operator>>(std::ifstream&, huffman_data&);
	friend std::ofstream& operator<<(std::ofstream&, huffman_data const&);
};

struct tree_code_t {
	huffman_data first;
	huffman_data second;
	tree_code_t();
	tree_code_t(huffman_data const&, huffman_data const&);
	friend std::ifstream& operator>>(std::ifstream&, tree_code_t&);
	friend std::ofstream& operator<<(std::ofstream&, tree_code_t const&);
};


#endif //HUFFMAN_HUFFMAN_DATA_H
