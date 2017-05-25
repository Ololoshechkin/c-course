#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "exceptions.h"
#include "huffman_archiver.h"
#include "binary_code.h"

const size_t block_size = 4 * 1024;

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

void print(std::string const& msg)
{
	std::cout << msg << std::endl;
}

void print(char c)
{
	std::cout << c << std::endl;
}

size_t get_size(std::ifstream& fin) {
	size_t size = 0;
	char c;
	while (fin.get(c)) {
		if (c == ' ')
			break;
		size = 10 * size + (c - '0');
	}
	return size;
}

int main(int argc, char* argv[])
{
	// TODO : delete this mesh...
	print("program started");
	if (argc != 4)
	{
		throw illegal_argument_cnt_exception(argc, 3);
	}
	if (!cmp(argv[1], "-encrypt") && !cmp(argv[1], "-decrypt"))
	{
		throw illegal_arguments_exception(1, "\"-encrypt\" or \"-decrypt\"");
	}
	print("gonna fin");
	std::ifstream fin;
	fin.open(argv[2]);
	if (!fin)
		throw std::runtime_error("input file open failed");
	print("gonna fout");
	std::ofstream fout(argv[3]);
	if (!fout)
		throw std::runtime_error("output file open failed");
	huffman_archiver archiver;
	if (cmp(argv[1], "-encrypt")) 
	{
		print("gonna encrypt");
		char symbol;
		while (fin.get(symbol))
			archiver.inc_letter_cnt(symbol, 1);
		print("fin is read!");
		std::vector<char> tree_code = archiver.get_tree_code();
		print("get_tree_code is finnished!");
		binary_code bin;
		for (char c : tree_code) {
			unsigned char uc = ((int) c - CHAR_MIN);
			bin.insert_symbol(uc);
		}
		bin.start_encoding();
		int balance = 0;
		while (!bin.empty()) {
			balance += bin.get_cur_data() ? 1 : -1;
			std::cout << " tree(next) : " << bin.get_next_data() << '\n';
			if (!balance)
				break;
		}
		uchar ctz = 0, d = 7;
		while (!bin.empty()) {
			ctz += bin.get_next_data() << d;
			--d;
			if (d < 0) {
				d = 7;
				std::cout << " tree(symbol-next) : " << (char) ((int) ctz - CHAR_MIN) << '\n';
				ctz = 0;
			}
		}
		for (char c : tree_code)
			fout << c;
		print("tree_code is written to out!");
		std::vector<char> block_code;
		fin.close();
		print("fin closed");
		fin.open(argv[2]);
		print("fin opened again");
		print("get_tree_code is finnished!");
		while (!fin.eof()) {
			block_code.clear();
			for (size_t i = 0; i < block_size && fin.get(symbol); ++i)
				block_code.push_back(symbol);
			std::cout << "block.size : " << block_code.size() << std::endl;
			block_code = archiver.encrypt(block_code);
			std::cout << "block.size' : " << block_code.size() << std::endl;
			for (char c : block_code)
				fout << c;
		}
	}
	else if (cmp(argv[1], "-decrypt"))
	{
		print("gonna decrypt");
		std::vector<char> tree_code;
		int sharp_cnt = 0;
		char symbol;
		fin.close();
		fin.open(argv[2]);
		while (fin.get(symbol) && sharp_cnt != 3)
		{
			if (symbol == '#')
				++sharp_cnt;
			else
				sharp_cnt = 0;
			tree_code.push_back(symbol);
		}
		if (sharp_cnt != 3) 
			throw bad_file_format_exception();
		archiver.set_tree_code(tree_code);
		std::cout << "tree built!\n";
		std::vector<char> data_block;
		while (!fin.eof()) {
			data_block.clear();
			size_t block_size = get_size(fin);
			for (size_t i = 0; i < block_size && fin.get(symbol); ++i)
				data_block.push_back(symbol);
			data_block = archiver.decrypt(block_size, data_block);
			for (char c : data_block)
				fout << c;
		}
	}
	else
	{
		std::cout << "bad argument (expected -encrypt or -decrypt)";
	}
	fin.close();
	fout.close();
	return 0;
}