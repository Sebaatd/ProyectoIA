# Car Sequencing Problem - Forward Checking+GBJ
Proyecto de Inteligencia Artificial que busca resolver instancias del Car Sequencing Problem mediante la técnica de búsqueda completa Forward Checking y retornos guiados por GBJ. 

### Prerequisitos
El único prerequisito para ejecutar el programa es trabajar en una terminal con compilador g++ instalado.

### Estructura de los archivos
El proyecto contiene los archivos en la siguiente estructura:

    main.cpp            --> Código fuente 
    funciones.cpp       --> Archivo con las funciones a ejecutar por el main
    funciones.h         --> Header con las declaraciones de las funciones
    makefile            --> Archivo make para compilar y ejecutar el programa
    Instancias          --> Carpeta con los inputs a trabajar
    Resultados          --> Carpeta con los resultados de cada input

La existencia de ambas carpetas es fundamental para el funcionamiento del programa. Si no están, crearlas manualmente.

### Instalación

Simplemente clonar el repositorio en una carpeta local. Los inputs deben ser ubicados en la carpeta "Instancias". Por otra parte, los resultados del algoritmo son copiados en la carpeta "Resultados" con el mismo nombre del input.

### Ejecución

Para ejecutar el programa simplemente ingresar el comando "make" (sin comillas) dentro de la carpeta base del proyecto.

Una vez que el programa se inicia, consulta por el archivo de instancia que se quiere procesar. Los archivos deben estar en la carpeta Instancias. Cuando el programa solicite una instancia, se debe escribir el nombre dl archivo sin el ".txt".

```
>>Escriba el nombre de la instancia que desee ejecutar (sin el .txt): Problem 60-10
```

Mediante la ejecución se muestra en la pantalla cada vez que encuentra una solución completa. En caso contrario, se muestra la solución parcial que se ha construido hasta el momento.

### Salidas

Los resultados se guardan en la carpeta Resultados en un archivo con el mismo nombre de la instancia. En el caso de que se encuentren soluciones óptimas, todas las soluciones se mostrarán en ese archivo consecutivamente. En caso de que la instancia sea muy grande, el archivo se modifica dinamicamente de modo que el archivo guardara la última solución parcial encontrada (aquella que tenga la menor cantidad de restricciones violadas). 

Para cancelar la ejecución, apretar la combinación "ctrl+C".

### Comentarios Generales
Este proyecto es compartido con el propósito de informar. No se recomienda las reproducción total de éste debido a que fue construido bajo ciertos supuestos correspondiente al caso asignado. Por lo mismo, no se garantiza un correcto funcionamiento para todas las instancias, sobretodo las grandes o si se trabaja con técnicas de búsqueda incompleta. 
