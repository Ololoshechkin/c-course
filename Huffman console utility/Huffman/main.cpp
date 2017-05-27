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

void solve(int argc, char* argv[]) 
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
		fin.close();
		fin.open(argv[2]);
		for (int c = CHAR_MIN; c <= CHAR_MAX; ++c) {
			if (archiver.get_letter_cnt((char) c))
				std::cout << "cnt[" << (char)  c << "] = " << archiver.get_letter_cnt(c) << '\n';
		}
		print("fin is read!");
		fout << archiver.get_tree_code();
		print("get_tree_code is finnished!");
		std::vector<char> symbols_block;
		while (!fin.eof())
		{
			symbols_block.clear();
			for (size_t i = 0; i < block_size && fin.get(symbol); ++i)
				symbols_block.push_back(symbol);
			fout << archiver.encrypt(symbols_block);
		}
		print("it's ok!");
	}
	else if (cmp(argv[1], "-decrypt"))
	{
		print("gonna decrypt");
		tree_code_t tree_code;
		fin >> tree_code;
		print("tree code is obtained");
		archiver.set_tree_code(tree_code);
		print("tree code is set to archiver");
		huffman_data data_block;
		while (!fin.eof())
		{
			fin >> data_block;
			std::vector<char> symbols = archiver.decrypt(data_block);
			for (char c : symbols)
				fout << c;
		}
		print("it's ok!");
	}
	else
	{
		std::cout << "bad argument (expected -encrypt or -decrypt)";
	}
	fin.close();
	fout.close();
}

int main(int argc, char* argv[])
{
	std::cout << (uint8_t) (200) << ' ' << (char) (200) << '\n';
	char* arguments[4];
	arguments[0] = "huffman", arguments[1] = "-encrypt", arguments[2] = "file.txt", arguments[3] = "code.txt";
	solve(4, arguments);
	arguments[0] = "huffman", arguments[1] = "-decrypt", arguments[2] = "code.txt", arguments[3] = "2.txt";
	solve(4, arguments);
	return 0;
}