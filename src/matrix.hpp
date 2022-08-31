#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

#define MAXTAM 15

using namespace std;

void writeText();	//Criação de uma matriz no arquivo txt
double keyFunction(int iLine, int fLine, int iColumn, int fColumn);
int verify(int key, unordered_map <int, int**> hashMatrix);
void execute(int key, unordered_map <int, int**> hashMatrix);

#endif