//
// Created by Vadim on 27.05.17.
//

#include "huffman_tester.h"

void huffman_tester::encrypt(std::string const& name1, std::string const& name2)
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

void huffman_tester::decrypt(std::string const& name1, std::string const& name2) 
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
	fin.close();
	fout.close();
}

int huffman_tester::test_item(bool should_encrypt)
{
	try {
		if (should_encrypt) {
			encrypt("file", "code");
		}
		decrypt("code", "file2");
	} catch (...) {
		return -1;
	}
	std::ifstream fin1("file");
	std::ifstream fin2("file2");
	char c1, c2;
	while (fin1.get(c1) && fin2.get(c2)) {
		if (c1 != c2) {
			return 0;
		}
	}
	if (fin1.get(c1) || fin2.get(c2)) {
		return 0;
	}
	return 1;
}

void huffman_tester::test()
{
	std::ofstream file("file");
	for (int i = 0; i < 100500; ++i) {
		file << char(rand() % 128);
	}
	file.close();
	file.open("code");
	std::cout << "random file test: " << (test_item(true) == 1 ? "ok" : "feelsbadman =(") << '\n';
	file << (int) (1e10) << ' ';
	for (int i = 0; i < (int) (1e10) / 8; ++i) {
		file << 'a';
	}
	file.close();
	std::cout << "big block size test: " << (test_item(false) == -1 ? "ok" : "feelsbadman =(") << '\n';
	file << 16 << ' ' << (char) ((1 << 128) - 1) << ' ' << (char) ((1 << 128) - 1) << 1 << 'a';
	file.close();
	std::cout << "bad tree test: " << (test_item(false) == -1 ? "ok" : "feelsbadman =(") << '\n';
	file.close();
}