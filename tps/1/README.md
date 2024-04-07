# Trabajo Practico I

Este es el primer trabajo practico de la materia Algoritmos y Estructura de
Datos de la
[FIUBA](https://en.wikipedia.org/wiki/Faculty_of_Engineering,_University_of_Buenos_Aires) curso Schmidt

El trabajo consiste en una aplicación de consola desarrollada puramente
con lenguaje C++. La aplicación busca números primos y aquellos que encuentra
los imprime en un archivo de texto llamado `primos.txt` localizado en el
directorio desde donde se ejecuta la aplicación. El limite de números a analizar
por la aplicación queda definido por el usuario en el archivo `primos.cpp` con la
variable `MAXIMO`:

```c++
const unsigned int MAXIMO = 50000;
```

Hay que tener en cuenta que cuanto mayor sea éste límite mayor tardará la
aplicación en finalizar su ejecución

## Quick Start

### Sistemas basados en UNIX

Compile el código con el programa `make`

```sh
$ make
```

Luego puede ejecutar la aplicación de la siguiente manera

```sh
$ ./primos
```

### Windows

En el caso de windows puede configurar
[WSL](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux), para hacerlo
puede seguir la [guia oficial de
Microsoft](https://learn.microsoft.com/en-us/windows/wsl/install). Una vez
configurado WSL siga los pasos para los sistemas basados en UNIX

De manera análoga puede compilar la aplicación directamente, sin la necesidad de
utilizar la herramienta `make`, para eso debe tener un compilador de C++
instalado, luego compile el archivo `primos.cpp` con el siguiente comando:

```
$ g++ -Wall -Wshadow -pedantic -ansi -std=c++98 -O3 primos.cpp -o primos
```

## LICENSE

[MIT](https://opensource.org/license/mit)
