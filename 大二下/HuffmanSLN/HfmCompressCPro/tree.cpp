#define _CRT_SECURE_NO_WARNINGS 1
#include"tree.h"

Node *HuffmanTree::getNode(unsigned char ch, int freq, Node *left, Node *right)
{
	Node *node = new Node;
	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node; // �������ڵ�
}

void HuffmanTree::insertNode(vector<Node *> &vec, Node *node)
{
	int index = 0;

	if (vec.size() > 0) { // Ƶ�ʵͣ����볤�������
		while (vec[index]->freq > node->freq) {
			index++;
			if (index >= vec.size()) {
				break;
			}
		}
	}

	vec.insert(vec.begin() + index, node);
}

void HuffmanTree::buildHuffmanTree(vector<unsigned char> &data) // ����ͼƬ����ķ���
{
	unordered_map<unsigned char, int> freqs;
	for (unsigned char val : data) { // ������ŵ�Ƶ��
		freqs[val] += 1;
	}

	for (auto pair : freqs) {
		Node *node = getNode(pair.first, pair.second, nullptr, nullptr);
		insertNode(huffman_tree, node);
	}

	while (huffman_tree.size() != 1) // ������һ������
	{
		Node *left = huffman_tree.back(); // ��֤��������һ����Ƶ����С
		huffman_tree.pop_back();
		Node *right = huffman_tree.back();
		huffman_tree.pop_back();

		int sum = left->freq + right->freq; //������С������

		Node *node = getNode('\0', sum, left, right); // �����µĽڵ�
		insertNode(huffman_tree, node); // ����
	}
}

void HuffmanTree::encode(Node *node, string str)
{
	// ����
	if (node == nullptr) {
		return;
	}

	//����Ҷ�ӽ��
	if (node->left == nullptr && node->right == nullptr) {
		huffman_code[node->ch] = str; // ����
		return;
	}

	encode(node->left, str + '0'); // �����ҵ�˳��ϳɶ����Ʊ���
	encode(node->right, str + '1');
}

void HuffmanTree::huffman_encode(std::vector<unsigned char> &data, std::string &encoded_string)
{
	buildHuffmanTree(data); // ����

	Node *root = huffman_tree[0];
	encode(root, ""); // ��һ��ʲô������

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