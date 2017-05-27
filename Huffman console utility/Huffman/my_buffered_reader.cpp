//
// Created by Vadim on 27.05.17.
//

#include "my_buffered_reader.h"

bool my_buffered_reader::get(char& c) 
{
	if (pos == size)
	{
		if (fin.eof())
			return false;
		pos = 0;
		fin.read(buffer, buffer_size);
		size = (size_t) fin.gcount();
	}
	c = buffer[pos++];
	return true;
}

bool my_buffered_reader::eof() 
{
	return size == pos && fin.eof();
}

void my_buffered_reader::open(std::string const& filename) 
{
	fin.open(filename);
}

void my_buffered_reader::close() 
{
	fin.close();
}

bool operator!(my_buffered_reader const& r) 
{
	return !r.fin;
}



void my_buffered_writer::put(char c) 
{
	fout << c;
}

void my_buffered_writer::put(size_t x)
{
	fout << x;
}

void my_buffered_writer::put(std::string const& s)
{
	fout << s;
}

void my_buffered_writer::open(std::string const& filename) 
{
	fout.open(filename);
}

void my_buffered_writer::close() 
{
	fout.close();
}

bool operator!(my_buffered_writer const& w)
{
	return !w.fout;
}