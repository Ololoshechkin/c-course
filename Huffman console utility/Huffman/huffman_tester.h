//
// Created by Vadim on 27.05.17.
//

#ifndef HUFFMAN_HUFFMAN_TESTER_H
#define HUFFMAN_HUFFMAN_TESTER_H

#include "huffman_archiver.h"
#include <iostream>
#include <fstream>

class huffman_tester
{
private:
	huffman_archiver archiver;
	size_t block_size = 4 * 1024;
	void encrypt(std::string name1, std::string name2);
	void decrypt(std::string name1, std::string name2);
	int test_item(bool should_encrypt);
public:
	void test();
};


#endif //HUFFMAN_HUFFMAN_TESTER_H
