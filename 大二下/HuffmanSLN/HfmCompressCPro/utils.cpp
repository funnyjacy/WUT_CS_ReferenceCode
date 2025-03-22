#define _CRT_SECURE_NO_WARNINGS 1
#include "utils.h"
#include<fstream>
#include <iostream>
#include<sstream>
#include <bitset>
// 这个文件用来读写文件
bool ReadFile(std::string &filename, std::vector<unsigned char> &buffer)
{
	std::ifstream infile(filename, std::ios::binary); // 用二进制方式打开文件
	if (!infile) {
		std::cerr << "Filed to open file" << std::endl;
		return false;
	}

	infile.seekg(0, std::ios::end); // 指针移动到文件尾部
	std::streampos file_size = infile.tellg(); // 获取文件大小
	infile.seekg(0, std::ios::beg);

	buffer.resize(file_size); // 把文件大小分配给buffer

	infile.read((char *)buffer.data(), file_size); // 从头开始把数据给到buffer
	infile.close();

	return true;
}

bool WriteFile(std::string &filename, std::vector<unsigned char> &buffer)
{
	std::ofstream outfile(filename, std::ios::binary);
	if (!outfile) {
		std::cerr << "Failed to open file" << filename << std::endl;
		return false;
	}

	outfile.write((char *)buffer.data(), buffer.size());
	outfile.close();

	return true;
}

void BinaryString2Vector(std::string &str, std::vector<unsigned char> &vec)
{
	std::stringstream ss;
	ss << str;

	int byte_num = str.length() / 8;
	int bit_num = str.length() % 8;

	for (int i = 0; i < byte_num; i++) {
		std::bitset<8> bs; // 8位8位读取
		ss >> bs;
		unsigned char val = static_cast<unsigned char>(bs.to_ulong()); // 8位转成unsigned char
		vec.push_back(val);
	}

	if (!ss.eof()) { // 余下的位数也得放进去
		std::bitset<8> bs;
		ss >> bs; // 补
		bs = bs << 0 - bit_num;
		unsigned char val = static_cast<unsigned char>(bs.to_ulong());
		vec.push_back(val);
	}

}

void Vector2BinaryString(std::vector<unsigned char> &vec, std::string &str)
{
	for (unsigned char ch : vec) {
		std::bitset<8> bs(ch);
		str += bs.to_string();
	}
}