/* Alejandro Rodríguez Calzada y Jorge González Soria*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
const int MAX_PROD = 25;
const int CENTINELA = -1;
const int PROD_NULO = 0;

typedef int tArray[MAX_PROD];

//Muestra el menú de opciones, solicita al usuario su respuesta, y devuelve la opción escogida cuando el usuario haya
//respondido una opción válida.
int menu();
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
bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar);
//Devuelve si el segmento a levantar no tiene su extremo derecho antes que el izquierdo y si todas las posiciones involucradas son
//válidas en la fila de tamaño tam.Fíjate en que, para comprobar lo segundo, te basta con comprobarlo para los cuatro extremos involucrados.
bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar);
//Funcion auxiliar que copia los elementos que hay que trasladar con la grua en un array
void inicializar(tArray fila, tArray array, int posIni, int posFin);
//Funcion auxiliar que pone los elementos del array auxiliar en el array principal si es posible.
void soltar(tArray fila, tArray aux, int posSoltar, int posIni, int posFin);
//Funcion principal de la Grua que maneja todo su funcionamiento.
bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar);
//Devuelve la posición del primer hueco libre de la fila si, comenzando por posIni, vamos avanzando paso a paso hacia la Izquierda.
//Si no hay ninguno, devolverá el valor tam.
int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion);
//Devuelve cierto si ha sido posible mover una posicion el elemento seleccionado hacia la direccion seleccionada
bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion);
//Funcion principal de la Excavadora que maneja todo su funcionamiento.
bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion);
//Opcion del menu que lee el fichero
bool ejecutarLeerFichero(tArray fila, int &tam);
//Opcion del menu que guarda el array en un fichero
void ejecutarGuardarFichero(const tArray fila, int tam);
//Opcion del menu que maneja la grua
bool ejecutarGrua(tArray fila, int tam);
//Opcion del menu que maneja la excavadora
bool ejecutarExcavadora(tArray fila, int tam);
//Funcion que dependiendo de la opcion que ha elegido el usuario, la ejecuta.
void ejecutarOpc(int opc, tArray fila, int &tam, int &contarJugadas);
//Devuelve cierto si el array esta ordenado, sin importar los huecos en blanco.
bool filaOrdenada(const tArray fila, int tam);



int main(){
	int contarJugadas = 0;
	int opcion = menu();
	tArray fila;
	int tam = 0;
	ejecutarOpc(opcion, fila, tam, contarJugadas);
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

//Cuando esta vacia muesta el inicio para ver que esta vacio.
void mostrarFila(const tArray fila, int tam){
	for (int i = 0; i < tam; i++){
		if (fila[i] != 0){
			cout << "|" << setw(2) <<  fila[i];
		}
		else
			cout << "|" << setw(3);
	}
	cout << "|" << endl;     
	for (int i = 0; i < tam; i++){
		cout << "---";
	}
	cout << "-" << endl;
	for (int i = 0; i < tam; i++){
		if (i < 10){
			cout << "|" << setw(2) << i;
		}
		else
			cout << "|" << setw(1) << i;
	}
	cout << "|" << endl;

}

bool esPosValida(int tam, int pos){
	bool ok;
	if (pos <0 || pos >= tam){
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

//Comprueba los posibles errores
bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar){
	bool ok = true;
	int i = 0;
	int iFinal = posFin - posIni;
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

//Comprueba errores de la grua al escribirlos el usuario.
bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar){
	bool ok;
	int posFinSoltar = posFin - posIni + posSoltar;
	if ((posIni > posFin) || (!esPosValida(tam, posIni)) || (!esPosValida(tam, posFin)) || (!esPosValida(tam, posSoltar)) || (!esPosValida(tam, posFinSoltar))){
		ok = false;
	}
	else
		ok = true;

	return ok;
}

void inicializar(tArray fila, tArray array, int posIni, int posFin){
	int posiciones = posFin - posIni;
	for (int i = 0; i <= posiciones; i++){
		array[i] = fila[posIni + i];
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
	else if (!esPosibleGrua(fila, tam, posIni, posFin, posSoltar)){
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
	while (i >= 0 && i < tam && !found){
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
	if (hueco < tam ){
		if (direccion == 1){
			//En la versión 3 no hacen falta en realidad, solo hacen falta cuando moviamos un elemento muchas posiciones.
			for (int i = hueco; i > posIni; i--){
				fila[i] = fila[i - 1];
			}
			fila[posIni] = 0;
			ok = true;
		}
		else if (direccion == -1){
			//En la versión 3 no hacen falta en realidad, solo hacen falta cuando moviamos un elemento muchas posiciones.
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
	bool ok, found = true;
	if (esPosValida(tam, posIni)){
		ok = true;
		while (found && i < numDespla){ // -1
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

bool ejecutarLeerFichero(tArray fila, int &tam){
	bool ok;
	ifstream fich;
	string nombre;
	cout << "Introduce el fichero a cargar: ";
	cin >> nombre;
	fich.open(nombre);
	if (!fich.is_open()){
		cout << "No se ha podido realizar la carga." << endl;
		ok = false;
	}
	else{
		leerFilaFich(fich, fila, tam);
		cout << "Se ha realizado la carga." << endl;
		mostrarFila(fila, tam);
		ok = true;
	}
	return ok;
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
		mostrarFila(fila, tam);
	}
}

bool ejecutarGrua(tArray fila, int tam){
	bool ejecutado = true;
	int posicion, posFin, posCaer;
	cout << "Introduce la posicion desde la quieres levantar y a continuacion hasta la que quieres levantar: ";
	cin >> posicion;
	cin >> posFin;
	cout << "Introduce la posicion en que quieres que caiga: ";
	cin >> posCaer;
	if (!grua(fila, tam, posicion, posFin, posCaer)){
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
	cout << "Cuantas posiciones quieres que se desplace: ";
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

void ejecutarOpc(int opc, tArray fila, int &tam, int &contarJugadas){
	while (opc != 0){
		switch (opc){
		case 1:
			if (ejecutarLeerFichero(fila, tam)){
				contarJugadas = 0;
				cout << "El contador de jugadas se ha puesto a 0." << endl;
			}
			break;
		case 2:
			ejecutarGuardarFichero(fila, tam);
			break;
		case 3:
			if (ejecutarGrua(fila, tam)){
				contarJugadas++;
				if (filaOrdenada(fila, tam)){
					cout << endl;
					cout << "La fila esta ordenada. " << endl;
				}
				else{
					cout << endl;
					cout << "La fila NO esta ordenada. " << endl;
				}
				cout << "El numero de jugadas es: " << contarJugadas << endl;
			}
			else{

			}
			
			break;
		case 4:
			if (ejecutarExcavadora(fila, tam)){
				contarJugadas++;
				if (filaOrdenada(fila, tam)){
					cout << endl;
					cout << "La fila esta ordenada. " << endl;
				}
				else{
					cout << endl;
					cout << "La fila NO esta ordenada. " << endl;
				}
				cout << "El numero de jugadas es: " << contarJugadas << endl;
			}
			
			break;
		default:
			break;
		}
		cout << endl;
		opc = menu();
	}
}

bool filaOrdenada(const tArray fila, int tam){
	int i = 0, valor = 0;
	bool ordenado = true;
	while ((i < tam) && ordenado){
		if (!estaVacia(fila, i)){
			if (valor < fila[i]){
				valor = fila[i];
			}
			else{
				ordenado = false;
			}
		}
		i++;
	}
	return ordenado;
}




