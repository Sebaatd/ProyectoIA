#include<bits/stdc++.h>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

void lecturaInput(string path, int &cant_autos, int &cant_opciones, int &cant_clases, vector<int> &maxCantAutosBloq, 
	vector<int> &tamBloq, vector<int> &autos_por_clase, vector<vector<int>> &opciones_por_clase, vector<vector<int>> &dominios, 
	vector<int> &solucion, vector<int> &matriz_conflictos);

void imprimirSolucion(vector<int> &solucion, vector<vector<int>> opciones_por_clase, int cant_opciones, ofstream &myfile,
	ofstream &myfile_aux);

int existeVacio(vector<vector<int>> dominios);

int excedeMaximo(int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq, vector<int> solucion, 
	vector<vector<int>> opciones_por_clase);

int DescartarDemandas(int nivel, int pos, vector<int> &dominio, vector<int> autos_por_clase, int valor, vector<int> &matriz_conflictos);

int DescartarExcesos(int nivel, int pos, vector<int> &dominio, vector<int> &solucion, int cant_opciones, 
	vector<int> tamBloq, vector<int> maxCantAutosBloq, vector<vector<int>> opciones_por_clase, vector<int> &matriz_conflictos);

void FC(int nivel, vector<int> autos_por_clase, vector<int> &solucion, vector<vector<int>> dominios, int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq,
		vector<vector<int>> opciones_por_clase, int cant_autos, vector<int> &matriz_conflictos, 
		int &retorno, clock_t &begin, ofstream &myfile, ofstream &myfile_aux);