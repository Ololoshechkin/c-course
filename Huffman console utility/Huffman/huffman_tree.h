//
// Created by Vadim on 30.04.17.
//

#ifndef HUFFMANLIBRARY_HUFFMAN_TREE_H
#define HUFFMANLIBRARY_HUFFMAN_TREE_H


#include <cstdint>
#include <climits>
#include <set>
#include <cstdlib>
#include "binary_code.h"
#include "huffman_data.h"


const bool LEFT_CODE = false;
const bool RIGHT_CODE = true;
const bool DOWN_CODE = false;
const bool UP_CODE = true;

class huffman_tree
{
private:
	struct node
	{
		uint64_t cnt;
		uint8_t letter;
		node* left;
		node* right;
		node(uint64_t cnt = 0, node* left = nullptr, node* right = nullptr);
		node(uint64_t, uint8_t);
		bool isLeaf() const;
		void dfs(std::vector<std::vector<bool>>&, std::vector<bool>&);
	};
	node* root;
	std::vector<uint64_t>& letter_cnt;
	std::vector<std::vector<bool>> letter_code;
	std::vector<bool> letter_exists;
	void to_tree_code(node*, binary_code&) const;
	void to_letters_in_dfs_order(node*, std::vector<uint8_t>&) const;
	void from_letters_in_dfs_order(node*, std::vector<uint8_t> const&, size_t&);
	void from_tree_code(node*, binary_code&);
	void destruct_dfs(node*);
public:
	friend bool compareNodes(node* l, node* r);
	huffman_tree(std::vector<uint64_t>&);
	void build();
	void build_from_code(tree_code_t&);
	tree_code_t get_code() const;
	huffman_data encode(std::vector<uint8_t> const&) const;
	std::vector<uint8_t> decode(huffman_data&) const;
	~huffman_tree();
};


#endif //HUFFMANLIBRARY_HUFFMAN_TREE_H
