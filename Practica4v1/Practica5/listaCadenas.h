#ifndef listaCadenas_h
#define listaCadenas_h

#include <string>
using namespace std;

const int MAXCAD = 100;

//Lista de archivos donde esta cada palabra;
typedef struct{
	int tam;
	string datos[MAXCAD];
}tListaCadenas;

//Devuelve el tama�o de la lista.
int getTamanno(const tListaCadenas & l);
//Devuelve una cadena en la posici�n pos.
string getCadena(const tListaCadenas & l, int pos);
//Inserta un elemento al final de la lista
void insertar(tListaCadenas & l, const string & s);
//Devuelve true si la cadena est� en la lista, y false si no.
bool buscar(const tListaCadenas & l, const string & s);
//Elimina el elemento en la posici�n pos.
void eliminar(tListaCadenas & l, int pos);
//Imprime los elementos de la lista.
void imprimir(const tListaCadenas & l);
//Redefine el operador para imprimir por pantalla
ostream & operator <<(ostream & salida, const tListaCadenas & l);

#endif