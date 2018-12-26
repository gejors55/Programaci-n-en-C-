#include <iostream>
#include <string>

using namespace std;
#include "indices.h"
#include "claveValor.h"
#include"listaCadenas.h"

int main(){
	tIndicePalabras palabras;
	tListaCadenas cadena;
	string fichero;
	string palabra;
	int pos;
	palabras.tam = 0;
	cout << "Buscador FdI-FP" << endl << endl;
	cout << "Por favor, introduzca el nombre del fichero raiz a partir del que se creará el índice: ";
	cin >> fichero;
	crearTabla(palabras, fichero);
	//int tamaño = getTamanno(palabras);
	//cout << " tabla tamano: " << tamaño << endl;
	//imprimir(palabras);
	cout << "Introduzca una palabra(fin para terminar): ";
	cin >> palabra;
	while (palabra != "fin"){
		if (esta(palabras, palabra, pos)){
			cadena = buscar(palabras, palabra);
			imprimir(cadena);
		}
		else{
			cout << "no se encuentra la palabra" << endl;
		}
		cout << "Introduzca una palabra(fin para terminar): ";
		cin >> palabra;
	}

	system("pause");
	return 0;
}