#include <iostream>
using namespace std;

#include "indices.h"
#include "checkML.h"

void crearTabla(tIndicePalabras & tabla, const string & archivoInicial, tListaCadenas & totales, tMatriz & L){
	tListaCadenas visitados, noVisitados;
	string archivo;
	inicializar(visitados);
	inicializar(noVisitados);
	inicializar(totales);
	insertar(noVisitados, archivoInicial);
	insertar(totales, archivoInicial);		//totales.tam -1 es la posicion donde se ha insertado
	L = matrizConstante(0, 1);		//creo matriz L tam 1
	int columna = -1;
	while (noVisitados.tam != 0){
		archivo = getCadena(noVisitados, 0);
		insertar(visitados, archivo);
		eliminar(noVisitados, 0);
		columna++;
		procesar(noVisitados, visitados, tabla, archivo, totales, L, columna);
	}
}

void inicializar(tListaCadenas & cadena){
	cadena.tam = 0;
}

void procesar(tListaCadenas & noVisitados, tListaCadenas & visitados, tIndicePalabras & tabla, const string & archivo, tListaCadenas & totales, tMatriz & L, int columna){
	string linea;
	ifstream fichero;
	fichero.open(archivo);
	while (!fichero.eof()){
		getline(fichero, linea);
		procesarLinea(noVisitados, visitados, linea, tabla, archivo, totales, L, columna);
		}
	fichero.close();
}

void procesarLinea(tListaCadenas & noVisitados, tListaCadenas & visitados, string linea, tIndicePalabras & tabla, const string & archivo, tListaCadenas & totales, tMatriz & L, int columna){
	int tamano = linea.size();
	string palabra;
	int inicio = 0;
	int enlace, pos;
	bool hay = false;	
	for (int i = 0; i < tamano; i++){
		if (linea[i] == '<'){
			enlace = linea.find(">", i);
			palabra = linea.substr(i + 1, enlace - i -1);
			transform(palabra.begin(), palabra.end(), palabra.begin(), std::tolower);
			if (buscar(totales, palabra, pos)){
				L.datos[pos][columna] = 1;		// si esta en la posicion i: Lij = 1;
			}
			else{													
				insertar(totales, palabra);							
				insertar(noVisitados, palabra);
				crearL(L);
				L.datos[L.filas - 1][columna] = 1;
			}
			i = enlace;
			inicio = i + 1;
		}
		else if (!ispunct(linea[i]) && !isspace(linea[i])){
			hay = true;
		}
		else if (hay &&(ispunct(linea[i]) || isspace(linea[i]))){
			palabra = linea.substr(inicio, i - inicio);
			inicio = i + 1;
			transform(palabra.begin(), palabra.end(), palabra.begin(), std::tolower);
			insertar(tabla, palabra, archivo);
			hay = false;
		}
		else{
			inicio++;
		}
	}
}

void crearL(tMatriz & L){
	L.columnas++;
	L.filas++;
	for (int i = 0; i < L.columnas; i++){
		L.datos[i][L.columnas - 1] = 0;
		L.datos[L.filas - 1][i] = 0;
	}
}

//Funciones auxiliares al MAIN

tVector valoresSubLista(tListaCadenas & cadena, tListaCadenas & totales, tVector & v){
	tVector valor;
	valor.tam = cadena.tam;
	int pos = 0;
	for (int i = 0; i < cadena.tam; i++){
		buscar(totales, cadena.datos[i], pos);
		valor.datos[i] = v.datos[pos];
	}
	return valor;
}

void ordenarLista(tListaCadenas &cadena, tVector &v){
	string nombre;
	double tmp;
	for (int i = 0; i < v.tam - 1; i++) {
		for (int j = v.tam - 1; j > i; j--) {
			if (v.datos[j] > v.datos[j - 1]) {
				tmp = v.datos[j];
				v.datos[j] = v.datos[j - 1];
				v.datos[j - 1] = tmp;
				nombre = cadena.datos[j];
				cadena.datos[j] = cadena.datos[j - 1];
				cadena.datos[j - 1] = nombre;
			}
		}
	}
}

