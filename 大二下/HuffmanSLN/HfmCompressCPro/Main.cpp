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
	hfTree.huffman_encode(buffer, encoded_string); // encoded_string�ŵ���ÿ�����ŵı��루�������ַ�����ʽ��

	std::vector<unsigned char> encoded_data;
	BinaryString2Vector(encoded_string, encoded_data);
	WriteFile(filename4encoded, encoded_data); // �Ѷ����ƴ���д���ļ���8λ8λ�ģ���һ���൱���Ǳ��������

	buffer.clear();
	if (ReadFile(filename4encoded, buffer) == false) {
		return -1;
	}

	std::string str = "";
	Vector2BinaryString(buffer, str); // ��buffer�е�����ת��Ϊ�������ַ���

	std::vector <unsigned char> decoded_data;
	hfTree.huffman_decode(str, decoded_data); // �������
	WriteFile(filename4decoded, decoded_data); // д���ļ�

}