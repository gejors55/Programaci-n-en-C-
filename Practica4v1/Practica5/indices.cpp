#include <iostream>
using namespace std;

#include "indices.h"
#include "claveValor.h"
#include"listaCadenas.h"

void crearTabla(tIndicePalabras & tabla, const string & archivoInicial){
	tListaCadenas visitados, noVisitados;
	string archivo;
	inicializar(visitados);
	inicializar(noVisitados);
	insertar(noVisitados, archivoInicial);
	while (noVisitados.tam != 0){
		archivo = getCadena(noVisitados, 0);
		insertar(visitados, archivo);
		eliminar(noVisitados, 0);
		procesar(noVisitados, visitados, tabla, archivo);
	}
}

void inicializar(tListaCadenas & cadena){
	cadena.tam = 0;
}

void procesar(tListaCadenas & noVisitados, tListaCadenas & visitados, tIndicePalabras & tabla, const string & archivo){
	string linea;
	ifstream fichero;
	fichero.open(archivo);
	while (!fichero.eof()){
		getline(fichero, linea);
		procesarLinea(noVisitados, visitados, linea, tabla, archivo);
		}
	fichero.close();
}

void procesarLinea(tListaCadenas & noVisitados, tListaCadenas & visitados, string linea, tIndicePalabras & tabla, const string & archivo){
	int tamano = linea.size();
	string palabra;
	int inicio = 0;		//donde empieza la palabra
	int enlace;
	bool hay = false;
	for (int i = 0; i < tamano; i++){
		if (linea[i] == '<'){
			enlace = linea.find(">", i);
			palabra = linea.substr(i + 1, enlace - i -1);
			std::transform(palabra.begin(), palabra.end(), palabra.begin(), std::tolower);
			if (!buscar(visitados, palabra) && !buscar(noVisitados, palabra)){
				insertar(noVisitados, palabra);
			}
			i = enlace;
			inicio = i +1;
		}
		else if (!ispunct(linea[i]) && !isspace(linea[i])){
			hay = true;
		}
		else if (hay &&(ispunct(linea[i]) || isspace(linea[i]))){
			palabra = linea.substr(inicio, i - inicio);
			inicio = i + 1;
			std::transform(palabra.begin(), palabra.end(), palabra.begin(), std::tolower);
			insertar(tabla, palabra, archivo);
			hay = false;
		}
		else{
			inicio++;
		}
	}
}
