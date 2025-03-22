#ifndef TREE_H
#define TREE_H
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

struct Node {
	unsigned char ch;
	int freq;
	Node *left;
	Node *right;
};

class HuffmanTree {
private:
	vector<Node *> huffman_tree;

	std::unordered_map<unsigned char, std::string>huffman_code;

	Node *getNode(unsigned char ch, int freq, Node *left, Node *right);  // 创建节点

	void insertNode(vector<Node *> &vec, Node *node);

	void buildHuffmanTree(vector<unsigned char> &data);  // 构建哈夫曼树 

	void encode(Node *node, string str); // 编码

	void decode(Node *node, int &index, std::string &encoded_string, std::vector<unsigned char> &decoded_data);

	void delete_node(Node *node);
public:
	HuffmanTree() {};
	~HuffmanTree();

	void huffman_encode(std::vector<unsigned char> &data, std::string &encoded_string);

	void huffman_decode(std::string &encoded_string, std::vector<unsigned char> &decoded_data);
};



#endif // !TREE?H
