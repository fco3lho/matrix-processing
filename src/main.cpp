#include "matrix.hpp"

int main(){	

	int option = -1;

	writeText();
	execute();

	while(option != 0){
		
		cout << endl << "_________________________________________________________" << endl;
		cout << "Para recortar uma nova matriz, digite 1." << endl;
		cout << "Para finalizar, digite 0." << endl << endl << "Opção: ";
		cin >> option;
		cout <<	"_________________________________________________________" << endl << endl;

		if(option == 1){
			execute();
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