/*Alejandro Rodríguez Calzada y Jorge González Soria*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>

using namespace std;

//CONSTANTES
const int MAX = 50;
const int MAXH = 10;
const int MAXE = 100;

//Enum para el manejo de las teclas especiales
typedef enum tTecla{ Arriba, Abajo, Derecha, Izquierda, Salir, Nada, Deshacer };
//Enum para las casillas del tablero
typedef enum tCasilla { Libre, Muro, DestinoL, DestinoC, DestinoJ, Jugador, Caja };

//El tablero inicializado a MAX
typedef tCasilla tTablero[MAX][MAX];

//Struct que contine las variables para el control y manejo del tablero y el mismo.
typedef struct{
	tTablero tablero;
	int nfilas;
	int ncolumnas;
	int filaJ;
	int columnaJ;
	int cajas;
	int colocadas;
}tSokoban;

//Array de tableros para deshacer movimientos
typedef tSokoban tArrayS[MAXH];

//Struct para el manejo de deshacer movimientos, indice que dice donde esta, y cont que comprueba que no se hagan mas deshacer de los permitidos
typedef struct{
	tArrayS sokoban;
	int indice;
	int contador;
}tHistoria;

//Struct  que lleva todo el juego
typedef struct{
	tHistoria historia;
	tSokoban estado;
	int numMovimientos;
	string nfichero;
	int nivel;
}tJuego;

//Struct que guarda informacion de la partida actual
typedef struct{
	string fichero;
	int nivel;
	int numMov;
}tPartida;

//Array de partidas
typedef tPartida tExitos[MAXE];

//Struct para guardar y ver por cada jugador que niveles ha superado
typedef struct{
	string nombreUsu;
	tExitos exitos;
	int partidas; 
}tInfo;

//Añade color de fondo con la biblioteca windows.h
void colorFondo(int color);
//Menu que controla las opciones del juego
int menu();
//Dibuja una casilla del tablero con el color correspondiente
void dibujaCasilla(tCasilla casilla);
//Dibuja todo el tablero, casilla a casilla
void dibujar(const tJuego &juego);
//Inicializa el tablero
void inicializar(tJuego &juego);
//Inicializa las variables para el manejo del tablero
void inicializarContadores(tSokoban &estado);
//Carga desde archivo
bool cargarJuego(tJuego &juego);
//Carga cada nivel desde archivo al tablero
bool cargarNivel(ifstream &fichero, tSokoban &estado, int nivel);
//Transforma el caracter del archivo de texto a una casilla del tablero
tCasilla conversion(char ia, tSokoban &estado, int columna);
//Mete una linea del archivo de texto al tablero
void meterLinea(tSokoban &estado, string linea);
//Lee la tecla que has pulsado
tTecla leerTecla();
//LLeva el juego movimiento a movimiento del jugador
void hacerMovimiento(tJuego &juego, tTecla tecla);
//Coprueba que la casilla anterior era jugador o destinoJ para darle valor al quedar desocupada
void comprobarCasilla(tJuego &juego);
//Comprueba si el jugador ha ganado
bool ganador(tJuego &juego);
//Comprueba si el jugador tiene una caja bloqueada, sin movimientos
bool bloqueado(const tJuego &juego);
//Comprueba las diagonales de la caja para poder saber si esta bloqueada
bool diagonales(const tJuego &juego, int fila, int columna);
//Deshace el movimiento cargando desde Historia el tablero anterior
bool deshacerMovimiento(tJuego &juego);
//Guarda en la historia el tablero para poder deshacerlo si es preciso 
void guardar(tJuego &juego);
//Carga de fichero todas las partidas superadas por el jugador
bool cargar(tInfo &info);
//Opcion 2 del menu, muestra las partidas ganadas por el jugador
void mostrar(const tInfo info);
//Guarda la informacion de las partidas ganadas por el jugador
void guardarFich(const tInfo info);
//Operador que compara un juego con info y devuelve true si info contine ese nivel y ese fichero y false en caso contrario
bool& operator==(tJuego const &juego, tInfo  &info);
//Inserta en una lista ordenada la informacion de la partida superada por el jugador
void operator<(tJuego const &juego, tInfo  &info);

int main(){
	setlocale(LC_CTYPE, "Spanish"); //Pone acentos
	tJuego juego;
	tTecla tecla;
	tInfo info;
	cout << "Introduce tu nombre: ";
	cin >> info.nombreUsu;
	cout << "Bienvenido " << info.nombreUsu << endl;
	system("pause");
	info.partidas = 0;
	if (!cargar(info)){
		cout << "No se encuentra la información del jugador. Se creara nueva." << endl;
		system("pause");
	}
	system("cls");
	int opcion = menu();
	while (opcion != 0){
		bool ganar = false;
		switch (opcion){
		case 1:
			inicializar(juego);
			if (cargarJuego(juego)){
				system("cls");
				dibujar(juego);
				tecla = leerTecla();
				while (!ganar && tecla != Salir){
					hacerMovimiento(juego, tecla);
					system("cls");
					dibujar(juego);
					if (ganador(juego)){
						cout << "Enhorabuena has superado este nivel, "  <<info.nombreUsu << "!" << endl;
						ganar = true;
					}
					else if (bloqueado(juego)){
						cout << "Estas bloqueado, no hay mas movimientos, vuelve pronto! " << endl;
						tecla = leerTecla();
					}
					else
						tecla = leerTecla();
				}
				if (ganar){
					if (juego == info){} //No hago nada porque ya esta actualizado dentro.
					else{
						juego < info;
					}
					guardarFich(info);
					system("pause");
				}
				system("cls");
			}
			break;
		case 2:
			mostrar(info);
			break;
		default:
			break;
		}
		opcion = menu();
	}
	cout << "Hasta pronto " << info.nombreUsu << "!" << endl;
	system("pause");
	return 0;
}

int menu(){
	int op;
	cout << "1. Jugar partida." << endl;
	cout << "2. Mostrar partidas ganadas." << endl;
	cout << "0. Salir" << endl;
	cout << "Opción: ";
	cin >> op;
	while ((op < 0) || (op > 2)){
		cout << "Opción no válida. " << endl;
		cout << "Opción: ";
		cin >> op;
	}
	return op;
}

void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

void dibujaCasilla(tCasilla casilla){
	if (casilla == Libre){
		colorFondo(1);
		cout << "  ";
	}
	else if (casilla == Muro){
		colorFondo(2);
		cout << "  ";
	}
	else if (casilla == Jugador){
		colorFondo(6);
		cout << "00";
	}
	else if (casilla == Caja){
		colorFondo(7);
		cout << "()";
	}
	else if (casilla == DestinoL){
		colorFondo(5);
		cout << "..";
	}
	else if (casilla == DestinoC){
		colorFondo(4);
		cout << "[]";
	}
	else if (casilla == DestinoJ){
		colorFondo(4);
		cout << "00";
	}
}

void dibujar(const tJuego &juego){
	cout << "Fichero:  " << juego.nfichero << "  Nivel: " << juego.nivel << endl;
	for (int i = 0; i < juego.estado.nfilas; i++){
		for (int j = 0; j < juego.estado.ncolumnas; j++){
			dibujaCasilla(juego.estado.tablero[i][j]);
		}
		cout << endl;
	}
	colorFondo(0);
	cout << "Numero de movimientos:  " << juego.numMovimientos << endl;
}

void inicializar(tJuego &juego){
	for (int i = 0; i < MAX; i++){
		for (int j = 0; j < MAX; j++){
			juego.estado.tablero[i][j] = Libre;
		}
	}
	juego.numMovimientos = 0;
	juego.historia.indice = 0;
	juego.historia.contador = 0;
}

void inicializarContadores(tSokoban &estado){
	estado.cajas = 0;
	estado.colocadas = 0;
	estado.ncolumnas = 0;
	estado.nfilas = 0;
}

bool cargarJuego(tJuego &juego) {  ////RETURNS 
	cout << "Introduzca el fichero que quieres cargar: ";
	cin >> juego.nfichero;
	ifstream fichero;
	fichero.open(juego.nfichero);
	if (!fichero.is_open()){
		cout << "No se ha podido cargar el archivo." << endl;
		system("cls");
	}
	else{
		cout << "Introduzca el nivel: ";
		cin >> juego.nivel;
		return cargarNivel(fichero, juego.estado, juego.nivel);
	}
}

bool cargarNivel(ifstream &fichero, tSokoban &estado, int nivel){
	bool ok = false;
	int columnaMax = 0;
	string linea;
	string miNivel = "Level " + to_string(nivel);
	getline(fichero, linea);
	while (miNivel != linea && !fichero.eof()){
		getline(fichero, linea);
	}
	if (miNivel == linea)
		ok = true;
	if (ok){
		inicializarContadores(estado);
		getline(fichero, linea);
		while (linea != ""){
			estado.ncolumnas = linea.size();
			meterLinea(estado, linea);
			getline(fichero, linea);
			estado.nfilas++;
			if (columnaMax < estado.ncolumnas)
				columnaMax = estado.ncolumnas;
		}
		estado.ncolumnas = columnaMax;
	}
	else{
		cout << "No se ha podido cargar el nivel." << endl;
		system("cls");
	}
	return ok;
}

void meterLinea(tSokoban &estado, string linea){
	for (int i = 0; i < estado.ncolumnas; i++){
		estado.tablero[estado.nfilas][i] = conversion(linea[i], estado, i);
	}
}

tCasilla conversion(char ia, tSokoban &estado, int columna){ 
	tCasilla casilla;
	if (ia == '#'){
		casilla = Muro;
	}
	else if (ia == ' '){
		casilla = Libre;
	}
	else if (ia == '$'){
		casilla = Caja;
		estado.cajas++;
	}
	else if (ia == '@'){
		casilla = Jugador;
		estado.filaJ = estado.nfilas;
		estado.columnaJ = columna;
	}
	else if (ia == '.'){
		casilla = DestinoL;
	}
	else if (ia == '+'){
		casilla = DestinoJ;
		estado.filaJ = estado.nfilas;
		estado.columnaJ = columna;
	}
	else if (ia == '*'){
		casilla = DestinoC;
		estado.cajas++;
		estado.colocadas++;
	}
	return casilla;
}

tTecla leerTecla(){
	tTecla tecla;
	int dir;
	cin.sync();
	dir = _getch();
	if (dir == 0xe0) {
		dir = _getch();
		switch (dir)
		{
		case 72: tecla = Arriba; break;
		case 80: tecla = Abajo; break;
		case 77: tecla = Derecha; break;
		case 75: tecla = Izquierda; break;
		}
	}
	else if (dir == 68 || dir == 100){
		tecla = Deshacer;
	}
	else if (dir == 27){
		tecla = Salir;
	}
	else{
		tecla = Nada;
	}
	return tecla;
}

void hacerMovimiento(tJuego &juego, tTecla tecla){
	int fDestino, cDestino;
	int cajaDestinoF, cajaDestinoC;
	bool mov = true;
	switch (tecla){
	case Arriba: fDestino = juego.estado.filaJ - 1; cDestino = juego.estado.columnaJ; break;
	case Abajo: fDestino = juego.estado.filaJ + 1; cDestino = juego.estado.columnaJ; break;
	case Derecha: fDestino = juego.estado.filaJ; cDestino = juego.estado.columnaJ + 1; break;
	case Izquierda:fDestino = juego.estado.filaJ; cDestino = juego.estado.columnaJ - 1; break;
	case Deshacer: mov = false; 
		if (!deshacerMovimiento(juego))
			cout << "No se puede deshacer" << endl;
		else{
			if (juego.historia.contador != 0)
				juego.historia.contador--;
		}
		break;
	case Nada: mov = false;
	}
	if (mov){
		guardar(juego);
		switch (juego.estado.tablero[fDestino][cDestino]){
		case Libre: juego.estado.tablero[fDestino][cDestino] = Jugador;
			comprobarCasilla(juego);
			break;
		case Muro: mov = false;
			break;
		case DestinoL:juego.estado.tablero[fDestino][cDestino] = DestinoJ;
			comprobarCasilla(juego);
			break;
		case Caja: 
			switch (tecla){
			case Arriba: cajaDestinoF = fDestino - 1;  cajaDestinoC = cDestino; break;
			case Abajo: cajaDestinoF = fDestino + 1;  cajaDestinoC = cDestino; break;
			case Derecha: cajaDestinoF = fDestino;  cajaDestinoC = cDestino + 1; break;
			case Izquierda:cajaDestinoF = fDestino; cajaDestinoC = cDestino - 1; break;
			}
			if (juego.estado.tablero[cajaDestinoF][cajaDestinoC] == Libre){
				juego.estado.tablero[cajaDestinoF][cajaDestinoC] = Caja;
				juego.estado.tablero[fDestino][cDestino] = Jugador;
				comprobarCasilla(juego);
			}
			else if (juego.estado.tablero[cajaDestinoF][cajaDestinoC] == DestinoL){
				juego.estado.tablero[cajaDestinoF][cajaDestinoC] = DestinoC;
				juego.estado.tablero[fDestino][cDestino] = Jugador;
				comprobarCasilla(juego);
				juego.estado.colocadas++;
			}
			else{
				mov = false;
			}
			break;
		case DestinoC:
			switch (tecla){
			case Arriba: cajaDestinoF = fDestino - 1;  cajaDestinoC = cDestino; break;
			case Abajo: cajaDestinoF = fDestino + 1;  cajaDestinoC = cDestino; break;
			case Derecha: cajaDestinoF = fDestino;  cajaDestinoC = cDestino + 1; break;
			case Izquierda:cajaDestinoF = fDestino; cajaDestinoC = cDestino - 1; break;
			}
			if (juego.estado.tablero[cajaDestinoF][cajaDestinoC] == Libre){
				juego.estado.tablero[cajaDestinoF][cajaDestinoC] = Caja;
				juego.estado.tablero[fDestino][cDestino] = DestinoJ;
				comprobarCasilla(juego);
				juego.estado.colocadas--;
			}
			else if (juego.estado.tablero[cajaDestinoF][cajaDestinoC] == DestinoL){
				juego.estado.tablero[cajaDestinoF][cajaDestinoC] = DestinoC;
				juego.estado.tablero[fDestino][cDestino] = DestinoJ;
				comprobarCasilla(juego);
			}
			else{
				mov = false;
			}
			break;
		}	
	}
	if (mov){
		juego.numMovimientos++;
		if (juego.historia.contador != MAXH){
			juego.historia.contador++;
		}
		switch (tecla){
		case Arriba: juego.estado.filaJ = fDestino; break;
		case Abajo: juego.estado.filaJ = fDestino;  break;
		case Derecha:juego.estado.columnaJ = cDestino; break;
		case Izquierda:juego.estado.columnaJ = cDestino; break;
		}
	}
}
void guardar(tJuego &juego){
	for (int i = 0; i < juego.estado.nfilas; i++){
		for (int j = 0; j < juego.estado.ncolumnas; j++){
			juego.historia.sokoban[juego.historia.indice].tablero[i][j] = juego.estado.tablero[i][j];
		}
	}
	juego.historia.sokoban[juego.historia.indice].nfilas = juego.estado.nfilas;
	juego.historia.sokoban[juego.historia.indice].ncolumnas = juego.estado.ncolumnas;
	juego.historia.sokoban[juego.historia.indice].filaJ = juego.estado.filaJ;
	juego.historia.sokoban[juego.historia.indice].columnaJ = juego.estado.columnaJ;
	juego.historia.sokoban[juego.historia.indice].colocadas = juego.estado.colocadas;
	juego.historia.sokoban[juego.historia.indice].cajas= juego.estado.cajas;
	juego.historia.indice = (juego.historia.indice + 1) % MAXH;
}

void comprobarCasilla(tJuego &juego){
	if (juego.estado.tablero[juego.estado.filaJ][juego.estado.columnaJ] == Jugador)
		juego.estado.tablero[juego.estado.filaJ][juego.estado.columnaJ] = Libre;
	else if (juego.estado.tablero[juego.estado.filaJ][juego.estado.columnaJ] == DestinoJ)
		juego.estado.tablero[juego.estado.filaJ][juego.estado.columnaJ] = DestinoL;
}

bool ganador(tJuego &juego){
	return (juego.estado.cajas == juego.estado.colocadas);
}

bool bloqueado(const tJuego &juego){
	bool ok = false;
	for (int i = 0; !ok && i < juego.estado.nfilas; i++){
		for (int j = 0; !ok && j < juego.estado.ncolumnas; j++){
			if (juego.estado.tablero[i][j] == Caja){
				ok = diagonales(juego, i, j);
			}
		}
	}
	return ok;
}

bool diagonales(const tJuego &juego, int fila, int columna){
	bool ok = false;
	if (juego.estado.tablero[fila][columna - 1] == Muro && juego.estado.tablero[fila + 1][columna] == Muro){ //Inf izq
		ok = true;
	}
	else if (juego.estado.tablero[fila - 1][columna] == Muro && juego.estado.tablero[fila][columna + 1] == Muro){//Sup der
		ok = true;
	}
	else if (juego.estado.tablero[fila + 1][columna] == Muro && juego.estado.tablero[fila][columna + 1] == Muro){//Inf der
		ok = true;
	}
	else if (juego.estado.tablero[fila - 1][columna] == Muro && juego.estado.tablero[fila][columna - 1] == Muro){//Sup izq
		ok = true;
	}
	return ok;
}

bool deshacerMovimiento(tJuego &juego){
	bool deshecho;
	if (juego.historia.contador == 0)
		deshecho = false;
	else{
		juego.historia.indice = (juego.historia.indice + 9) % MAXH;
		for (int i = 0; i < juego.estado.nfilas; i++){
			for (int j = 0; j < juego.estado.ncolumnas; j++){
				juego.estado.tablero[i][j] = juego.historia.sokoban[juego.historia.indice].tablero[i][j];
			}
		}
		juego.estado.nfilas = juego.historia.sokoban[juego.historia.indice].nfilas;
		juego.estado.ncolumnas = juego.historia.sokoban[juego.historia.indice ].ncolumnas;
		juego.estado.filaJ = juego.historia.sokoban[juego.historia.indice ].filaJ;
		juego.estado.columnaJ = juego.historia.sokoban[juego.historia.indice].columnaJ;
		juego.estado.colocadas = juego.historia.sokoban[juego.historia.indice].colocadas;
		juego.estado.cajas = juego.historia.sokoban[juego.historia.indice].cajas;
		juego.numMovimientos--;
		deshecho = true;
	}
	return deshecho;
}

bool cargar(tInfo &info){
	ifstream fichero;
	string linea;
	bool ok;
	fichero.open(info.nombreUsu +".txt");
	if (!fichero.is_open()){
		ok = false;
	}
	else{
		ok = true;
		fichero >> linea;
		while (linea !="" && !fichero.eof()){
			info.exitos[info.partidas].fichero = linea;
			fichero >> info.exitos[info.partidas].nivel;
			fichero >> info.exitos[info.partidas].numMov;
			info.partidas++;
			fichero >> linea;
		}
	}
	return ok;
}

void mostrar(const tInfo info){
	cout << "  Tableros derrotados por " << info.nombreUsu << endl;
	cout << "Fichero" << setw(18) << " Nivel" << setw(18) << " Movimientos" << endl;
	for (int i = 0; i < info.partidas; i++){
		cout << info.exitos[i].fichero << setw(8) << info.exitos[i].nivel << setw(18) << info.exitos[i].numMov << endl;
	}
	system("pause");
	system("cls");
}

void guardarFich(const tInfo info){
	ofstream archivo;
	archivo.open(info.nombreUsu + ".txt");
	for (int i = 0; i < info.partidas; i++){
		archivo << info.exitos[i].fichero << " " << info.exitos[i].nivel << " " << info.exitos[i].numMov << endl;
	}
}

bool& operator==(tJuego const &juego, tInfo &info){
	int i = 0;
	bool ok = false;
	while (!ok && i <info.partidas){
		if (juego.nfichero == info.exitos[i].fichero && juego.nivel == info.exitos[i].nivel){
			ok = true;
			if (juego.numMovimientos < info.exitos[i].numMov)
				info.exitos[i].numMov = juego.numMovimientos;
		}
		i++;
	}
	return ok;
}

void operator<(tJuego const &juego, tInfo &info){
	int pos = 0;
	while ((pos < info.partidas) && juego.nfichero > info.exitos[pos].fichero){
		pos++;
	}
	if (juego.nfichero == info.exitos[pos].fichero){
		while ((pos < info.partidas) && juego.nivel > info.exitos[pos].nivel){
			pos++;
		}
	}
	for (int i = pos; i < info.partidas; i++){
		info.exitos[i+1].fichero = info.exitos[i].fichero;
		info.exitos[i+1].nivel = info.exitos[i].nivel;
		info.exitos[i+1].numMov = info.exitos[i].numMov;
	}

	info.exitos[pos].fichero = juego.nfichero;
	info.exitos[pos].nivel = juego.nivel;
	info.exitos[pos].numMov = juego.numMovimientos;
	info.partidas++;
}
