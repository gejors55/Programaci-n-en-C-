#ifndef matriz_h
#define matriz_h

#include <vector>
#include <string>
#include <cmath>
using namespace std;

const int MAX_TAM = 10;
const double C = 0.85;
const double EPSILON = 0.00001;
typedef struct {
	int tam;
	double datos[MAX_TAM];
} tVector;

typedef struct{
	int filas, columnas;
	double datos[MAX_TAM][MAX_TAM];
} tMatriz;

//Crea una matriz de 𝑛 ∙ 𝑛, en la que todos los valores iniciales son x.
tMatriz matrizConstante(double x, int n);
//Multiplica una matriz por un vector.
tVector operator*(const tMatriz & m, const tVector & v);
//Obtiene la matriz que se obtiene multiplicando cada elemento de m por x.
tMatriz operator*(double x, const tMatriz & m);
//Suma dos matrices.
tMatriz operator+(const tMatriz & m1, const tMatriz & m2);
//Devuelve la matriz M obtenida de L como en la introducción de la sección 4.
tMatriz desdeEnlacesAMatriz(const tMatriz & L);
//Funcion auxiliar para la creacion de mPrima;
void trasformar(const tMatriz & L, tMatriz & mPrima, const int contador, double enlaces, const int fila);
//Devuelve un vector proporcional a v con la primera componente igual a 1.0.
tVector normaliza(const tVector & v);
//M es una matriz tal que todas sus columnas suman 1, devuelve un vector v con la primera componente igual a 1 tal que 𝑀 ∙ 𝑣 ≃ 𝑣.
tVector vectorPropio(const tMatriz & M);
//funcion auxiliar para ver si todas las componentes son menores que EPSILON
int vectoraux(const tVector &pr1, const tVector &pr2);
//Crea un vector con x valor y n tamaño
tVector crearVector(int x, int n);

//Pruebas para mostrar

//operador mostrar para matrices
ostream & operator <<(ostream & salida, const tMatriz & m);
//operador mostrar parra vectores
ostream & operator <<(ostream & salida, const tVector & v);

#endif