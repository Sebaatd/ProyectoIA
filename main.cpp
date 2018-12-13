#include<bits/stdc++.h>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
#include "funciones.h"

using namespace std;

int main(int argc, char **argv){
	ofstream myfile;
	int cant_autos, cant_opciones, cant_clases, retorno;
	string input, instancia, path;
	vector<int> maxCantAutosBloq, tamBloq, autos_por_clase, solucion, matriz_conflictos;
	vector<vector<int>> opciones_por_clase, dominios;
	
	path = "./instancias/";

	cout << "Proyecto Inteligencia Artificial - INF123" << endl;
	cout << "Resolución del Car Sequencing Problem mediante FC-GBJ" << endl;
	cout << endl;

	cout << "Escriba el nombre de la instancia que desea ejecutar (sin el .txt): ";
	
	getline(cin, input);
	instancia = input;
	path += input+".txt";

	ifstream f(path.c_str());

	//Archivo no existe. Terminar ejecución.
	if(!f.good()){
		cout << "No se encuentra la instancia " << instancia << endl;
		return 0;
	}

	//Archivo si existe. Continuar ejecución.
	cout << "Instancia encontrada: " << instancia << endl << endl;
	cout << "-----------------------------IMPORTANTE: SOBRE BÚSQUEDAS -----------------------------------" << endl;
	cout << "A continuación se comenzará a buscar las soluciones óptimas para la instancia seleccionada." << endl;
	cout << "Cada vez que se encuentre una solución, se anunciará con el tiempo que tardó en encontrarse." << endl;
	cout << "Para interrumpir la búsqueda, presionar la combinación de teclas ctrl + C." << endl;
	cout << "Para mas información, consultar el README." << endl;
	cout << "-------------------------------------------------------------------------------------------." << endl;
	cout << endl;

	cout << "Presione Enter para continuar";
	cin.ignore();
	cout << "Buscando soluciones óptimas" << endl;

	lecturaInput(path, cant_autos, cant_opciones, cant_clases, maxCantAutosBloq, 
		tamBloq, autos_por_clase, opciones_por_clase, dominios, solucion, matriz_conflictos);

	clock_t begin = clock();
	path = "./Resultados/"+instancia+".txt";

	myfile.open(path.c_str());

	//BORRAR: Para casos de prueba no más
	string path_aux;
	path_aux = "./Resultados/"+instancia+"_times.txt";
	ofstream myfile_aux;
	myfile_aux.open(path_aux.c_str());
	//RECORDAR BORRAR LAS LLAMADAS A LAS FUNCIONES TAMBIÉN (myfile_aux)

	retorno = -1;
	FC(0, autos_por_clase, solucion, dominios, cant_opciones, tamBloq, 
		maxCantAutosBloq, opciones_por_clase, cant_autos, matriz_conflictos, retorno, begin, myfile, myfile_aux);	

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Programa terminado en " << elapsed_secs << " segs. Todas las soluciones óptimas fueron encontradas" << endl;

	/*
	Variables:
		-cant_autos: Valor del total de autos.
		-cant_opciones: Valor del total de opciones.
		-cant_clases: Valor del total de clases distintas.

	Vectores:
		-maxCantAutosBloq: Vector que almacena los máximos de autos por bloque, donde el índice es el número de la opción.
		-tamBloq: Vector que almacena el tamaño del bloque, donde el índice es el número de la opción.
		-autos_por_clase: Vector que almacena la cantidad de autos de cada clase, donde el índice es el número de la clase.
		-opciones_por_clase: Vector de 2 dimensiones que almacena las opciones de cada clase, donde el índice es el número de la clase.
	*/


	/*

	

	





	*/
}