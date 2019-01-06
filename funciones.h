#include<bits/stdc++.h>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

//Lectura del archivo principal. Se almacenan los datos en variables del programa.
void lecturaInput(string path, int &cant_autos, int &cant_opciones, int &cant_clases, 
	vector<int> &maxCantAutosBloq, vector<int> &tamBloq, vector<int> &autos_por_clase, 
	vector<vector<int>> &opciones_por_clase, vector<vector<int>> &dominios, vector<int> &solucion, 
	vector<int> &matriz_conflictos);

//Función para imprimir en consola y archivo los resultados.
void imprimirSolucion(int fo, vector<int> &solucion, vector<vector<int>> opciones_por_clase, 
	int cant_opciones, ofstream &myfile, ofstream &myfile_aux, string path, clock_t begin, 
	int &cant_sol_optimas);

//Función que verifica si hay algun vacio en los dominios. Ideal para el FC.
int existeVacio(vector<vector<int>> dominios);

//Función que verifica si se excede el máximo determinado por bloques.
int excedeMaximo(int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq, 
	vector<int> solucion, vector<vector<int>> opciones_por_clase, int &cant_min_rest_violadas, 
	int cant_autos);

//Función que devuelve cuantas restricciones viola la solución parcial.
int cantRest_violadas(int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq, 
	vector<int> solucion, vector<vector<int>> opciones_por_clase);

//Función para el FC que descarta los autos que no tengan stock.
int DescartarDemandas(int nivel, int pos, vector<int> &dominio, vector<int> autos_por_clase, 
	int valor, vector<int> &matriz_conflictos);

//Función para el FC que descarta las posibles asignaciones que provocarían violación de restricciones 
//mayores al mínimo actual.
int DescartarExcesos(int nivel, int pos, vector<int> &dominio, vector<int> &solucion, int cant_opciones, 
	vector<int> tamBloq, vector<int> maxCantAutosBloq, vector<vector<int>> opciones_por_clase, 
	vector<int> &matriz_conflictos, int &cant_min_rest_violadas, int cant_autos);

//Forward Checking. Se ejecuta recursivamente.
void FC(int nivel, vector<int> autos_por_clase, vector<int> &solucion, vector<vector<int>> dominios, 
	int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq, vector<vector<int>> 
	opciones_por_clase, int cant_autos, vector<int> &matriz_conflictos, int &retorno, clock_t &begin, 
	int &cant_min_rest_violadas, ofstream &output, string path, int &cant_sol_optimas);