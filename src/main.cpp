#include "matrix.hpp"

int main(){	

	unordered_map <int, int**> hashMatrix;
	int option = -1;

	writeText();

	while(option != 0){
		execute(hashMatrix);

		cout << endl << "_________________________________________________________" << endl;
		cout << "Para recortar uma nova matriz, digite 1." << endl;
		cout << "Para finalizar, digite 0." << endl << endl << "Opção: ";
		cin >> option;
		cout <<	"_________________________________________________________" << endl << endl;
	}

	return 0;
}