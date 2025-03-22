#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdlib.h>
#include"tree.h"
#include"utils.h"
using namespace std;
std::string img_name = "../Pic.bmp";
std::string filename4encoded = "../Pic.hfm";
std::string filename4decoded = "../decoded_Pic.bmp";

int main()
{
	HuffmanTree hfTree;
	std::vector<unsigned char> buffer;
	if (ReadFile(img_name, buffer) == false) {
		return -1;
	}
	std::string encoded_string;
	hfTree.huffman_encode(buffer, encoded_string); // encoded_string放的是每个符号的编码（二进制字符串形式）

	std::vector<unsigned char> encoded_data;
	BinaryString2Vector(encoded_string, encoded_data);
	WriteFile(filename4encoded, encoded_data); // 把二进制代码写入文件（8位8位的）这一步相当于是编码完成了

	buffer.clear();
	if (ReadFile(filename4encoded, buffer) == false) {
		return -1;
	}

	std::string str = "";
	Vector2BinaryString(buffer, str); // 把buffer中的数据转换为二进制字符串

	std::vector <unsigned char> decoded_data;
	hfTree.huffman_decode(str, decoded_data); // 解码操作
	WriteFile(filename4decoded, decoded_data); // 写入文件

}