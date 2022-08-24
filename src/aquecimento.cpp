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
	vector<string> token;
	string numb;
	ifstream file;

	int initialLine, initialColumn, finalLine, finalColumn;
	int count = 0, countColumn = 0;
	int maxElements;

	cout << "Insira o número da linha inicial da matriz interna: ";
	cin >> initialLine;

	cout << "Insira o número da linha final da matriz interna: ";
	cin >> finalLine;

	cout << "Insira o número da coluna inicial da matriz interna: ";
	cin >> initialColumn;

	cout << "Insira o número da coluna final da matriz interna: ";
	cin >> finalColumn;

	maxElements = ((finalLine+1) - initialLine) * ((finalColumn+1) - initialColumn);

	file.open("matrix.txt");

	cout << "maxElements: " << maxElements << endl;

	if(file.is_open()){
		for(int i = 0; i < initialLine; i++){
			getline(file, numb);
		}

		while(! file.eof()){
			getline(file, numb, '\t');
			cout << numb << endl;

			if(count < maxElements){
				if((countColumn >= initialColumn) && (countColumn <= finalColumn)){
					token.push_back(numb);
					count++;
				}
			}
			
			countColumn++;

			if(countColumn == MAXTAM){
				countColumn = 0;
			}	
		}



		int size = token.size();
		int vetNumbers[size];

		for(int i = 0; i < size; i++){
			vetNumbers[i] = stoi(token[i]);
			cout << i << ":\t" << vetNumbers[i] << endl;
		}



		int dynamicLine = (finalLine - initialLine) + 1;
		int dynamicColumn = (finalColumn - initialColumn) + 1;
		int **dynamicMatrix;

		dynamicMatrix = new int *[dynamicLine];

		for(int i = 0; i < dynamicLine; i++){
			dynamicMatrix[i] = new int[dynamicColumn];
		}

		cout << endl << endl;

		int k = 0;

		for(int i = 0; i < dynamicLine; i++){
			for(int j = 0; j < dynamicColumn; j++){
				dynamicMatrix[i][j] = vetNumbers[k];
				cout << dynamicMatrix[i][j] << "\t";
				k++;
			}
			cout << endl;
		}


		file.close();
	}

	else{
		cout << "Did not open!" << endl;
	}
}
