#include<bits/stdc++.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void lecturaInput(int &cant_autos, int &cant_opciones, int &cant_clases, vector<int> &maxCantAutosBloq, 
	vector<int> &tamBloq, vector<int> &autos_por_clase, vector<vector<int>> &opciones_por_clase, vector<vector<int>> &dominios, vector<int> &solucion){

	string line;
	int cont = 0;
	vector<string> result;
	vector<int> opciones, clases;

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

		    for(int i = 0; i < cant_clases; i++){
		    	clases.push_back(i);
		    }

	        for(int i = 0; i < cant_autos; i++){
    			dominios.push_back(clases);
    			solucion.push_back(-1);
    		}

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

void ForwardChecking(int nivel, vector<int> solucion, int cant_clases, vector<vector<int>> dominios, vector<int> autos_por_clase){
	int clase_instanciada;
	vector<int> clases_disponibles(cant_clases), autos_disponibles_por_clase = autos_por_clase;
	vector<vector<int>> dominios_filtrados = dominios;

	iota(clases_disponibles.begin(), clases_disponibles.end(), 0);

	if(clases_disponibles.size() != 0){
		clase_instanciada = clases_disponibles[0];
		solucion[nivel] = clase_instanciada;


		clases_disponibles.erase(clases_disponibles.begin()); //OJO QUE SE BORRA SIEMPRE LA PRIMERA
		dominios_filtrados.erase(dominios_filtrados.begin()+nivel);

		for(size_t i = 0; i < dominios_filtrados.size(); i++){
			//ELIMINAR TODOS LOS VALORES INCONSISTENTES

		}


	}
}

void FC(int nivel, int cant_clases, vector<int> autos_por_clase, vector<int> &solucion, vector<vector<int>> dominios){
	
	//Seleccionar X_i
	for(int i = 0; i < cant_clases; i++){

		//Instanciar X_i
		if(autos_por_clase[i] != 0){
			solucion[nivel] = i;
			autos_por_clase[i]--;
			//dominios.erase(dominios.begin()+i);

			//Razonar hacia adelante (forward-check)
			for(size_t j = 0; j < dominios.size(); j++){

				for(size_t k = 0; k < dominios[j].size(); k++){
					if(dominios[j][k] == i && autos_por_clase[i] == 0){
						dominios[j][k] = -1;
					}
					cout << dominios[j][k];
				}
				cout << endl;
				
			}
			cout << endl;
		}

		break;
	}


}

int tresFC(int nivel, vector<int> &solucion){
	if(nivel == 9){
		return 1;
	}
	

}


vector<int> tercerFC(vector<int> solucion){
	vector<int> secuencia_final = solucion;
	int i = tresFC(0, secuencia_final);
	return secuencia_final;
}


int main(){
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

	int cant_autos, cant_opciones, cant_clases;
	vector<int> maxCantAutosBloq, tamBloq, autos_por_clase, solucion;
	vector<vector<int>> opciones_por_clase, dominios;

	lecturaInput(cant_autos, cant_opciones, cant_clases, maxCantAutosBloq, tamBloq, autos_por_clase, opciones_por_clase, dominios, solucion);

	//ForwardChecking(0, solucion, cant_clases, dominios, autos_por_clase);
	FC(0, cant_clases, autos_por_clase, solucion, dominios);


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

	/*
	for(int i = 0; i < cant_autos; i++){
		cout << "Posición " << i << ": ";
		for(int j = 0; j < cant_clases; j++){
			cout << dominios[i][j] << " ";
		}
		cout << endl;
	}
	*/
	

}