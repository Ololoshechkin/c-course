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

int main(int argc, char* argv[])
{
	// TODO : delete this mesh...
	argc = 4;
	argv = new char*[4];
	//argv = {"huffman", "-decrypt", "code.txt", "decoded.txt"};
	argv[0] = "huffman", argv[1] = "-encrypt", argv[2] = "file.txt", argv[3] = "code.txt";
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
			archiver.inc_letter_cnt((unsigned char) (symbol + 128), 1);
		print("fin is read!");
		std::vector<unsigned char> tree_code = archiver.get_tree_code();
		print("get_tree_code is finnished!");
		for (unsigned char c : tree_code)
			fout << (char) (c - 128);
		print("tree_code is written to out!");
		std::vector<unsigned char> block_code;
		fin.close();
		print("fin closed");
		fin.open(argv[2]);
		print("fin opened again");
		print("get_tree_code is finnished!");
		while (!fin.eof()) {
			block_code.clear();
			for (size_t i = 0; i < block_size && fin.get(symbol); ++i)
				block_code.push_back((unsigned char) (symbol + 128));
			std::cout << "block.size : " << block_code.size() << std::endl;
			block_code = archiver.encrypt(block_code);
			std::cout << "block.size' : " << block_code.size() << std::endl;
			for (unsigned char c : block_code)
				fout << (char) (c - 128);
		}
	}
	else
	{
		print("gonna decrypt");
		std::vector<unsigned char> tree_code;
		int sharp_cnt = 0;
		char symbol;
		while (fin.get(symbol)) {
			if (symbol == '#')
				std::cout << symbol << '\n';
			else {
				std::cout << "          " << symbol << '\n';
				binary_code bin;
				bin.insert_symbol(symbol + 128);
				bin.start_encoding();
				while (!bin.empty())
					std::cout << (int) bin.get_next_data() << '\n';
			}
		}
		fin.close();
		fin.open(argv[2]);
		while (fin.get(symbol) && sharp_cnt != 3)
		{
			if (symbol == '#')
				++sharp_cnt;
			else
				sharp_cnt = 0;
			tree_code.push_back((unsigned char) (symbol + 128));
		}
		if (sharp_cnt != 3) 
			throw bad_file_format_exception();
		archiver.set_tree_code(tree_code);
		std::cout << "tree built!\n";
		std::vector<unsigned char> data_block;
		while (!fin.eof()) {
			data_block.clear();
			for (size_t i = 0; i < block_size && fin.get(symbol); ++i)
				data_block.push_back((unsigned char) (symbol + 128));
			data_block = archiver.decrypt(data_block);
			for (unsigned char c : data_block)
				fout << (char) (c - 128);
		}
	}
	fin.close();
	fout.close();
	return 0;
}