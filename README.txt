Proyecto Inteligencia Artificial - INF295
Resolución Car Sequencing Problem mediante FC+GBJ
Sebastián Torrico - 201330061-8

									Estructura de los archivos
-------------------------------------------------------------------------------------------------
Revisar la estructura de los archivos. Deben estar los siguientes archivos y carpeta.
	-main.cpp
	-funciones.cpp
	-funciones.h
	-makefile
	-Instancias (Carpeta)
	-Resultados (Carpeta)

Si no está la carpeta Resultados, crearla. Es importante porque ahí se las soluciones.
-------------------------------------------------------------------------------------------------


											Ejecución
-------------------------------------------------------------------------------------------------
Para ejecutar el programa, simplemente escribir make en la carpeta principal del proyecto:

	>>make

Una vez que el programa se inicia, consulta por el archivo de instancia que se quiere procesar.
Los archivos deben estar en la carpeta Instancias.
Cuando el programa solicite una instancia, se debe escribir el nombre dl archivo sin el ".txt".
Por ejemplo:

	>>Escriba el nombre de la instancia que desee ejecutar (sin el .txt): Problem 60-10

-------------------------------------------------------------------------------------------------

											Salidas
-------------------------------------------------------------------------------------------------
Pueden ocurrir dos casos:
	1) Si la instancia es pequeña y tiene soluciones, se guardan las soluciones en la carpeta re-
	   sultados. 

	2) Si la instancia es grande y no se alcanza a encontrar una solución óptima, se guarda la 
	   solución en la carpeta resultados con el mismo nombre de la instancia. 
