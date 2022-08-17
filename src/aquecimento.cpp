#include "aquecimento.hpp"

void writeText(){
	int value;

	ofstream file;

	file.open("matrix.txt");

	srand(time(NULL));

	for(int i = 0; i < MAXTAM; i++){
		for(int j = 0; j < MAXTAM; j++){
			value = rand() % 100;
			file << value << "\t";
			cout << "Rodando..." << endl;
		}
		file << endl;
	}

	file.close();
}