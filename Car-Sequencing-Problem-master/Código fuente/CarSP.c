//README: Las clases de los autos deben comenzar desde cero
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

int EvaluarSolucion(int Opc, int * NroAutos, int * NroOpciones, int * NroClases, int **Solucion, int **NroMaxAutosPorOpcion,  int **TamBloqueAutosPorOpcion, int **NroDeAutosEnCadaClase, int ***Matriz);
int LeerArchivo(int * NroAutos, int * NroOpciones, int * NroClases, int **Solucion, int **NroMaxAutosPorOpcion,  int **TamBloqueAutosPorOpcion, int **NroDeAutosEnCadaClase, int ***Matriz);
double Greedy(int * NroAutos, int * NroOpciones, int * NroClases, int **Solucion, int **NroMaxAutosPorOpcion,  int **TamBloqueAutosPorOpcion, int **NroDeAutosEnCadaClase, int ***Matriz, int *ViolacionesGreedy);
void ImprimirSolucionFinal(int Filas, int Columnas, int *NroClases, int ***Matriz, int **Solucion, int a, int b, int *ViolacionesGreedy, double *TiempoGreedy, double *TiempoHC_MM);
int HC_MM(int * NroAutos, int * NroOpciones, int * NroClases, int **Solucion, int **NroMaxAutosPorOpcion,  int **TamBloqueAutosPorOpcion, int **NroDeAutosEnCadaClase, int ***Matriz, int *ViolacionesGreedy, double *TiempoGreedy, double *TiempoHC_MM);
void BuscarMejorDelVecindario(int **MejorDelVecindario, int * NroAutos, int * NroOpciones, int * NroClases, int **Solucion, int **NroMaxAutosPorOpcion,  int **TamBloqueAutosPorOpcion, int **NroDeAutosEnCadaClase, int ***Matriz);

int LeerArchivo(int * NroAutos, int * NroOpciones, int * NroClases, int **Solucion, int **NroMaxAutosPorOpcion,  int **TamBloqueAutosPorOpcion, int **NroDeAutosEnCadaClase, int ***Matriz)
{
	FILE *fichero;
	char texto[100];
	
	char *Autos, *Opciones, *Clases;
	int iMatriz;
	
	int NroAutosPorClase;	
	int i=1, j=0, k=0; //i para las lineas del archivo; j para contabilizar los caracteres en cada línea, k para moverse en arreglos
	char *palabra, *split;	//Variables auxiliares para el parseo del archivo

	fichero=fopen("csp.txt","r");
	if (fichero==NULL)
	{
		printf( "\nNo se puede abrir el archivo." );
	}
	else
	{
		
		fgets(texto,100,fichero);

		while (feof(fichero)==0)//Lectura del archivo hasta el final del mismo
		{

			if(i==1)//Si se lee la primera línea
			{
				//Se parsea la primera línea, almacenando valores de NroAutos, Opciones, Clases
				Autos = strtok ( texto, " " );
				Opciones = strtok ( NULL, " " );
				Clases = strtok ( NULL, " " );
				
				*NroAutos = atoi(Autos);
				*NroOpciones = atoi(Opciones);
				*NroClases = atoi(Clases);
				
				//Se crean los arreglos que almacenan: Número máximo de autos por cada opción
				//Tamaño de bloques que se evaluan por opción
				//Número de autos a crear por cada clase
				*NroMaxAutosPorOpcion = (int*)malloc(*NroOpciones*sizeof(int));				 
				*TamBloqueAutosPorOpcion = (int*)malloc(*NroOpciones*sizeof(int));
				*NroDeAutosEnCadaClase = (int*)malloc(*NroClases*sizeof(int));
				
				//Se inicializa eñ arreglo que almacenará la solución, es decir, la secuencia de autos
				*Solucion = (int*)malloc(*NroAutos*sizeof(int));
				while(j < *NroAutos)
				{		
					(*Solucion)[j]=0;
					j++;
				}	
				
				//Se inicializa la matriz que almacenará las opciones requeridas por cada clase de auto
				*Matriz = (int **)malloc(*NroClases*sizeof(int*)); 	
				for (iMatriz=0;iMatriz<*NroClases;iMatriz++) 
					(*Matriz)[iMatriz] = (int*)malloc(*NroOpciones*sizeof(int));  
	
			}
			else if(i==2)//Se lee la segunda línea
			{
				j=0;
				
				split=strtok(texto," ");
				
				while(j < *NroOpciones)
				{
					//Se parsea la linea y se almacena la cantidad máxima de autos por opción
					palabra=split;
					split=strtok(NULL," ");
					
					
					int num = atoi(palabra);
					(*NroMaxAutosPorOpcion)[j]=num;
					j++;
				}
			}
			else if(i==3)//Se lee la tercera linea
			{
				j=0;
				
				split=strtok(texto," ");
				

				while(j < *NroOpciones)
				{
					//Se parsea la linea y se almacena la cantidad bloques a evaluar por opción para revisar las restricciones
					palabra=split;
					split=strtok(NULL," ");
										
					(*TamBloqueAutosPorOpcion)[j]=atoi(palabra);
					j++;

				}

			}
			else if(i>3) //Se lee la cuarta linea del archivo
			{
				//Si el archivo tiene más líneas que las debidas, entonces el archivo ya tiene una solucion impresa
				if(i == *NroClases+4)
				{
					printf("\n\nEste archivo ya tiene solucion. Presione enter para verla.\n");
					getchar();
					return 1;
				}
				j=0;
				
				split=strtok(texto," ");	

				while(j < *NroOpciones + 2)
				{
					palabra=split;
					split=strtok(NULL," ");
					
					if(j==1) //se lee el numero de autos por clase
					{
						//Se almacena en el arreglo, la cantidad de autos a crear para la clase k
						NroAutosPorClase = atoi(palabra);
						(*NroDeAutosEnCadaClase)[k] = NroAutosPorClase; 
					}
					else if(j>1) //Se leen las otras columnas del archivo. Se indica si la clase requiere tal opción o no (1 o 0 respectivamente)
					{
						
						//en cada clase i se indica si se requiere(1) o no(0) la opción j
						(*Matriz)[i-4][j-2] = atoi(palabra);
						
					}	
					
					j++;
					
				}
			k++; //Se avanza a la siguiente clase k que se lee en el archivo
			}
			
			i++;//Indica que se está leyendo una línea más del archivo
			
			fgets(texto,100,fichero);
					
		}
		
		if (fclose(fichero)!=0)
			printf( "\nProblemas al cerrar el archivo" );
	}
	return 0;	
}

int EvaluarSolucion(int Opc, int * NroAutos, int * NroOpciones, int * NroClases, int **Solucion, int **NroMaxAutosPorOpcion,  int **TamBloqueAutosPorOpcion, int **NroDeAutosEnCadaClase, int ***Matriz)
{
	int **MatrizEvaluacion = NULL;
	int Filas;
	int Columnas = *NroOpciones;
	int i,j,k=0;
	int ContadorUnosPorBloque=0;
	int ContadorViolaciones=0;
	
	if(Opc != 0) //se llama a la función sin que el arreglo Solucion esté completo, es decir, desde la función Greedy
	{
		Filas = Opc;
	}
	else if(Opc == 0) //se llama la función cuando el arreglo Solucion esta lleno, es decir, desde la función HC_MM
	{
		Filas = * NroAutos;
	}
	
	//se crea la matriz que permitirá revisar las restricciones violadas
    MatrizEvaluacion = malloc(Filas*sizeof(int *));
    for(i = 0 ; i < Filas ; i++)
        MatrizEvaluacion[i] = malloc( Columnas*sizeof(int) );
	
	//Se llena la matriz a evaluar en base al arreglo Solucion que tiene el orden de la autos
	for(i=0; i<Filas; i++)
	{
		//copiar a MatrizEvaluacion la fila de la Matriz(que guarda las opciones por cada clase de auto), cuyo indice viene dado por Solucion(i)
		for(j=0; j<Columnas; j++)
		{
			MatrizEvaluacion[i][j] = (*Matriz)[(*Solucion)[i]][j];
		}		
	}
  
	//Se evalua por cada opción (columna), la cantidad de restricciones violadas
 	for(i=0; i<Columnas; i++)
	{
		//Revisar en cada columna, las restricciones p/q, con q el numero de bloques 
		//p la cantidad máxima permitida de unos en esos bloques
		for(j=0; j < Filas; j++)
		{				
					
			if(k < (*TamBloqueAutosPorOpcion)[i])
			{

				if(MatrizEvaluacion[j][i]==1)
				{
					ContadorUnosPorBloque++;
				}
				k++;
			}
			else //se ha alcanzado el numero de bloques máximo por opción, entonces se suman los unos de la cantidad de bloques respectiva, y se revisa la restricción
			{
		
				if(ContadorUnosPorBloque > (*NroMaxAutosPorOpcion)[i])
					ContadorViolaciones++;
		
				j--;
				k=0;
				ContadorUnosPorBloque=0;

			}
		}		
	}

	//liberar memoria
	for(i = 0 ; i < Filas ; i++)
        free(MatrizEvaluacion[i]);
    free(MatrizEvaluacion);

	return ContadorViolaciones;
		
}

double Greedy(int * NroAutos, int * NroOpciones, int * NroClases, int **Solucion, int **NroMaxAutosPorOpcion,  int **TamBloqueAutosPorOpcion, int **NroDeAutosEnCadaClase, int ***Matriz, int *ViolacionesGreedy)
{

	// variables utilizadas para medir tiempo de ejecución
	clock_t t_ini, t_fin;
	double secs;
	t_ini = clock();


	int i,j;
	int *NroAutosPorClaseAux = NULL;
	int CalidadAnterior=0;	//A menos valor, es mejor la calidad
	int CalidadActual=0;	//A menos valor, es mejor la calidad
	int Contador=0;
	//Variable auxiliar que permite contabilizar cuántos autos de cada clase quedan aún por colocar en la secuencia
	NroAutosPorClaseAux = (int*)malloc(*NroClases*sizeof(int));

	//Se copia la cantidad original de autos por crear para cada clase
	while(j < *NroClases)
	{		
		NroAutosPorClaseAux[j] = (*NroDeAutosEnCadaClase)[j];
		j++;
	}
	
	//llenar el arreglo tal que se alternen las clases en orden ascendente,
	//hasta que se ubiquen todos los autos que se requieran
	j=0;
	for(i=0; i < *NroAutos; i++)
	{
		
		if(j == *NroClases)
			j=0;
		
		//Si aun quedan autos de la clase j por colocar en la secuencia
		if(NroAutosPorClaseAux[j]!=0)
		{
			(*Solucion)[i] = j;
			
			//Se calcula la calidad
			CalidadActual = EvaluarSolucion(i+1, NroAutos, NroOpciones, NroClases, Solucion, NroMaxAutosPorOpcion, TamBloqueAutosPorOpcion, NroDeAutosEnCadaClase, Matriz);
			
			
			if(CalidadAnterior == CalidadActual) //Si las calidades son iguales, sirve la asignación que se está probando
			{

				//Se actualizan los datos
				CalidadAnterior = CalidadActual;
				
				//Diminuye la cantidad de autos que quedan por colocar de la clase j
				NroAutosPorClaseAux[j]--;
				
				//Si se ha dado la vuelta a la cantidad de clases existentes, se reinicia a 0, para comenzar de nuevo a probar las clases
				if(j < *NroClases)
					j++;
				else
					j=0;
							
			}
			else //No sirve la asignacion
			{
				//Contador permite saber cuantas veces ha cambiado la clase j con el fin de asignarl un auto a una casilla de la Solucion
				Contador++;
				
				if(Contador == *NroClases)//Si para una casilla de la Solucion, ya se han revisado todas las posibles clases de autos, sin encontrar una que tenga menor cantidad de restricciones violadas, se asigna de todas formas
				{

					CalidadAnterior = CalidadActual;
					NroAutosPorClaseAux[j]--;
					
					//Si se ha dado la vuelta a la cantidad de clases existentes, se reinicia a 0, para comenzar de nuevo a probar las clases
					if(j < *NroClases)
						j++;
					else
						j=0;
					
					Contador=0;
					
				}
				else//si no se han probado todas las posibles clases de auto para una casilla de la solucion
				{
					//Se quita la asignación que se realizó, para probar con otra clase
					(*Solucion)[i] = 0;
				
					if(j < *NroClases)
						j++;
					else
						j=0;
									
					i--;
				}				
			}

		}
		else
		{
			//Se revisa la misma casilla i de la Solucion, pero con una clase j más.
			j++;
			i--;
		}

	}
	free(NroAutosPorClaseAux);
	*ViolacionesGreedy = CalidadActual;
	
	t_fin = clock();

	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	
	return (secs * 1000.0);
}


void ImprimirSolucionFinal(int Filas, int Columnas, int *NroClases, int ***Matriz, int **Solucion, int a, int b, int *ViolacionesGreedy, double *TiempoGreedy, double *TiempoHC_MM)
{
	int i,j;
	int **MatrizEvaluacion = NULL;

	
	FILE *fp;
 
 	fp = fopen("csp.txt", "a");
 	
	//imprime la calidad de la Solucion encontrada por Greedy y su tiempo de ejecucion
	printf("\nCantidad de restricciones violadas (solucion Greedy): %d\nTiempo de ejecucion: %g milisegundos", *ViolacionesGreedy, *TiempoGreedy);
	fprintf(fp, "%s", "\nCantidad de restricciones violadas (solucion Greedy): ");
	fprintf(fp, "%d", *ViolacionesGreedy);	
	fprintf(fp, "%s", "\nTiempo de ejecucion :");
	fprintf(fp, "%g", *TiempoGreedy);
	fprintf(fp, "%s", " milisegundos");	
	//imprime la calidad de la Solucion encontrada por HC_MM y su tiempo de ejecucion
	printf("\n\nCantidad de restricciones violadas (solucion final): %d\nTiempo de ejecucion: %g milisegundos", b, *TiempoHC_MM);
	fprintf(fp, "%s", "\nCantidad de restricciones violadas (solucion final): ");
	fprintf(fp, "%d", b);
	fprintf(fp, "%s", "\nTiempo de ejecucion :");
	fprintf(fp, "%g", *TiempoHC_MM);
	fprintf(fp, "%s", " milisegundos");	
	//imprime la cantidad de iteraciones
	printf("\n\nCantidad de iteraciones: %d", a);
	fprintf(fp, "%s", "\nCantidad de iteraciones: ");
	fprintf(fp, "%d", a);
	
	
	
	//se crea la matriz
    MatrizEvaluacion = malloc(Filas*sizeof(int *));
    for(i = 0 ; i < Filas ; i++)
        MatrizEvaluacion[i] = malloc( Columnas*sizeof(int) );
	
	//Se llena la matriz a evaluar en base al arreglo Solucion que tiene el orden de la autos
	for(i=0; i<Filas; i++)
	{
		//copiar a MatrizEvaluacion la fila de la Matriz, cuyo indice viene dado por Solucion(i)
		for(j=0; j<Columnas; j++)
		{
			MatrizEvaluacion[i][j] = (*Matriz)[(*Solucion)[i]][j];
		}		
	}
	
	//imprime encabezado de la solucion
	printf("\n---------------------------------------\n");
	fprintf(fp, "%s", "\n---------------------------------------\n");
	printf("Nro. Auto	Clase	Opciones\n");
	fprintf(fp, "%s", "Nro. Auto   Clase	Opciones\n");
	printf("---------------------------------------\n");
	fprintf(fp, "%s", "---------------------------------------\n");
	
	//Se imprime la secuencia de Autos con sus respectivas opciones
 	for(i=0; i<Filas; i++)
	{
		if(j==Columnas)
		{	
			printf("\n");
			fprintf(fp, "%s", "\n");
		}
		
		
		printf("\t%d\t[%d]\t",i+1, (*Solucion)[i]);
		fprintf(fp, "%s", "\t");
		fprintf(fp, "%d", i+1);
		fprintf(fp, "%s", "\t");
		fprintf(fp, "%d", (*Solucion)[i]);
		fprintf(fp, "%s", "\t");
						
		for(j=0; j<Columnas; j++)
		{
			printf("[%d]", MatrizEvaluacion[i][j]);
			fprintf(fp, "%s", "[");
			fprintf(fp, "%d", MatrizEvaluacion[i][j]);
			fprintf(fp, "%s", "]");
		}
	}
	
 
	if (fclose(fp)!=0)
		printf( "\nProblemas al cerrar el archivo" );

	//se libera la memoria
	for(i = 0 ; i < Filas ; i++)
        free(MatrizEvaluacion[i]);
    free(MatrizEvaluacion);
    
}

void BuscarMejorDelVecindario(int **MejorDelVecindario, int * NroAutos, int * NroOpciones, int * NroClases, int **Solucion, int **NroMaxAutosPorOpcion,  int **TamBloqueAutosPorOpcion, int **NroDeAutosEnCadaClase, int ***Matriz)
{
	int i=0,j=0;
	int Aleatorio=0;
	int *SolucionAux = NULL;
	int MejorNumViolaciones;
	int ViolacionesActuales;
	
	//Variable auxiliar que almacena la Solucion candidata con mejor Calidad hasta el momento
	SolucionAux = (int*)malloc(*NroAutos*sizeof(int));
	
	//Inicilamente la mejor Solucion es la que se recibe al llamar a la función, entonces, se copian sus datos
	while(i < *NroAutos)
	{
		(*MejorDelVecindario)[i] = (*Solucion)[i];
		i++;
	}
	//Se calcula la calidad, a menos valor, mejora es la calidad, pues se violan menos restricciones
	MejorNumViolaciones = EvaluarSolucion(0, NroAutos, NroOpciones, NroClases, Solucion, NroMaxAutosPorOpcion, TamBloqueAutosPorOpcion, NroDeAutosEnCadaClase, Matriz);

	//Semilla que se utilizará para conseguir un número aleatorio
	srand(time(NULL));

	//tomar valor aleatorio y en base a éste, se hace swap en la posición, en la SolucionAux
	for(i=0; i < *NroAutos; i++)
	{
		//Conseguir número aleatorio entre 0 y el Numero de autos a secuenciar
		Aleatorio = rand() % *NroAutos;
		
		//Se recorre el arreglo auxiliar para hacer el movimiento y generar una nueva solución
		for(j=0; j < *NroAutos; j++)
		{		
			if(i==j)
				SolucionAux[j] = (*Solucion)[Aleatorio];
			else if(j==Aleatorio)
				SolucionAux[j] = (*Solucion)[i];
			else
				SolucionAux[j] = (*Solucion)[j];		
		}
	
		//Se calcula la calidad de la nueva solución
		ViolacionesActuales = EvaluarSolucion(0, NroAutos, NroOpciones, NroClases, &SolucionAux, NroMaxAutosPorOpcion, TamBloqueAutosPorOpcion, NroDeAutosEnCadaClase, Matriz);
		
		if(ViolacionesActuales <= MejorNumViolaciones) 
		{
			
			MejorNumViolaciones = ViolacionesActuales;
			j=0;
			while(j < *NroAutos)
			{
				(*MejorDelVecindario)[j] = SolucionAux[j];
				j++;
			}
		}			
		
	}
free(SolucionAux);	
}

int HC_MM(int * NroAutos, int * NroOpciones, int * NroClases, int **Solucion, int **NroMaxAutosPorOpcion,  int **TamBloqueAutosPorOpcion, int **NroDeAutosEnCadaClase, int ***Matriz, int *ViolacionesGreedy, double *TiempoGreedy, double *TiempoHC_MM)
{
	// variables utilizadas para medir tiempo de ejecución
	clock_t t_ini, t_fin;
	double secs;
	t_ini = clock();


	//La estructura básica del algoritmo es la siguiente
	
	//local<-False
	//Sc <- Greedy
	//Repeat
		//select Sn the best quality point in Vecindario
		//if Evaluar(Sn) is better than Evaluar(Sc)
			//Sc<-Sn
		//else
			//local<-True
	//Until local
	
	int Local=0;
	int ViolacionesNuevaSol, ViolacionesMejorSol;
	int i;
	int Iteracion=0;
	int *MejorDelVecindario = NULL; //Arreglo que tendrá el mejor vecino
	MejorDelVecindario = (int*)malloc(*NroAutos*sizeof(int));	
	
	//Greedy obtiene la sol inicial	
	*TiempoGreedy = Greedy(NroAutos, NroOpciones, NroClases, Solucion, NroMaxAutosPorOpcion, TamBloqueAutosPorOpcion, NroDeAutosEnCadaClase, Matriz, ViolacionesGreedy);
		
	//Se empiezan los movimientos para mejorar la solución
	while(!Local)
	{		
		BuscarMejorDelVecindario(&MejorDelVecindario, NroAutos, NroOpciones, NroClases, Solucion, NroMaxAutosPorOpcion, TamBloqueAutosPorOpcion, NroDeAutosEnCadaClase, Matriz);
		
		//Se calculan las calidades de la mejor Solucion y de la nueva, obtenida desde el vecindario generado
		ViolacionesNuevaSol = EvaluarSolucion(0, NroAutos, NroOpciones, NroClases, &MejorDelVecindario, NroMaxAutosPorOpcion, TamBloqueAutosPorOpcion, NroDeAutosEnCadaClase, Matriz);
		ViolacionesMejorSol = EvaluarSolucion(0, NroAutos, NroOpciones, NroClases, Solucion, NroMaxAutosPorOpcion, TamBloqueAutosPorOpcion, NroDeAutosEnCadaClase, Matriz);
		
		//Si la cantidad de violaciones de la Nueva solucion obtenida del vecindario es <= a la cantidad de soluciones de la Mejos Solucion
		if(ViolacionesNuevaSol < ViolacionesMejorSol)
		{
			
			i=0;
			//Se actualiza la solución
			while(i < *NroAutos)
			{
				(*Solucion)[i] = MejorDelVecindario[i];
				i++;
			}
		}
		else
			Local=1;
		
		//variable utilizada para contabilizar iteraciones realizadas por el algoritmo
		Iteracion++;

	}
	free(MejorDelVecindario);

	t_fin = clock();
	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	secs = secs * 1000.0;
	*TiempoHC_MM = secs;
	
	return Iteracion;
}

void MostrarArchivo(void)
{
	FILE *archivo;
	char caracter;

	archivo = fopen("csp.txt","r");

	if (archivo == NULL)
		printf("\nError de apertura del archivo. \n\n");
	else
	{

		while (feof(archivo) == 0)
		{
			caracter = fgetc(archivo);
			printf("%c",caracter);
		}
	}
	fclose(archivo);
}

int main()
{
	int *Solucion = NULL;
	int *NroMaxAutosPorOpcion = NULL;
	int *TamBloqueAutosPorOpcion = NULL;
	int *NroDeAutosEnCadaClase = NULL;
	int i,j;
	
	int **Matriz = NULL;
	int NroAutos, NroOpciones, NroClases, ViolacionesGreedy;
	double TiempoGreedy, TiempoHC_MM;

	printf("\nLeyendo el archivo");
	//leer el archivo y llenar los arreglos con la información correspondiente
	i = LeerArchivo(&NroAutos, &NroOpciones, &NroClases, &Solucion, &NroMaxAutosPorOpcion, &TamBloqueAutosPorOpcion, &NroDeAutosEnCadaClase, &Matriz);
	
	//Si la lectura del archivo devuelve 1, entonce el archivo ya tiene una solucion impresa
	if(i==1)
	{
		MostrarArchivo();
		return 0;
	}
	printf("\nSe ha iniciado la ejecucion\n\n");
	//iniciar la busqueda local y evaluar calidad de dicha solución
	i = HC_MM(&NroAutos, &NroOpciones, &NroClases, &Solucion, &NroMaxAutosPorOpcion, &TamBloqueAutosPorOpcion, &NroDeAutosEnCadaClase, &Matriz, &ViolacionesGreedy, &TiempoGreedy, &TiempoHC_MM);
	j = EvaluarSolucion(0, &NroAutos, &NroOpciones, &NroClases, &Solucion, &NroMaxAutosPorOpcion, &TamBloqueAutosPorOpcion, &NroDeAutosEnCadaClase, &Matriz);
	
	//Se imprime la solución por consola y a un archivo
	ImprimirSolucionFinal(NroAutos, NroOpciones, &NroClases, &Matriz, &Solucion, i, j, &ViolacionesGreedy, &TiempoGreedy, &TiempoHC_MM);
	
	//Liberar memoria
	for(i = 0 ; i < NroOpciones ; i++)
        free(Matriz[i]);
    free(Matriz);
       
	free(Solucion);
	free(NroMaxAutosPorOpcion);
	free(TamBloqueAutosPorOpcion);
	free(NroDeAutosEnCadaClase);
	
	 return 0;
}
