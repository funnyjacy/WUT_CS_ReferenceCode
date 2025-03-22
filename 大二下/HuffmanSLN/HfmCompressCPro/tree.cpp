#define _CRT_SECURE_NO_WARNINGS 1
#include"tree.h"

Node *HuffmanTree::getNode(unsigned char ch, int freq, Node *left, Node *right)
{
	Node *node = new Node;
	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node; // 产生根节点
}

void HuffmanTree::insertNode(vector<Node *> &vec, Node *node)
{
	int index = 0;

	if (vec.size() > 0) { // 频率低，编码长，放最后
		while (vec[index]->freq > node->freq) {
			index++;
			if (index >= vec.size()) {
				break;
			}
		}
	}

	vec.insert(vec.begin() + index, node);
}

void HuffmanTree::buildHuffmanTree(vector<unsigned char> &data) // 读入图片编码的符号
{
	unordered_map<unsigned char, int> freqs;
	for (unsigned char val : data) { // 计算符号的频率
		freqs[val] += 1;
	}

	for (auto pair : freqs) {
		Node *node = getNode(pair.first, pair.second, nullptr, nullptr);
		insertNode(huffman_tree, node);
	}

	while (huffman_tree.size() != 1) // 建的是一个左树
	{
		Node *left = huffman_tree.back(); // 保证最后的两个一定是频率最小
		huffman_tree.pop_back();
		Node *right = huffman_tree.back();
		huffman_tree.pop_back();

		int sum = left->freq + right->freq; //两个最小加起来

		Node *node = getNode('\0', sum, left, right); // 生成新的节点
		insertNode(huffman_tree, node); // 插入
	}
}

void HuffmanTree::encode(Node *node, string str)
{
	// 编码
	if (node == nullptr) {
		return;
	}

	//若是叶子结点
	if (node->left == nullptr && node->right == nullptr) {
		huffman_code[node->ch] = str; // 编码
		return;
	}

	encode(node->left, str + '0'); // 按左右的顺序合成二进制编码
	encode(node->right, str + '1');
}

void HuffmanTree::huffman_encode(std::vector<unsigned char> &data, std::string &encoded_string)
{
	buildHuffmanTree(data); // 建树

	Node *root = huffman_tree[0];
	encode(root, ""); // 第一次什么都不加

	for (unsigned char ch : data) {
		encoded_string += huffman_code[ch]; // 
	}

}

void HuffmanTree::decode(Node *node, int &index, std::string &encoded_string, std::vector<unsigned char> &decoded_data)
{
	if (node == nullptr || index >= (int)encoded_string.size()) {
		return;
	}

	if (node->left == nullptr && node->right == nullptr) {
		decoded_data.push_back(node->ch);
		return;
	}

	index++;
	if (encoded_string[index] == '0') {
		decode(node->left, index, encoded_string, decoded_data);
	}
	else {
		decode(node->right, index, encoded_string, decoded_data);
	}
}

void HuffmanTree::huffman_decode(std::string &encoded_string, std::vector<unsigned char> &decoded_data)
{
	int index = -1;
	Node *root = huffman_tree[0];

	while (index < (int)encoded_string.size() - 2) {
		decode(root, index, encoded_string, decoded_data);
	}
}

void HuffmanTree::delete_node(Node *node)
{
	if (node != nullptr) {
		delete_node(node->left);
		delete_node(node->right);
		delete node;
	}
}

HuffmanTree::~HuffmanTree() {
	Node *root = huffman_tree[0];
	delete_node(root);
}