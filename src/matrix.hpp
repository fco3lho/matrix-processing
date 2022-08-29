#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

#define MAXTAM 10

using namespace std;

void writeText();	//Criação de uma matriz no arquivo txt
double keyFunction(int iLine, int fLine, int iColumn, int fColumn);
int verify(int key, unordered_map <int, int**> hashMatrix);
void execute(unordered_map <int, int**> hashMatrix);	//Lê a matriz maior, tokeniza os elementos, cria matriz interna e faz o cálculo da matriz interna com sua transposta

#endif