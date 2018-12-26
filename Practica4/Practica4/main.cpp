/*Alejandro Rodríguez Calzada y Jorge González Soria*/
#include <iostream>
#include <string>

using namespace std;
#include "indices.h"
#include "claveValor.h"
#include"listaCadenas.h"


int main(){
	tIndicePalabras palabras;
	tListaCadenas cadena;
	tListaCadenas totales;
	tMatriz L;
	string fichero;
	string palabra;
	int pos;
	palabras.tam = 0;
	cout << "Buscador FdI-FP" << endl << endl;
	cout << "Por favor, introduzca el nombre del fichero raiz a partir del que se creará el índice: ";
	cin >> fichero;
	cout << "Cargando... [CORRECTO]" << endl;
	crearTabla(palabras, fichero, totales, L);
	cout << "Creando tablas... [CORRECTO]" << endl;
	tMatriz M = desdeEnlacesAMatriz(L);
	tVector v = vectorPropio(M);
	cout << "La información ha sido cargada. Puede empezar a hacer búsquedas" << endl;
	cout << "Introduzca una palabra('fin' para terminar): ";
	cin >> palabra;
	while (palabra != "fin"){
		if (esta(palabras, palabra, pos)){
			cadena = buscar(palabras, palabra);
			tVector semiVector = valoresSubLista(cadena, totales, v);
			ordenarLista(cadena, semiVector);
			for (int i = 0; i < cadena.tam; i++){
				cout << "Encontrada en '" << cadena.datos[i] << "' (Relevancia " << semiVector.datos[i] << ")." << endl;
			}
		}
		else{
			cout << "No se encuentra la palabra" << endl;
		}
		cout << "Introduzca una palabra(fin para terminar): ";
		cin >> palabra;
	}
	cout << "Gracias por usar el buscador." << endl;
	system("pause");
	return 0;
}

