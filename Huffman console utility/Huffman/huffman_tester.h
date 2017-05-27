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
	void encrypt(std::string name1, std::string name2) 
	{
		my_buffered_reader fin;
		fin.open(name1);
		if (!fin)
			throw std::runtime_error("input file open failed");
		my_buffered_writer fout;
		fout.open(name2);
		if (!fout)
			throw std::runtime_error("output file open failed");
		huffman_archiver archiver;
		
		std::cout << "encrypting...\n";
		
		char symbol;
		while (fin.get(symbol))
			archiver.inc_letter_cnt(symbol, 1);
		fin.close();
		fin.open(name1);
		tree_code_t tree_code = archiver.get_tree_code();
		tree_code.print(fout);
		std::vector<char> symbols_block;
		size_t block_cnt = 0;
		while (!fin.eof())
		{
			++block_cnt;
			symbols_block.clear();
			for (size_t i = 0; i < block_size && fin.get(symbol); ++i)
				symbols_block.push_back(symbol);
			auto code_block = archiver.encrypt(symbols_block);
			code_block.print(fout);
		}
		fin.close();
		fout.close();
	}
	void decrypt(std::string name1, std::string name2)
	{
		my_buffered_reader fin;
		fin.open(name1);
		if (!fin)
			throw std::runtime_error("input file open failed");
		my_buffered_writer fout;
		fout.open(name2);
		if (!fout)
			throw std::runtime_error("output file open failed");
		huffman_archiver archiver;
		
		std::cout << "decrypting...\n";
		tree_code_t tree_code;
		tree_code.read(fin);
		archiver.set_tree_code(tree_code);
		huffman_data data_block;
		size_t block_nmb = 0;
		while (!fin.eof())
		{
			++block_nmb;
			data_block.read(fin);
			std::vector<char> symbols = archiver.decrypt(data_block);
			for (char c : symbols)
				fout.put(c);
		}
		std::cout << "done.\ntime : " << (double) clock() / 1000000.0 << " sec.\n";
		fin.close();
		fout.close();
	}
public:
	bool test() {
		encrypt("file", "code");
		decrypt("code", "file2");
		std::ifstream fin1("file");
		std::ifstream fin2("file2");
		char c1, c2;
		while (fin1.get(c1) && fin2.get(c2))
			if (c1 != c2)
				return 0;
		if (!fin1.eof() || !fin2.eof())
			return 0;
		return 1;
	}
};


#endif //HUFFMAN_HUFFMAN_TESTER_H
