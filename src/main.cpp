#include "matrix.hpp"

int main(){	

	unordered_map <int, int**> hashMatrix;
	int key = 0;
	int option = -1;

	writeText();
	execute(key, hashMatrix);

	while(option != 0){
		
		cout << endl << "_________________________________________________________" << endl;
		cout << "Para recortar uma nova matriz, digite 1." << endl;
		cout << "Para finalizar, digite 0." << endl << endl << "Opção: ";
		cin >> option;
		cout <<	"_________________________________________________________" << endl << endl;

		if(option == 1){
			execute(key, hashMatrix);
		}
		else if(option == 0){
			return 0;
		}
		else{
			cout << "Opção inválida" << endl;
		}
	}

	return 0;
}