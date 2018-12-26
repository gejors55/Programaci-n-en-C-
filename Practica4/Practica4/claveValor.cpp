#include <iostream>
using namespace std;

#include "claveValor.h"

int getTamanno(const tIndicePalabras & l){
	return l.tam;
}

tRegistroIndicePalabras getRegistro(const tIndicePalabras & l, int pos){
	return l.datos[pos];
}

bool esta(const tIndicePalabras & l, const string & s, int & pos){
	bool encontrado = false;
	int ini = 0, fin = l.tam -1, mitad;
	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2;
		if (s == l.datos[mitad].clave) {
			encontrado = true;
			pos = mitad;
		}
		else if (s < l.datos[mitad].clave) {
			fin = mitad - 1;
		}
		else {
			ini = mitad + 1;
		}
	}
	if (!encontrado)
		pos = ini;
	return encontrado;
}

tListaCadenas buscar(const tIndicePalabras & l, const string & s){
	bool encontrado = false;
	int  ini = 0, fin = l.tam - 1, mitad;
	while (!encontrado) {
		mitad = (ini + fin) / 2;
		if (s == l.datos[mitad].clave) {
			encontrado = true;
		}
		else if (s < l.datos[mitad].clave) {
			fin = mitad - 1;
		}
		else {
			ini = mitad + 1;
		}
	}
	return l.datos[mitad].valor;
}

void insertar(tIndicePalabras & idx, const string & palabra, const string & nombreArchivo){
	tListaCadenas cadenaaux;
	int posicion;
	if (esta(idx, palabra, posicion)){
		cadenaaux = idx.datos[posicion].valor;
		insertar(cadenaaux, nombreArchivo);
		idx.datos[posicion].valor = cadenaaux;
	}
	else{
		for (int j = idx.tam - 1; j >= posicion; j--){ // mete todo a la siguiente posicion dejando un hueco para lo nuevo
			idx.datos[j + 1].clave = idx.datos[j].clave;
			idx.datos[j + 1].valor = idx.datos[j].valor;
			idx.datos[j + 1].valor.tam = idx.datos[j].valor.tam;
		}
		//nuevo registro con la lista de cadenas un solo elemento en la palabra, y una palabra mas( tam++)
		idx.datos[posicion].clave = palabra;
		idx.datos[posicion].valor.datos[0] = nombreArchivo;
		idx.datos[posicion].valor.tam = 1;
		idx.tam++;
	}
}

void imprimir(const tIndicePalabras & idx){
	for (int i = 0; i < idx.tam; i++){
		cout << idx.datos[i].clave << "  |  ";
		imprimir(idx.datos[i].valor);
	}
}
