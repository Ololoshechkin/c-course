//
// Created by Vadim on 26.05.17.
//

#ifndef HUFFMAN_HUFFMAN_DATA_H
#define HUFFMAN_HUFFMAN_DATA_H


#include <cstdio>
#include <iostream>
#include <fstream>
#include "binary_code.h"
#include "my_buffered_reader.h"

class huffman_data {
private:
	size_t get_size(my_buffered_reader&);
public:
	size_t size;
	binary_code bin;
	huffman_data();
	huffman_data(size_t, const binary_code&);
	huffman_data(const binary_code&);
	//friend std::istream& operator>>(std::istream&, huffman_data&);
	//friend std::ostream& operator<<(std::ostream&, huffman_data const&);
	void read(my_buffered_reader&);
	void print(my_buffered_writer&) const;
};

struct tree_code_t {
	huffman_data first;
	huffman_data second;
	tree_code_t();
	tree_code_t(huffman_data const&, huffman_data const&);
	//friend std::istream& operator>>(std::istream&, tree_code_t&);
	//friend std::ostream& operator<<(std::ostream&, tree_code_t&);
	void read(my_buffered_reader&);
	void print(my_buffered_writer&) const;
};


#endif //HUFFMAN_HUFFMAN_DATA_H
