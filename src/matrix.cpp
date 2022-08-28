#include "matrix.hpp"

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

void execute(){
	vector<string> token;
	string numb;
	ifstream file;

	int initialLine, initialColumn, finalLine, finalColumn;
	int count = 0, countColumn = 0;

	cout << "Insira o número da linha inicial da matriz interna: ";
	cin >> initialLine;

	cout << "Insira o número da linha final da matriz interna: ";
	cin >> finalLine;

	cout << "Insira o número da coluna inicial da matriz interna: ";
	cin >> initialColumn;

	cout << "Insira o número da coluna final da matriz interna: ";
	cin >> finalColumn;

	int maxElements = ((finalLine+1) - initialLine) * ((finalColumn+1) - initialColumn);

	file.open("matrix.txt");

	if(file.is_open()){ //Abrindo o arquivo txt
		for(int i = 0; i < initialLine; i++){
			getline(file, numb);
		}

		while(! file.eof()){
			getline(file, numb, '\t');

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
		}

		int dynamicLine = (finalLine - initialLine) + 1;
		int dynamicColumn = (finalColumn - initialColumn) + 1;

						/* Matriz Dinâmica */

		int **dynamicMatrix;

		dynamicMatrix = new int *[dynamicLine];

		for(int i = 0; i < dynamicLine; i++){
			dynamicMatrix[i] = new int[dynamicColumn];
		}

		cout << "___________________________________________" << endl << "\tMatriz normal" << endl << endl;

		int x = 0;

		for(int i = 0; i < dynamicLine; i++){
			for(int j = 0; j < dynamicColumn; j++){
				dynamicMatrix[i][j] = vetNumbers[x];
				cout << dynamicMatrix[i][j] << "\t";
				x ++;
			}
			cout << endl;
		}

						/* Matriz Transposta */

		int **transposedMatrix;

		transposedMatrix = new int *[dynamicColumn];

		for(int i = 0; i < dynamicColumn; i++){
			transposedMatrix[i] = new int[dynamicLine];
		}

		cout << "___________________________________________" << endl << "\tMatriz transposta" << endl << endl;

		for(int i = 0; i < dynamicColumn; i++){
			for(int j = 0; j < dynamicLine; j++){
				transposedMatrix[i][j] = dynamicMatrix[j][i];
				cout << transposedMatrix[i][j] << "\t";
			}
			cout << endl;
		}

						/* Multiplicação das matrizes */

		int **calculatedMatrix;

		calculatedMatrix = new int *[dynamicLine];

		for(int i = 0; i < dynamicLine; i++){
			calculatedMatrix[i] = new int[dynamicLine];
		}

		cout << "___________________________________________" << endl << "\tMatriz calculada" << endl << endl;

		for(int i = 0; i < dynamicLine; i++){
			for(int k = 0; k < dynamicLine; k++){
				calculatedMatrix[i][k] = 0;
				for(int j = 0; j < dynamicColumn; j++){
					calculatedMatrix[i][k] += dynamicMatrix[i][j] * transposedMatrix[j][k];
				}
			}
		}

		for(int i = 0; i < dynamicLine; i++){
			for(int j = 0; j < dynamicLine; j++){
				cout << calculatedMatrix[i][j] << "\t";
			}
			cout << endl;
		}

		file.close(); //Fecha o arquivo txt
	}

	else{
		cout << "Não foi possível abrir o arquivo." << endl;
	}
}