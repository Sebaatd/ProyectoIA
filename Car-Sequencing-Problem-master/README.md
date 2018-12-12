# Car Sequencing Problem

Proyecto de ILI295 - Inteligencia artificial, UTFSM Campus Santiago, San Joaquín 2014-1.
Marcela Vidal Ramírez

El Car Sequencing Problem es una variante del modelamiento de secuenciación en líneas de montaje de modelos mixtos, utilizada en sistemas reales de fabricación de vehículos. En esta implementación en lenguaje C, de ha desarrollado especícamente una heurística Greedy más una de búsqueda local. Su importancia radica en que la solución de este problema se encarga de buscar una secuencia de fabricación de automóviles que optimice el proceso productivo, de tal forma que se respeten ciertas reglas referente al número de veces que cada producto puede ser asignado en tramos de este ordenamiento, y así, optimizar el 
flujo de materiales y el ensamblado de las unidades sin sobrecargar las áreas de trabajo.

## Descripción del algoritmo

La técnica implementada para la resolución del problema es Hill-Climbing Mejor Mejora (HC-MM), un algoritmo iterativo que inicia con una solución que puede  ser obtenida de diversas formas, y que luego intenta encontrar una mejor, variando un único elemento de la respuesta temporal, para crear un vecindario de posibles soluciones. Si dentro del vecindario hay una solución de mejor calidad, lo que viene determinado por la cantidad de restricciones que se violan con esta nueva posibilidad, se realiza otro cambio a esta nueva solución, repitiendo el proceso hasta que ya no sea posible encontrar una mejora, lo que se conoce como óptimo local.

## Características del algoritmo

+ Lenguaje de programación C.
+ Uso de memoria dinámica.
+ Entrada: Archivo de texto plano csp.txt que incluye: Nro Autos, Nro Opciones (Ventanas, tapizado de cuero, aire acondicionado, etc), Nro Clases (Modelos de los vehículos diseñados).
+ Salida: csp.txt con la solución. 


#### Ejemplo de archivo de entrada
```
200 5 25
1 2 1 2 1 
2 3 3 5 5 
0 3 0 0 0 0 1
1 12 0 0 0 1 0
2 2 0 0 0 1 1
3 7 0 0 1 0 0
4 1 0 0 1 0 1
5 6 0 0 1 1 0
6 38 0 1 0 0 0
7 3 0 1 0 0 1
8 17 0 1 0 1 0
9 15 0 1 1 0 0
10 4 0 1 1 0 1
11 2 0 1 1 1 1
12 5 1 0 0 0 1
13 13 1 0 0 1 0
14 1 1 0 0 1 1
15 13 1 0 1 0 0
16 2 1 0 1 0 1
17 5 1 0 1 1 0
18 1 1 0 1 1 1
19 22 1 1 0 0 0
20 5 1 1 0 0 1
21 13 1 1 0 1 0
22 3 1 1 0 1 1
23 4 1 1 1 0 1
24 3 1 1 1 1 0
```

*Descripción*
+ Primera línea: No de autos, No de opciones, No de clases.
+ Segunda línea: Restricciones a cumplir por la línea de producción, donde cada número corresponde a la máxima cantidad de vehículos en un bloque, que puede tener esa opción.
+ Tercera línea: Por cada opción, se indica el tamaño del bloque de vehículos.
+ Siguientes líneas: Número de la clase - vehículos por clase - 0 ó 1 para indicar si la clase requiere instalar tal opción. 


#### Ejemplo de archivo de salida
```
Cantidad de restricciones violadas (solucion Greedy): 85
Tiempo de ejecucion :113.126 milisegundos
Cantidad de restricciones violadas (solucion final): 42
Tiempo de ejecucion :455.383 milisegundos
Cantidad de iteraciones: 29
---------------------------------------
  Auto Clase	Opciones
---------------------------------------

	1	24	[1][1][1][1][0]
	2	8	[0][1][0][1][0]
	3	1	[0][0][0][1][0]
	4	9	[0][1][1][0][0]
	5	6	[0][1][0][0][0]
	6	12	[1][0][0][0][1]
	7	6	[0][1][0][0][0]
	8	5	[0][0][1][1][0]
	9	6	[0][1][0][0][0]
	10	7	[0][1][0][0][1]
	11	11	[0][1][1][1][1]
	12	19	[1][1][0][0][0]
	13	23	[1][1][1][0][1]
	14	1	[0][0][0][1][0]
	15	12	[1][0][0][0][1]
	16	8	[0][1][0][1][0]
	17	4	[0][0][1][0][1]
	18	19	[1][1][0][0][0]
	19	6	[0][1][0][0][0]
	20	15	[1][0][1][0][0]
	21	20	[1][1][0][0][1]
	22	8	[0][1][0][1][0]
	23	0	[0][0][0][0][1]
	24	1	[0][0][0][1][0]
	25	8	[0][1][0][1][0]
	26	3	[0][0][1][0][0]
	27	5	[0][0][1][1][0]
	28	8	[0][1][0][1][0]
	29	12	[1][0][0][0][1]
	30	10	[0][1][1][0][1]
	31	9	[0][1][1][0][0]
	32	17	[1][0][1][1][0]
	33	6	[0][1][0][0][0]
	34	17	[1][0][1][1][0]
	35	20	[1][1][0][0][1]
	36	23	[1][1][1][0][1]
	37	13	[1][0][0][1][0]
	38	6	[0][1][0][0][0]
	39	22	[1][1][0][1][1]
	40	10	[0][1][1][0][1]
	41	11	[0][1][1][1][1]
	42	16	[1][0][1][0][1]
	43	21	[1][1][0][1][0]
	44	1	[0][0][0][1][0]
	45	8	[0][1][0][1][0]
	46	19	[1][1][0][0][0]
	47	17	[1][0][1][1][0]
	48	22	[1][1][0][1][1]
	49	19	[1][1][0][0][0]
	50	5	[0][0][1][1][0]
	51	6	[0][1][0][0][0]
	52	12	[1][0][0][0][1]
	53	6	[0][1][0][0][0]
	54	20	[1][1][0][0][1]
	55	23	[1][1][1][0][1]
	56	1	[0][0][0][1][0]
	57	8	[0][1][0][1][0]
	58	15	[1][0][1][0][0]
	59	21	[1][1][0][1][0]
	60	6	[0][1][0][0][0]
	61	5	[0][0][1][1][0]
	62	12	[1][0][0][0][1]
	63	21	[1][1][0][1][0]
	64	6	[0][1][0][0][0]
	65	17	[1][0][1][1][0]
	66	1	[0][0][0][1][0]
	67	13	[1][0][0][1][0]
	68	6	[0][1][0][0][0]
	69	13	[1][0][0][1][0]
	70	6	[0][1][0][0][0]
	71	5	[0][0][1][1][0]
	72	9	[0][1][1][0][0]
	73	7	[0][1][0][0][1]
	74	13	[1][0][0][1][0]
	75	9	[0][1][1][0][0]
	76	24	[1][1][1][1][0]
	77	13	[1][0][0][1][0]
	78	9	[0][1][1][0][0]
	79	15	[1][0][1][0][0]
	80	7	[0][1][0][0][1]
	81	1	[0][0][0][1][0]
	82	21	[1][1][0][1][0]
	83	15	[1][0][1][0][0]
	84	9	[0][1][1][0][0]
	85	21	[1][1][0][1][0]
	86	8	[0][1][0][1][0]
	87	9	[0][1][1][0][0]
	88	13	[1][0][0][1][0]
	89	3	[0][0][1][0][0]
	90	10	[0][1][1][0][1]
	91	19	[1][1][0][0][0]
	92	8	[0][1][0][1][0]
	93	6	[0][1][0][0][0]
	94	5	[0][0][1][1][0]
	95	6	[0][1][0][0][0]
	96	2	[0][0][0][1][1]
	97	9	[0][1][1][0][0]
	98	13	[1][0][0][1][0]
	99	19	[1][1][0][0][0]
	100	24	[1][1][1][1][0]
	101	6	[0][1][0][0][0]
	102	13	[1][0][0][1][0]
	103	20	[1][1][0][0][1]
	104	1	[0][0][0][1][0]
	105	8	[0][1][0][1][0]
	106	15	[1][0][1][0][0]
	107	19	[1][1][0][0][0]
	108	0	[0][0][0][0][1]
	109	9	[0][1][1][0][0]
	110	21	[1][1][0][1][0]
	111	9	[0][1][1][0][0]
	112	21	[1][1][0][1][0]
	113	9	[0][1][1][0][0]
	114	21	[1][1][0][1][0]
	115	9	[0][1][1][0][0]
	116	21	[1][1][0][1][0]
	117	9	[0][1][1][0][0]
	118	21	[1][1][0][1][0]
	119	9	[0][1][1][0][0]
	120	6	[0][1][0][0][0]
	121	1	[0][0][0][1][0]
	122	10	[0][1][1][0][1]
	123	1	[0][0][0][1][0]
	124	19	[1][1][0][0][0]
	125	20	[1][1][0][0][1]
	126	6	[0][1][0][0][0]
	127	3	[0][0][1][0][0]
	128	6	[0][1][0][0][0]
	129	6	[0][1][0][0][0]
	130	13	[1][0][0][1][0]
	131	13	[1][0][0][1][0]
	132	15	[1][0][1][0][0]
	133	19	[1][1][0][0][0]
	134	21	[1][1][0][1][0]
	135	9	[0][1][1][0][0]
	136	13	[1][0][0][1][0]
	137	15	[1][0][1][0][0]
	138	19	[1][1][0][0][0]
	139	3	[0][0][1][0][0]
	140	19	[1][1][0][0][0]
	141	6	[0][1][0][0][0]
	142	17	[1][0][1][1][0]
	143	6	[0][1][0][0][0]
	144	13	[1][0][0][1][0]
	145	8	[0][1][0][1][0]
	146	8	[0][1][0][1][0]
	147	8	[0][1][0][1][0]
	148	13	[1][0][0][1][0]
	149	1	[0][0][0][1][0]
	150	21	[1][1][0][1][0]
	151	2	[0][0][0][1][1]
	152	15	[1][0][1][0][0]
	153	19	[1][1][0][0][0]
	154	6	[0][1][0][0][0]
	155	8	[0][1][0][1][0]
	156	15	[1][0][1][0][0]
	157	19	[1][1][0][0][0]
	158	6	[0][1][0][0][0]
	159	8	[0][1][0][1][0]
	160	15	[1][0][1][0][0]
	161	19	[1][1][0][0][0]
	162	8	[0][1][0][1][0]
	163	1	[0][0][0][1][0]
	164	15	[1][0][1][0][0]
	165	19	[1][1][0][0][0]
	166	3	[0][0][1][0][0]
	167	8	[0][1][0][1][0]
	168	22	[1][1][0][1][1]
	169	18	[1][0][1][1][1]
	170	19	[1][1][0][0][0]
	171	6	[0][1][0][0][0]
	172	15	[1][0][1][0][0]
	173	19	[1][1][0][0][0]
	174	6	[0][1][0][0][0]
	175	15	[1][0][1][0][0]
	176	19	[1][1][0][0][0]
	177	6	[0][1][0][0][0]
	178	19	[1][1][0][0][0]
	179	6	[0][1][0][0][0]
	180	19	[1][1][0][0][0]
	181	3	[0][0][1][0][0]
	182	19	[1][1][0][0][0]
	183	6	[0][1][0][0][0]
	184	3	[0][0][1][0][0]
	185	6	[0][1][0][0][0]
	186	16	[1][0][1][0][1]
	187	6	[0][1][0][0][0]
	188	21	[1][1][0][1][0]
	189	6	[0][1][0][0][0]
	190	6	[0][1][0][0][0]
	191	6	[0][1][0][0][0]
	192	6	[0][1][0][0][0]
	193	14	[1][0][0][1][1]
	194	0	[0][0][0][0][1]
	195	6	[0][1][0][0][0]
	196	23	[1][1][1][0][1]
	197	6	[0][1][0][0][0]
	198	6	[0][1][0][0][0]
	199	19	[1][1][0][0][0]
	200	6	[0][1][0][0][0]
```

## Ejecutar el programa

###### Antes de compilar:

1. Copiar los archivos del directorio "Codigo Fuente" (CarSP.c, csp.txt, makefile).
2. Es importante que el nombre del archivo que contiene la instancia debe ser "csp.txt".

###### Para compilar (con gcc) y ejecutar el programa:

1. Abrir el terminal y situarse en el directorio donde se han copiado los archivos. Por ej: $ cd Escritorio/Proyectos/
2. Escribir "make" sin comillas.
3. Se muestra por pantalla la solución de la instancia, y también se agrega al mismo archivo desde donde se lee.

### Excepción de responsabilidades

Este proyecto se presenta con el único propóstito de compartir información, por lo que no se garantiza su correcto funcionamiento bajo ninguna cinrcunstancia. Se puede copiar y editar, total o parcialmente, respetando la creación de la autora, enlazando la página principal del proyecto. 

