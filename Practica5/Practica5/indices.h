#ifndef indices_h
#define indices_h
#include <string>
#include <fstream>
#include <cctype>
#include<algorithm>

using namespace std;

#include "claveValor.h"
#include "listaCadenas.h"
#include "matriz.h"

//A partir de archivoInicial, rellena la tabla tabla, tras haberla inicializado(a vacía).
void crearTabla(tIndicePalabras & tabla, const string & archivoInicial, tListaCadenas & totales, tMatriz & L);
//Inicializa tipos tListaCadenas a vacio.
void inicializar(tListaCadenas & cadena);
//Procesa el archivo linea a linea
void procesar(tListaCadenas & noVisitados, tListaCadenas & visitados, tIndicePalabras & tabla, const string & archivo, tListaCadenas & totales, tMatriz & L, int columna);
//Procesa la linea
void procesarLinea(tListaCadenas & noVisitados, tListaCadenas & visitados, string linea, tIndicePalabras & tabla, const string & archivo, tListaCadenas & totales, tMatriz & L, int columna);
//Crea la matriz L
void crearL(tMatriz & L);

//Fuciones auxiliares al main


//Crea un subvector del mismo tamaño que cadena con los numero asociados a la cadena.
tVector valoresSubLista(tListaCadenas & cadena, tListaCadenas & totales, tVector & v);
//Ordena la lista de cadenas de la palabra deseada y su vector asociado
void ordenarLista(tListaCadenas & cadena, tVector & v);


#endif