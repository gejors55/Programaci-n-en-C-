#include <iostream>
using namespace std;

#include "listaCadenas.h"


int getTamanno(const tListaCadenas & l){
	return l.tam;
}

string getCadena(const tListaCadenas & l, int pos){
	return l.datos[pos];
}

void insertar(tListaCadenas & l, const string & s){
	bool esta = false;
	if (l.tam < 0){
		l.tam = 0;
	}
	for (int i = 0; i < l.tam; i++){
		if (l.datos[i] == s){
			esta = true;
		}
	}
	if (!esta){
		l.datos[l.tam] = s;
		l.tam++;
	}
}

bool buscar(const tListaCadenas & l, const string & s){
	bool encontrado = false;
	int i = 0;
	while (!encontrado && i < l.tam){
		if (s == l.datos[i]){
			encontrado = true;
		}
		else{
			i++;
		}
	}
	return encontrado;
}

void eliminar(tListaCadenas & l, int pos){
	for (int i = pos; i < l.tam; i++){
		l.datos[i] = l.datos[i + 1];
	}
	l.tam--;
}

void imprimir(const tListaCadenas & l){
	cout << l << endl;
}

ostream & operator <<(ostream & salida, const tListaCadenas & l){
	salida << "[";
	for (int i = 0; i < l.tam; i++){
		salida << l.datos[i];
		if (i != l.tam - 1){
			salida << " ,";
		}
	}
	salida << "]";
	return salida;
}