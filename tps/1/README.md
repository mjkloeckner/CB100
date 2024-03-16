# Trabajo Practico I

Este es el primer trabajo practico de la materia Algoritmos y Estructura de
Datos de la FIUBA.

El trabajo consiste en una aplicación de consola desarrollada puramente
con lenguaje C++. La aplicación calcula números primos y los imprime en un
archivo de texto `primos.txt`. El limite de números a analizar por la
aplicación queda definido por el usuario en el código fuente, en concreto en el
archivo `main.cpp` y con la variable `MAXIMO`:

```c++
const unsigned int MAXIMO = 50000;
```

Hay que tener en cuenta que cuanto mayor sea ese limite mayor tardará la
aplicación en finalizar.

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

En el caso de windows recomiendo configurar
[WSL](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux) puede hacerlo
siguiendo la [guia oficial de
Microsoft](https://learn.microsoft.com/en-us/windows/wsl/install). Luego
seguir los pasos para los sistemas basados en UNIX.

## LICENSE

[MIT](https://opensource.org/license/mit)
