# Algoritmos y Estructuras de Datos

En este repositorio usted encontrara mis notas y resoluciones de la materia
Algoritmos y Estructuras de Datos (CB100) cátedra Schmidt. Esta materia es
equivalente a Algoritmos y Programación 2 en planes de estudios anteriores al
Plan 2020

## Códigos de Escape ANSI

Los códigos de escape ANSI sirven para controlar el comportamiento de una
terminal (la cual soporte códigos de escape ANSI). Utilizando estos códigos se
puede controlar el color de impresión, la posición del cursor, entre otras
cosas.

### Links Útiles

* [wikipedia: ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code)
* [ANSI Escape Sequences Cheatsheet](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797)

## Librería Termios

> **NOTA**: La cátedra no recomienda utilizar librerías de C en C++

La librería `termios.h` permite cambiar la configuración de las interfaces de
entrada y salida de la terminal. Esta librería en conjunto con los codigos de
escape ANSI, resultan útiles en casos en los que se quiera hacer un programa
interactivo como el que se muestra a continuación:

![Termios Example](https://github.com/mjkloeckner/CB100/assets/64109770/57ef45a4-e7cc-4a01-af84-4b30eb3c48b3)

La aplicación anterior corresponde con la [solución del ejercicio
11](https://github.com/mjkloeckner/CB100/blob/main/solutions/ej11.cpp) el cual
pide formar un menú de 4 opciones

## Recursos Recomendados

* [Standard C++ Library reference](https://cplusplus.com/reference/)
* [C++ reference](https://en.cppreference.com )
* [Deitel & Deitel - C how to program with an Introduction to C++](https://deitel.com/c-how-to-program-8-e/)

### Recursos Recomendados Sobre `termios.h` y Manejo de Señales

* [termios(3) — Linux manual page](https://man7.org/linux/man-pages/man3/tcsetattr.3.html)
* [Terminal Input Modes](https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_352.html)
* [Setting Terminal Modes Properly](https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_351.html#SEC360)
* [Serial Programming/termios](https://en.wikibooks.org/wiki/Serial_Programming/termios)
* [Characters that Cause Signals](https://www.gnu.org/software/libc/manual/html_node/Signal-Characters.html)
* [Install a Signal Handler ](https://www.csl.mtu.edu/cs4411.ck/www/NOTES/signal/install.html)
