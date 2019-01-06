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

	ofstream output;
	int cant_autos, cant_opciones, cant_clases, retorno, cant_min_rest_violadas, cant_sol_optimas;
	string input, instancia, path;
	vector<int> maxCantAutosBloq, tamBloq, autos_por_clase, solucion, matriz_conflictos;
	vector<vector<int>> opciones_por_clase, dominios;
	
	path = "./Instancias/";

	cout << "Proyecto Inteligencia Artificial - INF295" << endl;
	cout << "Resolución del Car Sequencing Problem mediante FC-GBJ" << endl;
	cout << endl;

	cout << "Escriba el nombre de la instancia que desea ejecutar (sin el .txt): ";
	
	getline(cin, input);
	instancia = input;
	path += input+".txt";
	cout << path << endl;
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
	cout << endl << "Buscando soluciones" << endl;

	lecturaInput(path, cant_autos, cant_opciones, cant_clases, maxCantAutosBloq, 
		tamBloq, autos_por_clase, opciones_por_clase, dominios, solucion, matriz_conflictos);

	clock_t begin = clock();
	path = "./Resultados/"+instancia+".txt";

	retorno = -1;
	cant_min_rest_violadas = -1;
	cant_sol_optimas = 0;

	//Caso de que haya solo un auto. Revisar si cumple la condición de la única pieza de ensamblaje.
	if(cant_autos == 1){
		for(size_t i = 0; i < opciones_por_clase[0].size(); i++){
			if(opciones_por_clase[0][i] > maxCantAutosBloq[i]){
				cout << "No existe solución" << endl;
				return 0;
			}
		}

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		output.open(path.c_str(), ios::trunc);
		cout << "¡Solución óptima encontrada en " << elapsed_secs << " segs!" << endl;
		output << "¡Solución óptima encontrada en " << elapsed_secs << " segs!" << endl;
		output << "---------------------------------------------------------------" << endl;		
		output << dominios[0][0] << "  ";
		for(size_t j = 0; j < opciones_por_clase[0].size(); j++){
			output << opciones_por_clase[0][j] << " ";
		}	
		return 0;
	}

	//Caso de que haya mas de un auto. Se realiza FC recursivamente.
	FC(0, autos_por_clase, solucion, dominios, cant_opciones, tamBloq, 
		maxCantAutosBloq, opciones_por_clase, cant_autos, matriz_conflictos, 
		retorno, begin, cant_min_rest_violadas, output, path, cant_sol_optimas);	

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	if(cant_sol_optimas == 0){
		cout << "No existe solución óptima" << endl;
		cout << "Se guarda en el archivo la solución con menor cantidad de restricciones violadas" << endl;
	}

	cout << endl << "Programa terminado en " << elapsed_secs << " segs." << endl;
}
