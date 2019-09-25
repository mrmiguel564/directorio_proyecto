Taller 01: 
==========
Contar en forma paralela/concurrente las apariciones de un caracter en un arreglo, utilizando threads en C++14

Objetivos:
==========

Crear un programa que llene de un arreglo de letras aleatorias en forma secuencial y que luego cuente en forma paralela/concurrente las apariciones de una letra determinada. 

Forma de uso:
=============

./contar -n <nro> -t <nro>  -l <letra> [-h]

Parámetros:
	-n   : tamaño del arreglo.
	-t   : número de threads.
	-l   : letra a buscar
	[-h] : muestra la ayuda de uso y termina.
 
Ejemplo de uso:
===============

1) Crea un arreglo de 1000000 letras. Busca la letra 'a' con 4 threads. 
   
./contar -n 1000000 -t 4 -l a

2) Muestra la ayuda y termina

./contar -h
./contar


Trabajo a realizar
==================
1) A partir del código entregado, implementar un programa que llene un arreglo de letras tamaño N (en forma secuencial) y que luego busque una letra determinada utilizando t threads.

Observaciones
=============

1) El trabajo deberá utilizar C++14, bajo linux. El proyecto de compilará con el comando make y la secuencia de revisión será:

$cd <directorio_proyecto>
<...si el directorio no tiene la misma estructura que la que se entregó, la calificación será 1.0>
$more README
<...Contenido del archivo según indicaciones de más abajo...>
<...Si no existe este archivo, la calificación es 1.0> 
$make clean
$ make
<...Salida del proceso de compilación, sin ningún tipo de warnings y totalmente exitosa>
<...Si no es exitosa, la calificación es 1.0. Si tiene warnings, nota máxima 5.0> 
$ ./contar -n 1000 -t 2 -l a
<...Salida del programa... sin fallos>
<...Si el programa falla, o no hace lo solicitado, la calificación será 1.0>

2) Para la compilación, el archivo Makefile NO SE DEBE modificar. 

3) La tarea será revisada por el ayudante de la asignatura en forma independiente, y luego se coordinará un horario para la interrogación respectiva.

4) Trabajo Grupal (2 personas).

Forma de entrega
================

Cada grupo deberá subir al aula virtual un archivo tar.gz con su proyecto, el que debe tener la misma estructura de directorios que el entregado por el profesor.

En el archivo README debe indica claramente: Integrantes (Nombre, Correo) y una breve explicación de cómo se solucionó el problema. Este archivo debe ser texto plano.

Si usted no cumple con alguna de estas indicaciones, no se revisará su tarea y su calificación será 1.0.










