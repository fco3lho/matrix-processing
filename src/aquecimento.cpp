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
		}
		file << endl;
	}

	file.close();
}

void readMatrix(){
	string line;
	ifstream file;
	vector<string> token;

	file.open("matrix.txt");

	if(file.is_open()){
		while(! file.eof()){
			getline(file, line);
			cout << line << endl;
			token.push_back(line);
		}

		int size = token.size();
		
		for(int i = 0; i < size-1; i++){
			cout << i << ":\t" << token[i] << endl;
		}

		file.close();
	}

	else{
		cout << "Não abriu!" << endl;
	}
}

void tokenizerVector(){
	string frase = "O brasileiro tem que ser estudado!";
	stringstream ss(frase);

	vector<string> tokens;
	string temp_str;

	while(getline(ss, temp_str, ' ')){
		tokens.push_back(temp_str);
	}

	int size = tokens.size();

	for(int i = 0; i < size; i++){
		cout << i << "- " << tokens[i] << endl;
	}
}