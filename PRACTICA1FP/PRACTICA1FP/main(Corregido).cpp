/*Alejandro Rodríguez Calzada y Jorge González Soria*/


#include <iostream>
#include <string>
#include <iomanip>
#include <locale.h>
#include <fstream>

using namespace std;


int menu();
int solicitaAnyo();
int solicitaMes();
int solicitaDia(int mes, int anyo);
long int diasTranscurridos(int dia, int mes, int anyo);
long int diasAnyosCompletos(int anyo);
int diasEsteAnyo(int dia, int mes, int anyo);
int contarBisiestos(int anyoInicio, int anyoFinal);
int diasMes(int mes, int anyo);
bool esBisiesto(int anyo);
int diaSemana(long int numDias);
string nombreDia(int representacionDia);
string diaDeLaSemana(int dia, int mes, int anyo);
int primerDomingoMes(int mes, int anyo);
int domingosAnyo(int anyo);
bool puentes();
string obtenerMes(int mes);
bool finMes(int mes, int anyo, int domingo);
bool puentesMejorado();


int main()
{
	setlocale(LC_CTYPE, "Spanish"); // pone acentos

	string nombre;
	bool ok;
	int anyo, mes, dia, numDias, representacionDia,dias2,numDomingos;
	int opcion = menu();
	while (opcion != 0){
		switch (opcion)
		{
		case 1:
			anyo = solicitaAnyo();
			mes = solicitaMes();
			dia = solicitaDia(mes, anyo);
			numDias = diasTranscurridos(dia, mes, anyo);
			representacionDia = diaSemana(numDias);
			nombre = nombreDia(representacionDia);
			cout << "El día " << dia << " de " << mes << " de " << anyo << " era " << nombre << endl;
			break;
		case 2:
			anyo = solicitaAnyo();
			dias2 = primerDomingoMes(1, anyo);
			cout << "El primer domingo del año " << anyo << " es el día: " << dias2 << " de enero" << endl;
			break;
		case 3:
			anyo = solicitaAnyo();
			numDomingos = domingosAnyo(anyo);
			cout << " Numero total de domingos: " << numDomingos << endl;
			break;
		case 4:						///QUE TIENE QUE MOSTRAR?????
			ok = puentes();
			if (ok)
				cout << "Se realizó " << endl;
			else
				cout << "No se pudo realizar " << endl;
			break;
		case 5:
			ok = puentesMejorado();
			if (ok)
				cout << "Se realizó " << endl;
			else
				cout << "No se pudo realizar " << endl;
			break;
		default:
			break;
		}
		cout << endl;
		opcion = menu();
	}


	system("pause");

	return 0;
}
int menu(){
	int op;
	cout << "1 – Calcular el día de la semana para una fecha dada" << endl;
	cout << "2 – Obtener la fecha correspondiente al primer domingo de un año" << endl;
	cout << "3 – Obtener los domingos de un año" << endl;
	cout << "4 – Obtener los posibles puentes de un año " << endl;
	cout << "5 - Obtener los posibles puentes de un año “mejorado”" << endl;
	cout << "0 - Salir" << endl;
	cout << "Opción: ";
	cin >> op;
	while ((op < 0) || (op > 5)){
		cout << "¡Opción no válida! " << endl;
		cout << "Opción: ";
		cin >> op;
	}
	return op;
}
int solicitaAnyo()
{
	int anyo;
	cout << "Inserte el año: ";
	cin >> anyo;
	while (anyo < 1900)
	{
		cout << "Introduzca un año válido: ";
		cin >> anyo;
	}
	return anyo;
}
int solicitaMes()
{
	int mes;
	cout << "Inserte el mes: ";
	cin >> mes;
	while ((mes > 12) || (mes < 1))
	{
		cout << "Introduzca un mes válido: ";
		cin >> mes;
	}
	return mes;
}
int solicitaDia(int mes, int anyo) 
{
	int dia;
	cout << "Inserte el dia: ";
	cin >> dia;

	if (mes == 2)
	{
		if (esBisiesto(anyo) == true){
			while (dia > 29){
				cout << "Día no válido para el mes solicitado, introduzca otro: ";
				cin >> dia;
			}
		}
		else{
			while (dia > 28){
				cout << "Día no válido para el mes solicitado, introduzca otro: ";
				cin >> dia;
			}
		}
	}
	else if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
	{
		while (dia > 31)
		{
			cout << "Día no válido para el mes solicitado, introduzca otro: ";
			cin >> dia;
		}
	}
	else
		while (dia > 30)
		{
			cout << "Día no válido para el mes solicitado, introduzca otro : ";
			cin >> dia;
		}
	return dia;
}
long int diasTranscurridos(int dia, int mes, int anyo)  
{
	return diasAnyosCompletos(anyo) + diasEsteAnyo(dia, mes, anyo);

}

long int diasAnyosCompletos(int anyo){
	int numero = contarBisiestos(1900, anyo);
	int totalAnyos = anyo - 1900;
	int total = numero + (totalAnyos * 365);
	return total;
}
int diasEsteAnyo(int dia, int mes, int anyo){ 
	int total = 0;
	int dias;
	for (int i = 1; i < mes; i++)
	{
		dias = diasMes(i, anyo);
		total = total + dias;
	}
	total = total + dia;
	return total;
}
int contarBisiestos(int anyoInicio, int anyoFinal){
	int contador = 0;
	for (int i = anyoInicio; i < anyoFinal; i++){
		if (esBisiesto(i) == true){ 
			contador++;
		}
	}
	return contador;
}
int diasMes(int mes, int anyo){
	int dias;
	if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
		dias = 31;
	}
	else if (mes == 4 || mes == 6 || mes == 9 || mes == 11){
		dias = 30;
	}
	else if (mes == 2){
		if (esBisiesto(anyo) == true){
			dias = 29;
		}
		else{
			dias = 28;
		}
	}
	return dias;
}
bool esBisiesto(int anyo){
	bool bisiesto;
	if (anyo % 4 != 0 || (anyo % 100 == 0 && anyo % 400 != 0))
		bisiesto = false;
	else
		bisiesto = true;
	return bisiesto;
}
int diaSemana(long int numDias){
	int num;
	if (numDias <= 7){ // si es uno de los primeros dias se suma 6 para que el modulo salga bien
		numDias = numDias + 6;
	}
	else {
		numDias = numDias - 1;// no se cuenta el 1 de enero de 1900, asi si lo contamos
	}
	num = numDias % 7;
	return num;
}
string nombreDia(int representacionDia){
	string dia;
	if (representacionDia == 0){
		dia = "Lunes";
	}
	else if (representacionDia == 1){
		dia = "Martes";
	}
	else if (representacionDia == 2){
		dia = "Miercoles";
	}
	else if (representacionDia == 3){
		dia = "Jueves";
	}
	else if (representacionDia == 4){
		dia = "Viernes";
	}
	else if (representacionDia == 5){
		dia = "Sabado";
	}
	else if (representacionDia == 6){ 
		dia = "Domingo";
	}
	return dia;
}
string diaDeLaSemana(int dia, int mes, int anyo){//mal
	int dias = diasTranscurridos(dia, mes, anyo);
	int representacionDia = diaSemana(dias);
	string diaSemana = nombreDia(representacionDia);

	return diaSemana;
}
int primerDomingoMes(int mes, int anyo){
	int diasAnuales = diasAnyosCompletos(anyo);
	int diasAño = diasEsteAnyo(1, mes, anyo);
	int totalDias = diasAnuales + diasAño;
	int dias = diaSemana(totalDias);			//devuelve del 0-6
	if (dias == 0)									// Si el primer dia del mes es lunes
		dias = 7;									//el domingo sera dia 1
	else if (dias == 1)				// martes
		dias = 6;
	else if (dias == 2)				//miercoles
		dias = 5;
	else if (dias == 3)				//jueves
		dias = 4 ;
	else if (dias == 4)				//viernes
		dias = 3;
	else if (dias == 5)				//sabado
		dias = 2 ;
	else {							//domingo
		dias = 1;
	}
	return dias;
}
int domingosAnyo(int anyo){
	string nombre;
	int contador = 0;
	bool ok;
	cout << setw(50) << "Domingos de " << anyo << endl;
	for (int i = 1; i <= 12; i++){
		int domingo = primerDomingoMes(i, anyo);
		contador++;
		nombre = obtenerMes(i);
		cout << domingo << " de " << nombre << endl;
		ok = false;
		while (!ok){
			domingo = domingo + 7;
			cout << domingo << " de " << nombre << endl;
			ok = finMes(i, anyo, domingo);
			contador++;
		}
		//ok = false;
	}
	return contador;
}
bool puentes(){  ///// AÑO >1900 , DIA DISTINTO DE DOMINGO						SOLOOOO??????????????????
	ifstream archivoFiestas;
	ofstream archivoPuentes;
	bool ok = true;
	string nombre;
	int anyo, mes, dia,numDias, diaSem;
	archivoFiestas.open("fiestas.txt");
	archivoPuentes.open("puentes.txt"); 
	if (!archivoFiestas.is_open() || !archivoPuentes.is_open())
		ok = false;
	else{
		archivoFiestas >> anyo;
		if (anyo < 1900){
			ok = false;
			cout << "El año del archivo es incorrecto." << endl;
		}
		else{
			archivoPuentes << anyo << endl;
			archivoFiestas >> dia;
			archivoFiestas >> mes;
			while ((dia != 0 && mes != 0)){
				numDias = diasTranscurridos(dia, mes, anyo);
				diaSem = diaSemana(numDias);
				if (diaSem == 1 || diaSem == 3){
					nombre = nombreDia(diaSem);
					archivoPuentes << dia << " " << mes << " " << nombre << endl;
				}

				archivoFiestas >> dia;
				archivoFiestas >> mes;
			}
			archivoPuentes << 0 << " " << 0 << " XXX" << endl;
		}
	}
	archivoPuentes.close();
	archivoFiestas.close();
	return ok;
}
string obtenerMes(int mes){
	string nombre;
	if (mes == 1)
		nombre = "enero";
	else if (mes == 2)
		nombre = "febrero";
	else if (mes == 3)
		nombre = "marzo";
	else if (mes == 4)
		nombre = "abril";
	else if (mes == 5)
		nombre = "mayo";
	else if (mes == 6)
		nombre = "junio";
	else if (mes == 7)
		nombre = "julio";
	else if (mes == 8)
		nombre = "agosto";
	else if (mes == 9)
		nombre = "septiembre";
	else if (mes == 10)
		nombre = "octubre";
	else if (mes == 11)
		nombre = "noviembre";
	else if (mes == 12)
		nombre = "diciembre";

	return nombre;
}
bool finMes(int mes, int anyo, int domingo){
	int diasdelMes;
	bool fin = false;
	diasdelMes = diasMes(mes, anyo);
	if (diasdelMes == 31 && domingo > 24)
		fin = true;
	else if (diasdelMes == 30 && domingo > 23)
		fin = true;
	else if (diasdelMes == 28 && domingo > 21)
		fin = true;
	else if (diasdelMes == 29 && domingo > 22)
		fin = true;
	else
		fin = false;

	return fin;
}
bool puentesMejorado(){
	ifstream archivoFiestas;
	ofstream archivoPuentes;
	int posibleDia, posibleMes;
	bool ok = true;
	string nombre;
	int anyo, mes, dia, numDias, diaSem;
	archivoFiestas.open("fiestas.txt");
	archivoPuentes.open("puentes.txt");
	if (!archivoFiestas.is_open() || !archivoPuentes.is_open())
		ok = false;
	else{
		archivoFiestas >> anyo;
		if (anyo < 1900){
			ok = false;
			cout << "El año del archivo es incorrecto." << endl;
		}
		else{
			archivoPuentes << anyo << endl;
			archivoFiestas >> dia;
			archivoFiestas >> mes;
			while ((dia != 0 && mes != 0)){
				numDias = diasTranscurridos(dia, mes, anyo);
				diaSem = diaSemana(numDias);
				if (diaSem == 0){
					posibleDia = dia + 1;
					posibleMes = mes;
				}
				if (diaSem == 1){
					if (dia != posibleDia && mes != posibleMes))
					nombre = nombreDia(diaSem);
					archivoPuentes << dia << " " << mes << " " << nombre << endl;
				}
				if (diaSem == 3){
					nombre = nombreDia(diaSem);
					posibleDia = dia;
					posibleMes = mes;
				}
				archivoFiestas >> dia;
				archivoFiestas >> mes;
				if ((diaSem == 3 ) && ((dia != posibleDia +1)&& (mes != posibleMes))){
					archivoPuentes << posibleDia << " " << posibleMes << " " << nombre << endl;	
				}
			}
			archivoPuentes << 0 << " " << 0 << " XXX" << endl;
		}
	}
	archivoPuentes.close();
	archivoFiestas.close();
	return ok;
}