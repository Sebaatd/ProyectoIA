#include<bits/stdc++.h>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

//Lectura del archivo principal. Se almacenan los datos en variables del programa.
void lecturaInput(string path, int &cant_autos, int &cant_opciones, int &cant_clases, vector<int> &maxCantAutosBloq, 
	vector<int> &tamBloq, vector<int> &autos_por_clase, vector<vector<int>> &opciones_por_clase, vector<vector<int>> &dominios, 
	vector<int> &solucion, vector<int> &matriz_conflictos);

//Funcion para imprimir en consola y archivo los resultados.
void imprimirSolucion(int fo, vector<int> &solucion, vector<vector<int>> opciones_por_clase, int cant_opciones, ofstream &myfile,
	ofstream &myfile_aux, string path, clock_t begin);

int existeVacio(vector<vector<int>> dominios);

int excedeMaximo(int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq, vector<int> solucion, 
	vector<vector<int>> opciones_por_clase, int &cant_min_rest_violadas, int cant_autos);

int cantRest_violadas(int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq, 
	vector<int> solucion, vector<vector<int>> opciones_por_clase);

int DescartarDemandas(int nivel, int pos, vector<int> &dominio, vector<int> autos_por_clase, int valor, vector<int> &matriz_conflictos);

int DescartarExcesos(int nivel, int pos, vector<int> &dominio, vector<int> &solucion, int cant_opciones, 
	vector<int> tamBloq, vector<int> maxCantAutosBloq, vector<vector<int>> opciones_por_clase, vector<int> &matriz_conflictos, 
	int &cant_min_rest_violadas, int cant_autos);

void FC(int nivel, vector<int> autos_por_clase, vector<int> &solucion, vector<vector<int>> dominios, int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq,
	vector<vector<int>> opciones_por_clase, int cant_autos, vector<int> &matriz_conflictos, 
	int &retorno, clock_t &begin, int &cant_min_rest_violadas, ofstream &output, string path);