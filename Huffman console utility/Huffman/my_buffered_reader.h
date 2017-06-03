//
// Created by Vadim on 27.05.17.
//

#ifndef HUFFMAN_MY_BUFFERED_READER_H
#define HUFFMAN_MY_BUFFERED_READER_H

#include <fstream>
#include <iostream>
#include <string>

const size_t buffer_size = 64 * 1024 * 8;

class my_buffered_reader
{
private:
	std::ifstream fin;
	char* buffer;
	size_t pos = 0, size = 0;
public:
	my_buffered_reader();
	bool get(char& c);
	bool eof();
	void open(std::string const& filename);
	void close();
	friend bool operator !(my_buffered_reader const&);
	~my_buffered_reader();
};

class my_buffered_writer
{
private:
	std::ofstream fout;
	char* buffer;
	size_t pos = 0;
public:
	my_buffered_writer();
	void put(char c);
	void put(size_t x);
	void put(std::string const& s);
	void open(std::string const& filename);
	void close();
	friend bool operator !(my_buffered_writer const&);
	~my_buffered_writer();
};


#endif //HUFFMAN_MY_BUFFERED_READER_H
