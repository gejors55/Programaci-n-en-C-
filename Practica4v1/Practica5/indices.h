#ifndef indices_h
#define indices_h
#include <string>
#include <fstream>
#include <cctype>
#include<algorithm>

using namespace std;

#include "claveValor.h"
#include "listaCadenas.h"

//A partir de archivoInicial, rellena la tabla tabla, tras haberla inicializado(a vacía).
void crearTabla(tIndicePalabras & tabla, const string & archivoInicial);
//Inicializa tipos tListaCadenas a vacio.
void inicializar(tListaCadenas & cadena);
//Procesa el archivo linea a linea
void procesar(tListaCadenas & noVisitados, tListaCadenas & visitados, tIndicePalabras & tabla, const string & archivo);
//Procesa la linea
void procesarLinea(tListaCadenas & noVisitados, tListaCadenas & visitados, string linea, tIndicePalabras & tabla, const string & archivo);

#endif