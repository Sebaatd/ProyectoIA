#include "funciones.h"

void lecturaInput(string path, int &cant_autos, int &cant_opciones, int &cant_clases, vector<int> &maxCantAutosBloq, 
	vector<int> &tamBloq, vector<int> &autos_por_clase, vector<vector<int>> &opciones_por_clase, vector<vector<int>> &dominios, 
	vector<int> &solucion, vector<int> &matriz_conflictos){

	string line;
	int cont = 0;
	vector<string> result;
	vector<int> opciones, clases;

	ifstream myfile(path.c_str());

	while (getline(myfile, line)){
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
    			matriz_conflictos.push_back(-1);
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

		//Resto de las líneas: Obtención del número de autos en cada clase y las opciones que utiliza.
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

    myfile.close();
}

void imprimirSolucion(vector<int> &solucion, vector<vector<int>> opciones_por_clase, int cant_opciones, ofstream &myfile, 
	ofstream &myfile_aux){
	for(size_t i = 0; i < solucion.size(); i++){
		myfile_aux << solucion[i] << "  ";
		myfile << solucion[i] << "  ";
		for(int j = 0; j < cant_opciones; j++){
			myfile_aux << opciones_por_clase[solucion[i]][j] << " ";
			myfile << opciones_por_clase[solucion[i]][j] << " ";
		}
		myfile_aux << endl;	
		myfile << endl;
	}
	myfile_aux << endl;
	myfile << endl;
}

int existeVacio(vector<vector<int>> dominios){
	for(size_t i = 0; i < dominios.size(); i++){
		if(dominios[i].empty()){
			return 1;
		}
	}
	return 0;
}

int excedeMaximo(int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq, vector<int> solucion, vector<vector<int>> opciones_por_clase, 
	int &cant_min_rest_violadas, int cant_autos){
	int clase, cont, cant_rest_violadas;
	vector<vector<int>> opciones_por_secuencia;

	for(size_t i = 0; i < solucion.size(); i++){
		clase = solucion[i];
		opciones_por_secuencia.push_back(opciones_por_clase[clase]);
	}

	cont = 0;
	cant_rest_violadas = 0;

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
					cant_rest_violadas += 1;
				}
			}
			j++;
		}
	}

	if(static_cast<int>(solucion.size()) == cant_autos){
		if(cant_min_rest_violadas == -1){
			cant_min_rest_violadas = cant_rest_violadas;
		}
		else if(cant_min_rest_violadas >= cant_rest_violadas){
			cant_min_rest_violadas = cant_rest_violadas;
		}
		else{
			return 1;
		}

		return 0;
	}

	else{
		if(cant_min_rest_violadas != -1 && cant_min_rest_violadas < cant_rest_violadas){
			return 1;
		}
	}



	return 0;
}

int cantRest_violadas(int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq, 
						vector<int> solucion, vector<vector<int>> opciones_por_clase){

	int clase, cont, cant_rest_violadas, tamano_bloque;
	size_t j;
	vector<vector<int>> opciones_por_secuencia;

	for(size_t i = 0; i < solucion.size(); i++){
		clase = solucion[i];
		opciones_por_secuencia.push_back(opciones_por_clase[clase]);
	}

	cont = 0;
	cant_rest_violadas = 0;

	
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
					cant_rest_violadas += 1;
				}
			}
			j++;
		}
	}

	return cant_rest_violadas;
}


int DescartarDemandas(int nivel, int pos, vector<int> &dominio, vector<int> autos_por_clase, int valor, vector<int> &matriz_conflictos){
	if(dominio.empty()){
		return 1;
	}

	auto it = dominio.begin();
	while(it != dominio.end()){
		if(*it == valor && autos_por_clase[valor] == 0){
			it = dominio.erase(it);
			matriz_conflictos[nivel+pos] = nivel;
		}

		else{
			++it;
		}
	}
	return 0;
}

int DescartarExcesos(int nivel, int pos, vector<int> &dominio, vector<int> &solucion, int cant_opciones, 
	vector<int> tamBloq, vector<int> maxCantAutosBloq, vector<vector<int>> opciones_por_clase, vector<int> &matriz_conflictos,
	 int &cant_min_rest_violadas, int cant_autos){

	if(dominio.empty()){
		return 1;
	}

	vector<int> solucion_temporal;
	
	for(int i = 0; i <= nivel; i++){
		solucion_temporal.push_back(solucion[i]);
	}

	auto it = dominio.begin();
	while(it != dominio.end()){
		solucion_temporal.push_back(*it);
		if(excedeMaximo(cant_opciones, tamBloq, maxCantAutosBloq, solucion_temporal, opciones_por_clase, cant_min_rest_violadas, cant_autos) == 1){
			it = dominio.erase(it);
			matriz_conflictos[nivel+pos] = nivel;
		}
		else{
			++it;
		}
		solucion_temporal.erase(solucion_temporal.end()-1);	
	}
	return 0;
}

void FC(int nivel, vector<int> autos_por_clase, vector<int> &solucion, vector<vector<int>> dominios, int cant_opciones, vector<int> tamBloq, vector<int> maxCantAutosBloq,
		vector<vector<int>> opciones_por_clase, int cant_autos, vector<int> &matriz_conflictos, 
		int &retorno, clock_t &begin, ofstream &myfile, ofstream &myfile_aux, int &cant_min_rest_violadas){
	int fo; 
	size_t cont = 0;
	vector<int> clases_disponibles, autos_por_clase_aux;
	vector<vector<int>> respaldo;
	clases_disponibles = dominios[0];
	
	//1. Seleccionar X_i.
	for(vector<int>::iterator it = clases_disponibles.begin(); it != clases_disponibles.end(); ++it){
		autos_por_clase_aux = autos_por_clase;
		respaldo = dominios;
		respaldo.erase(respaldo.begin());	
		cont++;

		//2. Instanciar X_i <- a_i: a_i existe en D_i -- D_i: Dominio de i.
		if(autos_por_clase_aux[*it] > 0){
			solucion[nivel] = *it;
			autos_por_clase_aux[*it] -= 1;

			//3. Razonar hacia adelante (forward-check).
			//Eliminar de los dominios de las variables no instanciadas, aquellos valores inconsistentes con respecto a la instanciación, de acuerdo al conjunto de restricciones.
			//Eliminar autos sin demanda de los dominios.
			for(size_t j = 0; j < respaldo.size(); j++){
				DescartarDemandas(nivel, j+1, respaldo[j], autos_por_clase_aux, *it, matriz_conflictos);				
			}

			//Eliminar autos que infringen restricción de máximo por bloque de los dominios.
			DescartarExcesos(nivel, 1, respaldo[0], solucion, cant_opciones, tamBloq, maxCantAutosBloq, 
				opciones_por_clase, matriz_conflictos, cant_min_rest_violadas, cant_autos);

			//4. Si quedan valores posibles en los dominios de todas las variables por instanciar, entonces:
			if(existeVacio(respaldo) == 0){
				//4.1. Si i < n, incrementar i, e ir al paso (1).
				if(nivel < cant_autos-1){
					FC(nivel+1, autos_por_clase_aux, solucion, respaldo, cant_opciones, 
						tamBloq, maxCantAutosBloq, opciones_por_clase, cant_autos, matriz_conflictos, 
						retorno, begin, myfile, myfile_aux, cant_min_rest_violadas);
					
					if(retorno != -1 && retorno != nivel){
						break;
					}

					else if(retorno == nivel){
						retorno = -1;
					}
					
				}
				//4.2. Si i = n, salir con la solución.
				else{
					if(excedeMaximo(cant_opciones, tamBloq, maxCantAutosBloq, solucion, opciones_por_clase, cant_min_rest_violadas, cant_autos) != 1){
						fo = cantRest_violadas(cant_opciones, tamBloq, maxCantAutosBloq, solucion, opciones_por_clase);
						clock_t end = clock();
						double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

						if(elapsed_secs > 300){
							//cout << "Última solución encontrada: " << fo << " restricciones infringidas, en " << elapsed_secs << " segs." << endl;
							//myfile_aux << "-----------------------------------------------------------------" << endl;
							//myfile_aux << "Solución de " << fo << " restricciones encontrada en " << elapsed_secs << " segs." << endl;
							//myfile_aux << "-----------------------------------------------------------------" << endl;
							//imprimirSolucion(solucion, opciones_por_clase, cant_opciones, myfile, myfile_aux);

							myfile_aux << fo << " " << elapsed_secs << endl;


							//ERROR INTENCIONAL PARA QUE PARE
							myfile.close();
							myfile_aux.close();
							cout << "Termino intencional" << endl << endl;
							cout << opciones_por_clase[10000][12];
						}

						else{

							if(fo == 0){
								cout << "Solución óptima de 0 restricciones infringidas encontrada." << endl;
								myfile_aux << "-----------------------------------------------------------------" << endl;
								myfile_aux << "Solución óptima de 0 restricciones encontrada en " << elapsed_secs << " segs." << endl;
								myfile_aux << "-----------------------------------------------------------------" << endl;
								imprimirSolucion(solucion, opciones_por_clase, cant_opciones, myfile, myfile_aux);	
							}

							else{
								cout << "Solución de " << fo << " restricciones infringidas encontrada en " << elapsed_secs << " segs." << endl;
								myfile_aux << fo << endl;
								myfile << (int) elapsed_secs  <<  endl;
							}
						}
					}
				}
			}

			//5. Si existe una variable por instanciar, sin valores posibles en su dominio, entonces retractar los efectos de la instanciación.
			else{
				//Si quedan valores por intentar en el dominio actual, volver al paso (2) (volver a instanciar).
				//Si no quedan valores:
				if(it == clases_disponibles.end()){ //cont == clases_disponibles.size()
					//Si i = 1, salir sin solución
					if(nivel == 1){
						cout << "No existe solución" << endl;
					}
					//Fallo (GBJ)
					else{
						retorno = matriz_conflictos[nivel];
					}
					//Si i > 1, decrementar i y volver al paso (2).
				}
			}
		}
	}
}