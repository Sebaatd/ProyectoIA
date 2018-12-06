#include<bits/stdc++.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void lecturaInput(int &cant_autos, int &cant_opciones, int &cant_clases, vector<int> &maxCantAutosBloq, 
	vector<int> &tamBloq, vector<int> &autos_por_clase, vector<vector<int>> &opciones_por_clase){

	string line;
	int cont = 0;
	vector<string> result;
	vector<int> opciones;

	while (getline(cin, line)){
		//Primera línea: Obtención de cantidades de: autos, opciones y clases.
		if(cont == 0){
			istringstream iss(line);

			for(string s; iss >> s;){
				result.push_back(s);
			}

		    cant_autos = stoi(result[0]);
		    cant_opciones = stoi(result[1]);
		    cant_clases = stoi(result[2]);
		    result.clear();
		}

		//Segunda línea: Obtención de tamaño máximo de autos por bloques.
		else if(cont == 1){
			istringstream iss(line);

			for(string s; iss >> s;){
				result.push_back(s);
			}

			for(size_t i = 0; i < result.size(); i++){
				maxCantAutosBloq.push_back(stoi(result[i]));
			}
			result.clear();
		}

		//Tercera línea: Obtención de los tamaños del bloque.
		else if(cont == 2){
			istringstream iss(line);

			for(string s; iss >> s;){
				result.push_back(s);
			}

			for(size_t i = 0; i < result.size(); i++){
				tamBloq.push_back(stoi(result[i]));
			}
			result.clear();
		}

		//Resto de las líneas: Obtención del número de autos en cada clase y las opciones que utiliza
		else{
			istringstream iss(line);

			for(string s; iss >> s;){
				result.push_back(s);
			}

			autos_por_clase.push_back(stoi(result[1]));

			for(int i = 0; i < cant_opciones; i++){
				opciones.push_back(stoi(result[i+2]));
			}

			opciones_por_clase.push_back(opciones);

			result.clear();
			opciones.clear();
		}

		cont++;
    }

}

int main(){
	int cant_autos, cant_opciones, cant_clases;
	vector<int> maxCantAutosBloq, tamBloq, autos_por_clase;
	vector<vector<int>> opciones_por_clase;

	lecturaInput(cant_autos, cant_opciones, cant_clases, maxCantAutosBloq, tamBloq, autos_por_clase, opciones_por_clase);

	/* REVISION INPUT
	cout << cant_autos << " " << cant_opciones << " " << cant_clases << endl;
	for(size_t i = 0; i < maxCantAutosBloq.size(); i++){
		cout << maxCantAutosBloq[i] << " ";
	}
	cout << endl;

	for(size_t i = 0; i < tamBloq.size(); i++){
		cout << tamBloq[i] << " ";
	}
	cout << endl;

	for(size_t i = 0; i < opciones_por_clase.size(); i++){
		cout << i << " " << autos_por_clase[i] << " ";
		for(size_t j = 0; j < opciones_por_clase[i].size(); j++){
			cout << opciones_por_clase[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	*/

}