#include <iostream>
#include <string>
#include <fstream>

using namespace std;
const int MAX_PROD = 25;
const int CENTINELA = -1;
const int PROD_NULO = 0;

typedef int tArray[MAX_PROD];


//Dada una fila, la muestra en pantalla siguiendo el formato del final de la segunda página.
void mostrarFila(const tArray fila, int tam);
//Devuelve si la posición pos es válida en la fila de tamaño tam
bool esPosValida(int tam, int pos);
//Devuelve si la posición pos está vacía.
bool estaVacia(const tArray fila, int pos);
//Dado elfichero de lectura abierto fich, carga su contenido en la fila.
void leerFilaFich(istream &fich, tArray fila, int &tam);
//Dado el fichero de escritura abierto fich, guarda en dicho fichero el contenido de la fila.
void escribirFilaFich(ostream &fich, const tArray fila, int tam);
//Devuelve cierto si posIni y posSoltar son posiciones válidas de la fila y además es posible dejar caer el contenido de la fila
//situado en posIni en su posición posSoltar.
bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni, int posSoltar);
//Si es posible, realiza el movimiento de la grúa entre las posiciones posIni y posSoltar.Devuelve si el movimiento se ha realizado.
bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar);
//Devuelve la posición del primer hueco libre de la fila si, comenzando por posIni, vamos avanzando paso a paso hacia la derecha.
//Si no hay ninguno, devolverá el valor tam.
int posHuecoLibreDerecha(const tArray fila, int tam, int posIni);
//Devuelve la posición del primer hueco libre de la fila si, comenzando por posIni, vamos avanzando paso a paso hacia la Izquierda.
//Si no hay ninguno, devolverá el valor tam.
int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion);
//
bool excavadora1Derecha(tArray fila, int tam, int posIni);

//Muestra el menú de opciones, solicita al usuario su respuesta, y devuelve la opción escogida cuando el usuario haya
//respondido una opción válida.
int menu();
//
void ejecutarLeerFichero(tArray fila, int &tam);
//
void ejecutarGuardarFichero(const tArray fila, int tam);
//
void ejecutarGrua(tArray fila, int tam);
//
void ejecutarExcavadora(tArray fila, int tam);
//
void ejecutarOpc(int opc, tArray fila, int &tam);

int main(){
	int opcion = menu();
	tArray fila;
	int tam = 0;
	ejecutarOpc(opcion, fila, tam);
	system("pause");
	return 0;
}

int menu(){
	int op;
	cout << "1.- Cargar fila de fichero " << endl;
	cout << "2.- Guarda fila en fichero" << endl;
	cout << "3.- Usar grua (1 elemento)" << endl;
	cout << "4.- Usar excavadora (1 posicion derecha)" << endl;
	cout << "0. - Salir" << endl;
	cout << "Opcion: ";
	cin >> op;
	while (op < 0 || op > 4){
		cout << "Opcion incorrecta " << endl;
		cout << "Opcion: ";
		cin >> op;
	}
	return op;
}

void mostrarFila(const tArray fila, int tam){
	for (int i = 0; i < tam; i++){
		cout << "| " << fila[i];
	}
	cout << "|" << endl;
	for (int i = 0; i < tam; i++){
		cout << "---";
	}
	cout << "-" << endl;
	for (int i = 0; i < tam; i++){
		cout << "| " << i;
	}
	cout << "|" << endl;

}
bool esPosValida(int tam, int pos){
	bool ok;
	if (pos <0 && pos >= tam){
		ok = false;
	}
	else
		ok = true;

	return ok;
}
bool estaVacia(const tArray fila, int pos){
	bool ok;
	if (fila[pos] == 0)
		ok = true;
	else
		ok = false;

	return ok;
}
void leerFilaFich(istream &fich, tArray fila, int &tam){
	int i = 0;
	int num;
	fich >> num;
	while (i < MAX_PROD && num != CENTINELA){
		fila[i] = num;
		i++;
		fich >> num;
	}
	tam = i;
}

void escribirFilaFich(ostream &fich, const tArray fila, int tam){
	for (int i = 0; i < tam; i++){
		fich << fila[i] << " ";
	}
	fich << CENTINELA << endl;
}
bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni, int posSoltar){
	bool ok;
	if (esPosValida(tam, posIni) && esPosValida(tam, posSoltar)){
		if (!estaVacia(fila, posIni) && estaVacia(fila, posSoltar)){
			ok = true;
		}
		else{
			ok = false;
		}
	}
	else{
		ok = false;
	}

	return ok;
}

bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar){
	bool ok;
	if (esPosibleGrua1Entre(fila, tam, posIni, posSoltar)){
		fila[posSoltar] = fila[posIni];
		fila[posIni] = 0;
		ok = true;
	}
	else{
		ok = false;
	}
	return ok;
}

int posHuecoLibreDerecha(const tArray fila, int tam, int posIni){
	int hueco;
	int i = posIni;
	bool found = false;
	while (i < tam && !found){
		if (estaVacia(fila, i)){
			found = true;
			hueco = i;
		}
		else{
			i++;
		}
	}

	if (!found){
		hueco = tam;
	}

	return hueco;
}
/*int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion){
	int hueco;
	int i = posIni;
	bool found = false;
	while (i < tam && !found){
		if (estaVacia(fila, i)){
			found = true;
			hueco = i;
		}
		else{
			if (direccion == 1)
				i++;
			else if (direccion == -1)
				i--;
		}
	}

	if (!found){
		hueco = tam;
	}

	return hueco;
}*/


bool excavadora1Derecha(tArray fila, int tam, int posIni){
	bool ok;
	int hueco;
	if (esPosValida(tam, posIni)){
		hueco = posHuecoLibreDerecha(fila, tam, posIni);
		if (hueco != tam){
			for (int i = hueco; i > posIni; i--){
				fila[i] = fila[i - 1];
			}
			fila[posIni] = 0;
			ok = true;
		}
		else
			ok = false;
	}
	else{
		ok = false;
	}
	return ok;
}

/*bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion){
	bool ok;
	int hueco;
	if (esPosValida(tam, posIni)){
		hueco = posHuecoLibreDerecha(fila, tam, posIni);
		if (hueco != tam){
			if (direccion == 1){
				for (int i = hueco; i > posIni; i--){
					fila[i] = fila[i - 1];
				}
				fila[posIni] = 0;
				ok = true;
			}
			else if (direccion == -1){
				for (int i = hueco; i < posIni; i++){
					fila[i] = fila[i +1];
				}
				fila[posIni] = 0;
				ok = true;
			}
		}
		else
			ok = false;
	}
	else{
		ok = false;
	}
	return ok;

}*/

void ejecutarLeerFichero(tArray fila, int &tam){
	ifstream fich;
	string nombre;
	cout << "Introduce el fichero a cargar: ";
	cin >> nombre;
	fich.open(nombre);
	if (!fich.is_open())
		cout << "No se ha podido realizar la carga." << endl;
	else{
		leerFilaFich(fich, fila, tam);
		cout << "Se ha realizado la carga." << endl;
		mostrarFila( fila, tam);
	}

}

void ejecutarGuardarFichero(const tArray fila, int tam){
	ofstream fich;
	string nombre;
	cout << "Introduce el fichero a guardar: ";
	cin >> nombre;
	fich.open(nombre);
	if (!fich.is_open())
		cout << "No se ha podido abrir." << endl;
	else{
		escribirFilaFich(fich, fila, tam);
		cout << "Se ha realizado el guardado." << endl;
	}
}

void ejecutarGrua(tArray fila, int tam){
	int posicion, posCaer;
	cout << "Introduce la posicion que quieres levantar: ";
	cin >> posicion;
	cout << "Introduce la posicion en que quieres que caiga: ";
	cin >> posCaer;
	if (!grua1Elemento(fila, tam, posicion, posCaer)){
		cout << "El movimiento no fue posible." << endl;
	}
	mostrarFila(fila, tam);
}

void ejecutarExcavadora(tArray fila, int tam){
	int posicion;
	cout << "Desde que posicion quieres que empuje la escavadora: ";
	cin >> posicion;
	if (!excavadora1Derecha(fila, tam, posicion)){
		cout << "No fue posible realizar el movimiento." << endl;
	}
	mostrarFila(fila, tam);
}

void ejecutarOpc(int opc, tArray fila, int &tam){
	while (opc != 0){
		switch (opc){
		case 1:
			ejecutarLeerFichero(fila, tam);
			break;
		case 2:
			ejecutarGuardarFichero(fila, tam);
			break;
		case 3:
			ejecutarGrua(fila, tam);
			break;
		case 4:
			ejecutarExcavadora(fila, tam);
			break;
		default:
			break;
		}
		cout << endl;
		opc = menu();
	}
}