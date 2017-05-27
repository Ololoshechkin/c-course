//
// Created by Vadim on 30.04.17.
//

#ifndef HUFFMANLIBRARY_BINARY_CODE_H
#define HUFFMANLIBRARY_BINARY_CODE_H

#include <vector>
#include <cstdint>


class binary_code
{
private:
	std::vector<bool> data;
	size_t pos;
public:
	binary_code();
	void insert_symbol(uint8_t);
	void build(std::vector<uint8_t>&);
	std::vector<uint8_t> get_code();
	void start_encoding();
	bool get_next_data();
	bool get_cur_data();
	bool empty();
	void insert_bool(bool);
	size_t get_size() const;
	~binary_code();
	
	// TODO : delete that shit>
	std::vector<bool> get_data() {
		return data;
	}
};


#endif //HUFFMANLIBRARY_BINARY_CODE_H
