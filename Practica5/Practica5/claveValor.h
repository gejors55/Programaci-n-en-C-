#ifndef claveValor_h
#define claveValor_h

#include <string>
using namespace std;

#include "listaCadenas.h"

const int MAXCLAVES = 200;

typedef struct{
	string clave;
	tListaCadenas valor;	//lista de archivo donde estan las claves
}tRegistroIndicePalabras;

typedef struct{
	int tam;
	tRegistroIndicePalabras datos[MAXCLAVES];
}tIndicePalabras;

//Devuelve el tamaño de la tabla;
int getTamanno(const tIndicePalabras & l);
//Devuelve elregistro en pos;
tRegistroIndicePalabras getRegistro(const tIndicePalabras & l, int pos);
//Devuelve si la palabra es una clave en la tabla;
bool esta(const tIndicePalabras & l, const string & s, int & pos);
//dada una clave que está en la tabla devuelve la lista de cadenas asociada a esa clave.
tListaCadenas buscar(const tIndicePalabras & l, const string & s);
//Si palabra es ya una clave de la tabla, añade nombreArchivo a la lista de archivos correspondiente.
//Si no, crea un registro nuevo con esa información.
void insertar(tIndicePalabras & idx, const string & palabra, const string & nombreArchivo);
//Imprime la tabla;
void imprimir(const tIndicePalabras & idx);


#endif