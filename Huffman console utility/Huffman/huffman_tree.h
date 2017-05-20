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
		bool isLeaf() const;
		void dfs(std::vector<uchar>&, uchar);
	};
	node* root;
	node* state;
	std::vector<uint64_t>& letter_cnt;
	std::vector<uchar> letter_code;
	std::vector<bool> letter_exists;
	void to_tree_code(node*, binary_code&) const;
	void to_letters_in_dfs_order(node*, std::vector<uchar>&) const;
	void from_letters_in_dfs_order(node*, std::vector<uchar>&, size_t&);
	void from_tree_code(node*, binary_code&);
public:
	friend bool compareNodes(node* l, node* r);
	huffman_tree(std::vector<uint64_t>&);
	void build();
	void build_from_code(std::vector<uchar>&);
	std::vector<uchar> get_code() const;
	std::vector<uchar> encode(std::vector<uchar>&) const;
	std::vector<uchar> decode(std::vector<uchar>&);
};


#endif //HUFFMANLIBRARY_HUFFMAN_TREE_H
