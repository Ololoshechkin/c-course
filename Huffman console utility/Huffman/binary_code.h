//
// Created by Vadim on 30.04.17.
//

#ifndef HUFFMANLIBRARY_BINARY_CODE_H
#define HUFFMANLIBRARY_BINARY_CODE_H

#include <vector>

#define uchar unsigned char

class binary_code
{
private:
	std::vector<bool> data;
	size_t pos;
public:
	binary_code();
	void insert_symbol(uchar);
	void build(std::vector<uchar>&, size_t);
	std::vector<uchar> get_code();
	void start_encoding();
	bool get_next_data();
	bool get_cur_data();
	bool empty();
	void insert_bool(bool);
	size_t get_size();
	~binary_code();
};


#endif //HUFFMANLIBRARY_BINARY_CODE_H
