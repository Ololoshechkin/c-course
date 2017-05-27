#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include "exceptions.h"
#include "huffman_archiver.h"
#include "binary_code.h"

const size_t block_size = 128 * 1024 * 8;

bool cmp(char* arg, std::string str)
{
	size_t len = strlen(arg);
	if (len != str.length())
		return false;
	for (size_t i = 0; i < len; ++i)
		if (arg[i] != str[i])
			return false;
	return true;
}


uint64_t file_size(std::string name) {
	std::ifstream fin(name, std::ifstream::ate | std::ifstream::binary);
	uint64_t ans = (uint64_t) fin.tellg();
	fin.close();
	return ans;
}

void encrypt(int argc, char* argv[]) 
{
	std::ifstream fin;
	fin.open(argv[2]);
	if (!fin)
		throw std::runtime_error("input file open failed");
	std::ofstream fout(argv[3]);
	if (!fout)
		throw std::runtime_error("output file open failed");
	huffman_archiver archiver;
	
	std::cout << "encrypting...\n";
	uint64_t old_size = file_size(argv[2]), new_size = 0;
	
	char symbol;
	while (fin.get(symbol))
		archiver.inc_letter_cnt(symbol, 1);
	fin.close();
	fin.open(argv[2]);
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
	new_size = file_size(argv[3]);
	std::cout << "done (" << block_cnt << " blocks total, old file size : "
	          << 1.0 * old_size / 1024.0 << " kbs , new file size :"
	          << 1.0 * new_size / 1024.0 << " kbs, compressing ratio :"
	          << 100.0 * ((double) old_size - (double) new_size) / (double) old_size << "%"
	          << ")\ntime : " << (double) clock() / 1000000.0 << " sec.\n";
}

void decrypt(int argc, char* argv[]) 
{
	std::ifstream fin;
	fin.open(argv[2]);
	if (!fin)
		throw std::runtime_error("input file open failed");
	std::ofstream fout(argv[3]);
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
			fout << c;
	}
	std::cout << "done.\ntime : " << (double) clock() / 1000000.0 << " sec.\n";	
	fin.close();
	fout.close();
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		throw illegal_argument_cnt_exception(argc - 1, 3);
	}
	if (!cmp(argv[1], "-encrypt") && !cmp(argv[1], "-decrypt"))
	{
		throw illegal_arguments_exception(1, "\"-encrypt\" or \"-decrypt\"");
	}
	if (cmp(argv[1], "-encrypt"))
	{
		encrypt(argc, argv);
	}
	else if (cmp(argv[1], "-decrypt"))
	{
		decrypt(argc, argv);
	}
	else
	{
		std::cout << "bad argument (expected -encrypt or -decrypt)";
	}
	return 0;
}