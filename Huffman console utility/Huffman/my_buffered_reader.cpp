//
// Created by Vadim on 27.05.17.
//

#include "my_buffered_reader.h"

my_buffered_reader::my_buffered_reader()
{
	buffer = new char[buffer_size];
}

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

my_buffered_reader::~my_buffered_reader() 
{
	delete[] buffer;
}



my_buffered_writer::my_buffered_writer() 
{
	buffer = new char[buffer_size];
}

void my_buffered_writer::put(char c) 
{
	/*if (pos == buffer_size)
		fout.write(buffer, buffer_size), pos = 0;
	buffer[pos++] = c;*/
	fout.put(c);
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
	//pos = 0;
	fout.open(filename);
}

void my_buffered_writer::close() 
{
	//if (pos)
	//	fout.write(buffer, pos + 1), pos = 0;
	fout.close();
}

bool operator!(my_buffered_writer const& w)
{
	return !w.fout;
}

my_buffered_writer::~my_buffered_writer() 
{
	delete [] buffer;
}