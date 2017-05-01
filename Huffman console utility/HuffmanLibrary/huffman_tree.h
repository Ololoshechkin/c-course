//
// Created by Vadim on 30.04.17.
//

#ifndef HUFFMANLIBRARY_HUFFMAN_TREE_H
#define HUFFMANLIBRARY_HUFFMAN_TREE_H


#include <cstdint>
#include <climits>
#include <set>
#include "binary_code.h"

class huffman_tree
{
private:
	typedef unsigned char uchar;
	struct node
	{
		uint64_t cnt;
		uchar letter;
		node* left;
		node* right;
		node(uint64_t cnt = 0, node* left = nullptr, node* right = nullptr);
		node(uint64_t, uchar);
		bool operator<(const node) const;
		bool isLeaf() const;
		void dfs(uchar*, uchar);
	};
	std::set<node> nodes;
	node root;
	node* state;
	uint64_t*& letter_cnt;
	uchar letter_code[256];
	bool letter_exists[256];
public:
	huffman_tree(uint64_t*&);
	void build();
	void build_from_code(std::vector<uchar>&);
	std::vector<uchar> get_code() const;
	std::vector<uchar> encode(std::vector<uchar>&) const;
	std::vector<uchar> decode(std::vector<uchar>&) const;
};


#endif //HUFFMANLIBRARY_HUFFMAN_TREE_H
