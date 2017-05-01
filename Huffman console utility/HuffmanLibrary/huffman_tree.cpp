//
// Created by Vadim on 30.04.17.
//

#include <tkDecls.h>
#include <vector>
#include "huffman_tree.h"

huffman_tree::node::node(uint64_t cnt = 0, node* left = nullptr, node* right = nullptr)
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

huffman_tree::node::bool operator<(const huffman_tree::node other) const
{
	return cnt < other.cnt;
}

bool huffman_tree::node::isLeaf() const
{
	return !left && !right;
}

void huffman_tree::node::dfs(uchar* codes_arr, uchar code)
{
	if (isLeaf())
		codes_arr[letter] = code;
	if (left)
		left->dfs(codes_arr, (uchar) (code << 1));
	if (right)
		right->dfs(codes_arr, (uchar) ((code << 1) + 1));
}

huffman_tree::huffman_tree(uint64_t*&)
		: nodes(std::set())
		, root(node())
		, letter_cnt(letter_cnt)
		, state(nullptr)
{}

void huffman_tree::build()
{
	for (uchar c = 0; c < 256; ++c) 
	{
		if (!letter_cnt[c]) 
		{
			letter_exists[c] = false;
			break;
		}
		letter_exists[c] = true;
		nodes.insert(node(letter_cnt[c], c));
	}
	while (nodes.size() != 1)
	{
		node first = *nodes.erase(nodes.begin());
		node second = *nodes.erase(nodes.begin());
		node father = node(first.cnt + second.cnt, &first, &second);
		nodes.insert(father);
	}
	root = *nodes.erase(nodes.begin());
	state = &root;
	root.dfs(letter_code, 0);
}

void huffman_tree::build_from_code(std::vector<uchar>& code) 
{
	for (size_t i = 0; i < code.size() - 3; i += 2)
		letter_code[code[2 * i]] = code[2 * i + 1];
	build();
}

std::vector<uchar> huffman_tree::get_code() const
{
	std::vector<uchar> answer;
	for (uchar c = 0; c < 256; ++c)
		if (letter_exists[c])
			answer.push_back(c), answer.push_back(letter_code[c]);
	answer.push_back('#');
	answer.push_back('#');
	answer.push_back('#');
	return answer;
}

std::vector<uchar> huffman_tree::encode(std::vector<uchar>& data) const 
{
	binary_code bin;
	for (uchar c : data)
	{
		bin.insert_symbol(letter_code[c]);
	}
	return bin.get_code();
}

std::vector<uchar> huffman_tree::decode(std::vector<uchar>& code) const 
{
	std::vector<uchar> data;
	binary_code bin;
	bin.build(code);
	bin.start_encoding();
	while (!bin.empty())
	{
		state = (bin.get_next_data() ?  state->left : state->right);
		if (state->isLeaf())
			data.push_back(state->letter), state = &root;
	}
	return data;
}