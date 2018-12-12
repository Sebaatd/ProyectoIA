#include<bits/stdc++.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void lecturaInput(int &cant_autos, int &cant_opciones, int &cant_clases, vector<int> &maxCantAutosBloq, 
	vector<int> &tamBloq, vector<int> &autos_por_clase, vector<vector<int>> &opciones_por_clase, vector<vector<int>> &dominios, 
	vector<int> &solucion, vector<vector<int>> &matriz_asociacion){

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

void imprimirSolucion(vector<int> &solucion, vector<vector<int>> opciones_por_clase, int cant_opciones){
	
	for(size_t i = 0; i < solucion.size(); i++){
		cout << solucion[i] << "  ";
		for(int j = 0; j < cant_opciones; j++){
			cout << opciones_por_clase[solucion[i]][j] << " ";
		}
		cout << endl;	
	}
	cout << endl;
}

int existeVacio(vector<vector<int>> dominios){
	int vacio = 0;
	for(size_t i = 0; i < dominios.size(); i++){
		if(dominios[i].empty()){
			vacio = 1;
		}
	}
	return vacio;
}

int excedeMaximo(int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq, vector<int> solucion, vector<vector<int>> opciones_por_clase){
	int clase, cont;
	vector<vector<int>> opciones_por_secuencia;

	for(size_t i = 0; i < solucion.size(); i++){
		clase = solucion[i];
		opciones_por_secuencia.push_back(opciones_por_clase[clase]);
	}

	cont = 0;
	size_t j = 0;
	int tamano_bloque;
	for(int i = 0; i < cant_opciones; i++){
		j = 0;
		tamano_bloque = tamBloq[i];
		while(j < solucion.size()){
			cont = 0;

			if(j + tamano_bloque <= solucion.size()){
				for(int k = 0; k < tamano_bloque; k++){
					if(opciones_por_secuencia[j+k][i] == 1){
						cont++;
					}
				}
				if(cont > maxCantAutosBloq[i]){
					return 1;

				}
			}
			j++;
		}
	}
	return 0;
}

int filtrarDominio(int nivel, vector<int> &dominio, vector<int> autos_por_clase, int valor, vector<int> &solucion, int cant_opciones, 
	vector<int> tamBloq, vector<int> maxCantAutosBloq, vector<vector<int>> opciones_por_clase){
	
	if(dominio.empty()){
		return 1;
	}

	vector<int> solucion_temporal;
	
	for(int i = 0; i <= nivel; i++){
		solucion_temporal.push_back(solucion[i]);
	}

	auto it = dominio.begin();
	while(it != dominio.end()){
		if(*it == valor && autos_por_clase[valor] == 0){
			it = dominio.erase(it);
		}

		else{
			solucion_temporal.push_back(*it);
			if(excedeMaximo(cant_opciones, tamBloq, maxCantAutosBloq, solucion_temporal, opciones_por_clase) == 1){
				it = dominio.erase(it);
			}
			else{
				++it;
			}
			solucion_temporal.erase(solucion_temporal.end()-1);	
		}
	}
	return 0;
}

void prepararDominio(int nivel, vector<vector<int>> &dominio_original, vector<vector<int>> &dominio_dinamico){
	dominio_dinamico = dominio_original;
	
	if(nivel != 0){
		for(int i = 0; i <= nivel; i++){
			dominio_dinamico.erase(dominio_dinamico.begin()+i);
		}	
	}

}

void FC(int nivel, int cant_clases, vector<int> autos_por_clase, vector<int> &solucion, vector<vector<int>> &dominios, int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq,
		vector<vector<int>> opciones_por_clase, int cant_autos, vector<vector<int>> &dominio_dinamico){

	size_t cont = 0;
	vector<int> clases_disponibles, autos_por_clase_aux;
	clases_disponibles = dominio_dinamico[0];
	//1. Seleccionar X_i.
	for (vector<int>::iterator it = clases_disponibles.begin() ; it != clases_disponibles.end(); ++it){
		autos_por_clase_aux = autos_por_clase;
		prepararDominio(nivel, dominios, dominio_dinamico);
		cont++;

		//2. Instanciar X_i <- a_i: a_i existe en D_i -- D_i: Dominio de i.
		if(autos_por_clase_aux[*it] > 0){
			solucion[nivel] = *it;
			autos_por_clase_aux[*it] -= 1;

			//3. Razonar hacia adelante (forward-check).
			//Eliminar de los dominios de las variables no instanciadas, aquellos valores inconsistentes con respecto a la instanciación, de acuerdo al conjunto de restricciones.
			for(size_t j = 0; j < dominio_dinamico.size(); j++){
				filtrarDominio(nivel, dominio_dinamico[j], autos_por_clase_aux, *it, solucion, cant_opciones, tamBloq, maxCantAutosBloq, opciones_por_clase);				
			}

			//4. Si quedan valores posibles en los dominios de todas las variables por instanciar, entonces:
			if(existeVacio(dominio_dinamico) == 0){
				//4.1. Si i < n, incrementar i, e ir al paso (1).
				if(nivel < cant_autos-1){
					FC(nivel+1, cant_clases, autos_por_clase_aux, solucion, dominios, cant_opciones, 
						tamBloq, maxCantAutosBloq, opciones_por_clase, cant_autos, dominio_dinamico);

				}
				//4.2. Si i = n, salir con la solución.
				else{
					imprimirSolucion(solucion, opciones_por_clase, cant_opciones);
				}
			}

			//5. Si existe una variable por instanciar, sin valores posibles en su dominio, entonces retractar los efectos de la instanciación.
			else{
				//Si quedan valores por intentar en el dominio actual, volver al paso (2) (volver a instanciar).
				//Si no quedan valores:
				if(cont == clases_disponibles.size()){
					//Si i = 1, salir sin solución
					if(nivel == 1){
						cout << "No existe solución" << endl;
					}
					//Si i > 1, decrementar i y volver al paso (2).
				}
			}
		}
	}
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
	vector<vector<int>> opciones_por_clase, dominios, matriz_asociacion;
	vector<vector<int>> dominio_dinamico;

	lecturaInput(cant_autos, cant_opciones, cant_clases, maxCantAutosBloq, 
		tamBloq, autos_por_clase, opciones_por_clase, dominios, solucion, matriz_asociacion);

	dominio_dinamico = dominios;
	FC(0, cant_clases, autos_por_clase, solucion, dominios, cant_opciones, tamBloq, 
		maxCantAutosBloq, opciones_por_clase, cant_autos, dominio_dinamico);	

}