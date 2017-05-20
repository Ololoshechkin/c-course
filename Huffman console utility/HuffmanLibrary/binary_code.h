//
// Created by Vadim on 30.04.17.
//

#ifndef HUFFMANLIBRARY_BINARY_CODE_H
#define HUFFMANLIBRARY_BINARY_CODE_H

#include <vector>

class binary_code
{
private:
	std::vector<bool> data;
	size_t pos;
public:
    typedef unsigned char uchar;
	binary_code();
	void insert_symbol(uchar);
	void build(std::vector<uchar>&);
	std::vector<uchar> get_code();
	void start_encoding();
	bool get_next_data();
	bool empty();
	~binary_code();
};


#endif //HUFFMANLIBRARY_BINARY_CODE_H
