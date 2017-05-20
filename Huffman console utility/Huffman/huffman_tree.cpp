//
// Created by Vadim on 30.04.17.
//

#include <vector>
#include <iostream>
#include "huffman_tree.h"

huffman_tree::node::node(uint64_t cnt, node* left, node* right)
		: cnt(cnt)
		, letter(0)
		, left(left)
		, right(right)
{}

huffman_tree::node::node(uint64_t cnt, uchar c)
		: cnt(cnt)
		, letter(c)
		, left(nullptr)
		, right(nullptr)
{}

bool compareNodes(huffman_tree::node* l, huffman_tree::node* r)
{
	return l->cnt < r->cnt;
}

bool huffman_tree::node::isLeaf() const
{
	return left == nullptr && right == nullptr;
}

void huffman_tree::node::dfs(std::vector<uchar>& codes_arr, uchar code = 0)
{
	if (isLeaf())
		codes_arr[letter] = code;
	if (left)
		left->dfs(codes_arr, (uchar) (code << 1));
	if (right)
		right->dfs(codes_arr, (uchar) ((code << 1) + 1));
}

void huffman_tree::to_tree_code(node* v, binary_code& bin) const
{
	if (v->left) {
		bin.insert_bool(1);
		to_tree_code(v->left, bin);
	}
	if (v->right) {
		bin.insert_bool(1);
		to_tree_code(v->right, bin);
	}
	bin.insert_bool(0);
}

void huffman_tree::to_letters_in_dfs_order(node* v, std::vector<uchar>& answer) const
{
	if (v->left)
		to_letters_in_dfs_order(v->left, answer);
	if (v->right)
		to_letters_in_dfs_order(v->right, answer);
	if (v->isLeaf()) {
		answer.push_back(v->letter);
	}
}

void huffman_tree::from_letters_in_dfs_order(node* v, std::vector<uchar>& answer, size_t& pos)
{
	if (v->left)
		from_letters_in_dfs_order(v->left, answer, pos);
	if (v->right)
		from_letters_in_dfs_order(v->right, answer, pos);
	if (v->isLeaf()) {
		v->letter = answer[pos++];
	}
}

void huffman_tree::from_tree_code(node* v, binary_code& bin)
{
	if (bin.get_cur_data())
	{
		if (!v->left) {
			v->left = new node();
			bin.get_next_data();
			from_tree_code(v->left, bin);
		}
		else
		{
			v->right = new node();
			bin.get_next_data();
			from_tree_code(v->right, bin);
		}
	}
	else
	{
		bin.get_next_data();
		return;
	}
}

huffman_tree::huffman_tree(std::vector<uint64_t>& letter_cnt)
		: root(nullptr)
		, state(nullptr)
		, letter_cnt(letter_cnt) 
		, letter_code(std::vector<uchar> (UCHAR_MAX, 0))
		, letter_exists(std::vector<bool> (UCHAR_MAX, false))
{}

void huffman_tree::build()
{
	std::cout << "building tree...\n";
	std::set<node*, bool (*)(node*, node*)> nodes(compareNodes);
	for (uchar c = 0; ; ++c) 
	{
		if (!letter_cnt[c]) 
		{
			letter_exists[c] = false;
			if (c == UCHAR_MAX - 1)
				break;
			continue;
		}
		letter_exists[c] = true;
		nodes.insert(new node(letter_cnt[c], c));
		if (c == UCHAR_MAX - 1)
			break;
	}
	std::cout << "nodes() built...\n";
	while (nodes.size() != 1)
	{
		node* first = *nodes.begin();
		nodes.erase(first);
		node* second = *nodes.begin();
		nodes.erase(second);
		nodes.insert(new node(first->cnt + second->cnt, first, second));
	}
	root = *nodes.begin();
	std::cout << "root.dfs(...)\n";
	root->dfs(letter_code);
	state = root;
	std::cout << "tree is built\n";
}

void huffman_tree::build_from_code(std::vector<huffman_tree::uchar>& code) 
{
	std::cout << "building tree from code :\n";
	binary_code bin;
	for (size_t i = 0; i < code.size() - 3; ++i)
		bin.insert_symbol(code[i]);
	bin.start_encoding();
	from_tree_code(root, bin);
	std::vector<uchar> letters = bin.get_code(false);
	size_t pos = 0;
	from_letters_in_dfs_order(root, letters, pos);
}

std::vector<huffman_tree::uchar> huffman_tree::get_code() const
{
	binary_code bin;
	to_tree_code(root, bin);
	std::vector<uchar> answer = bin.get_code(false);
	to_letters_in_dfs_order(root, answer);
	answer.push_back('#' + 128);
	answer.push_back('#' + 128);
	answer.push_back('#' + 128);
	return answer;
}

std::vector<huffman_tree::uchar> huffman_tree::encode(std::vector<huffman_tree::uchar>& data) const 
{
	binary_code bin;
	for (uchar c : data)
	{
		std::cout << "symbol : " << (int) (c) << '>' << (int)letter_code[c] << '\n';
		bin.insert_symbol(letter_code[c]);
	}
	std::vector<uchar> code = bin.get_code(true);
	return code;
}

std::vector<huffman_tree::uchar> huffman_tree::decode(std::vector<huffman_tree::uchar>& code) 
{
	std::cout << "tree.decode()\n";
	std::vector<uchar> data;
	std::cout << "data.\n";
	binary_code bin;
	std::cout << "bin.\n";
	bin.build(code, true);
	std::cout << "bin.build(code)\n";
	bin.start_encoding();
	std::cout << "bin.start()\n";
	std::cout << "empty? " << bin.empty() << std::endl;
	while (!bin.empty())
	{
		std::cout << "in cycle\n";
		int ok = (int) bin.get_next_data();
		std::cout << ok << "\n";
		state = (ok ?  state->right : state->left);
		if (state->isLeaf())
			data.push_back(state->letter), state = root;
	}
	return data;
}