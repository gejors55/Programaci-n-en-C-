#ifndef listaCadenas_h
#define listaCadenas_h

#include <string>
using namespace std;

const int MAXCAD = 100;

typedef string *tCadPtr;
typedef struct{
	tCadPtr datos;
	int tam;
	int capacidad;
	//string datos[MAXCAD];
}tListaCadenas;

//Devuelve el tamaño de la lista.
int getTamanno(const tListaCadenas & l);
//Devuelve una cadena en la posición pos.
string getCadena(const tListaCadenas & l, int pos);
//Inserta un elemento al final de la lista
void insertar(tListaCadenas & l, const string & s);
//Redimensiona el array
void resize(tListaCadenas & l);
//Devuelve true si la cadena está en la lista, y false si no.
bool buscar(const tListaCadenas & l, const string & s, int & pos);
//Elimina el elemento en la posición pos.
void eliminar(tListaCadenas & l, int pos);
//Imprime los elementos de la lista.
void imprimir(const tListaCadenas & l);
//Redefine el operador para imprimir por pantalla
ostream & operator <<(ostream & salida, const tListaCadenas & l);

#endif