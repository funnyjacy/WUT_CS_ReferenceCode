#ifndef UTILS_H
#define UTILS_H

#include<string>
#include<vector>


bool ReadFile(std::string &filename, std::vector<unsigned char> &buffer);

bool WriteFile(std::string &filename, std::vector<unsigned char> &buffer);

void BinaryString2Vector(std::string &str, std::vector<unsigned char> &vec);

void Vector2BinaryString(std::vector<unsigned char> &vec, std::string &str);

#endif // !UTILS
