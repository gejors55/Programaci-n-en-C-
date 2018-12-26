#include <iostream>
using namespace std;

#include "matriz.h"

tMatriz matrizConstante(double x, int n){
	tMatriz m;
	m.filas = n;
	m.columnas = n;
	for (int i = 0; i < m.filas; i++){
		for (int j = 0; j < m.columnas; j++){
			m.datos[i][j] = x;
		}
	}
	return m;
}

tVector operator*(const tMatriz & m, const tVector & v){
	tVector vector;
	double numero = 0;
	vector.tam = v.tam;
	for (int i= 0; i < m.filas; i++){
		for (int j = 0; j < vector.tam; j++){
			numero += m.datos[i][j] * v.datos[j];
		}
		vector.datos[i] = numero;
		numero = 0;
	}
	return vector;
}

tMatriz operator*(double x, const tMatriz & m){
	tMatriz matriz;
	matriz.filas = m.filas;
	matriz.columnas = m.columnas;
	for (int i = 0; i < m.filas; i++){
		for (int j = 0; j < m.columnas; j++){
			matriz.datos[i][j] = m.datos[i][j] * x;
		}
	}
	return matriz;
}

tMatriz operator+(const tMatriz & m1, const tMatriz & m2){
	tMatriz matriz;
	matriz.filas = m1.filas;
	matriz.columnas = m1.columnas;
	for (int i = 0; i < m1.filas; i++){
		for (int j = 0; j < m1.columnas; j++){
			matriz.datos[i][j] = m1.datos[i][j] + m2.datos[i][j];
		}
	}
	return matriz;
}

tMatriz desdeEnlacesAMatriz(const tMatriz & L){
	double enlaces = 1.0 / (L.filas);
	int contador = 0 ;
	double indi;
	tMatriz M;
	tMatriz Cn = matrizConstante(enlaces, L.filas);
	tMatriz mPrima = matrizConstante(0, L.filas);
	for (int i = 0; i < L.columnas; i++){
		contador = 0;
		for (int j = 0; j < L.filas; j++){
			if (L.datos[j][i] == 1){
				contador++;
			}
			if (j == L.filas - 1){
				trasformar(L, mPrima, contador, enlaces, i);
			}
		}
	}
	indi = 1 - C;
	Cn = indi * Cn;//(1-C) * Cn 
	mPrima = C * mPrima;//Mprima * C
	M = Cn + mPrima;
	return M;
}

void trasformar(const tMatriz & L, tMatriz & mPrima, const int contador, double enlaces,  const int fila){
	if (contador == 0){
		for (int i = 0; i < L.filas; i++){
			mPrima.datos[i][fila] = enlaces;
		}
	}
	else{
		for (int i = 0; i < L.filas; i++){
			if (L.datos[i][fila] == 1){
				mPrima.datos[i][fila] = 1.0 / contador;
			}
		}
	}
}

tVector normaliza(const tVector & v){
	tVector vectorUnitario;
	vectorUnitario.tam = v.tam;
	for (int i = 0; i < v.tam; i++){
		vectorUnitario.datos[i] = v.datos[i] / v.datos[0];
	}
	return vectorUnitario;
}

tVector vectorPropio(const tMatriz & M){
	bool parar = false;
	int cont = 0;
	tVector pr = crearVector(1, M.filas);			// vector de unos
	tVector pr1 = M * pr;				//pr1
	tVector pr2 = M* pr1;				//m*pr1
	while (!parar){
		cont = vectoraux(pr1, pr2);
		if (cont == pr1.tam){				//si m*pr1 esta proximo a pr1 | la diferencia entre los cocientes sea menor que 10 e-5 
			parar = true;
		}
		else{					//repetimos pr2 = m*pr1
			pr1 = pr2;
			pr2 = M * pr1;
		}

	}
	return normaliza(pr1);
}

int vectoraux(const tVector &pr1, const tVector &pr2){
	int cont = 0;
	while (cont < pr1.tam &&  abs(1 - (pr1.datos[cont] / pr2.datos[cont])) < EPSILON){
		cont++;
	}
	return cont;
}

tVector crearVector(int x, int n){
	tVector vector;
	vector.tam = n;
	for (int i = 0; i < vector.tam; i++){
		vector.datos[i] = x;
	}
	return vector;
}

// Pruebas para Mostrar
ostream & operator <<(ostream & salida, const tMatriz & m){
	for (int i = 0; i <m.filas; i++){
		for (int j = 0; j < m.columnas; j++){
			salida << m.datos[i][j] << " ";
			if (j == m.columnas - 1){
				salida << endl;
			}
		}
	}
	return salida;
}

ostream & operator <<(ostream & salida, const tVector & v){
	for (int i = 0; i < v.tam; i++){
		salida << v.datos[i];
		if (i != v.tam - 1){
			salida << ", ";
		}
	}
	salida << endl;
	return salida;
}
