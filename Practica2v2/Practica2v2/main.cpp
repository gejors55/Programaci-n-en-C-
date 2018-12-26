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
//Devuelve la posición del primer hueco libre de la fila si, comenzando por posIni, vamos avanzando paso a paso hacia la Izquierda.
//Si no hay ninguno, devolverá el valor tam.
int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion);
//
bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion);
//Muestra el menú de opciones, solicita al usuario su respuesta, y devuelve la opción escogida cuando el usuario haya
//respondido una opción válida.
int menu();
//
void ejecutarLeerFichero(tArray fila, int &tam);
//
void ejecutarGuardarFichero(const tArray fila, int tam);
//
bool ejecutarGrua(tArray fila, int tam);
//
bool ejecutarExcavadora(tArray fila, int tam);
//
void ejecutarOpc(int opc, tArray fila, int &tam);

bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar);
void inicializar(tArray fila, tArray array, int posIni, int posFin);

bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar);
void soltar(tArray fila, tArray aux, int posSoltar, int posIni, int posFin);

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
	cout << "3.- Usar grua " << endl;
	cout << "4.- Usar excavadora " << endl;
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

bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar){
	bool ok = true;
	int i = 0;
	int iFinal = posIni - posFin;
	while (i <= iFinal && ok){
		if (estaVacia(fila, posIni + i) && !estaVacia(fila, posSoltar + i)){
			ok = true;
		}
		else if (!estaVacia(fila, posIni + i) && estaVacia(fila, posSoltar + i)){
			ok = true;
		}
		else if (estaVacia(fila, posIni + i) && estaVacia(fila, posSoltar + i)){
			ok = true;
		}
		else{
			ok = false;
		}
		i++;
	}
	return ok;
}

bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar){
	bool ok;
	int posFinSoltar = posFin - posIni + posSoltar;
	if ((posIni > posFin) && (esPosValida(tam, posIni)) && (esPosValida(tam, posFin)) && (esPosValida(tam, posSoltar)) && (esPosValida(tam, posFinSoltar))){
		ok = false;
	}
	else
		ok = true;

	return ok;
}

/*bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar){
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
}*/
void inicializar(tArray fila, tArray array, int posIni, int posFin){
	int posiciones = posFin - posIni;
	for (int i = 0; i <= posiciones; i++){
		array[i]= fila[posIni + i] ;
		fila[posIni + i] = 0;
	}
}

void soltar(tArray fila, tArray aux, int posSoltar, int posIni, int posFin){
	int posiciones = posFin - posIni;
	for (int i = 0; i <= posiciones; i++){
		if (!estaVacia(aux, i)){
			fila[posSoltar + i] = aux[i];
		}
	}
}

bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar){
	bool ok;
	tArray aux;
	if (!sonPosicionesPosiblesGrua(tam, posIni, posFin, posSoltar)){
		ok = false;
	}
	else{
		inicializar(fila, aux, posIni, posFin);
		soltar(fila, aux, posSoltar, posIni, posFin);
		ok = true;
	}
	return ok;
}

int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion){
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
}

bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion){
	bool ok;
	int hueco;
	hueco = posHuecoLibreDir(fila, tam, posIni, direccion);
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
				fila[i] = fila[i + 1];
			}
			fila[posIni] = 0;
			ok = true;
		}
	}
	else
		ok = false;
	return ok;

}
bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion){
	int i = 0;
	bool ok,found = true;
	if (esPosValida(tam, posIni)){
		ok = true;
		while (found && i < numDespla ){ // -1
			if (!excavadora1Dir(fila, tam, posIni, direccion)){
				found = false;
			}
			if (direccion == 1)
				posIni += 1;
			else if (direccion == -1)
				posIni -= 1;
			i++;
		}
	}
	else
		ok = false;

	return ok;
}

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
		mostrarFila(fila, tam);
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

bool ejecutarGrua(tArray fila, int tam){
	bool ejecutado = true;
	int posicion,posFin, posCaer;
	cout << "Introduce la posicion desde la quieres levantar y a continuacion hasta la que quieres levantar: ";
	cin >> posicion;
	cin >> posFin;
	cout << "Introduce la posicion en que quieres que caiga: ";
	cin >> posCaer;
	if (!grua(fila,tam,posicion,posFin,posCaer)){
		cout << "El movimiento no fue posible." << endl;
		ejecutado = false;
	}
	mostrarFila(fila, tam);
	return ejecutado;
}

bool ejecutarExcavadora(tArray fila, int tam){
	bool ejecutados = true;
	int posicion, numDespla;
	string dir;
	cout << "Desde que posicion quieres que empuje la escavadora: ";
	cin >> posicion;
	cout << " Cuantas posiciones quieres que se desplace: ";
	cin >> numDespla;
	cout << "En que direccion quieres que se desplace(der o izq) ";
	cin >> dir;
	if (dir == "der"){
		if (!excavadora(fila, tam, posicion, numDespla, 1)){
			cout << "No fue posible realizar el movimiento." << endl;
			ejecutados = false;
		}
	}
	else if (dir == "izq"){
		if (!excavadora(fila, tam, posicion, numDespla, -1)){
			cout << "No fue posible realizar el movimiento." << endl;
			ejecutados = false;
		}
	}
	mostrarFila(fila, tam);
	return ejecutados;
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




