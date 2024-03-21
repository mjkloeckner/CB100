# Clase 20-03-24

## Punteros en C++

Los punteros, al igual que en C, son variables que almacenan una dirección en
memoria. Para que un puntero funcione debe ser capaz de almacenar un **Word**,
ya que ese es el tamaño de una dirección de memoria de una computadora.

### Sintaxis

Para imprimir la dirección de memoria de una variable se utiliza `&`

```c++
int a = 1;
std::cout << &a << std::end; // Imprime la dirección de memoria de `a`
```

Para declarar un puntero a un tipo de dato se utiliza el asterisco `*` luego del
tipo de dato.

```c++
int *p; // Se declara un puntero a un entero
```

Para asignar la dirección de memoria de una variable a un puntero se utiliza el
operador `=`

```c++
int a = 1;
int *p = &a; // p es un puntero que apunta a la variable a
```

Para imprimir el contenido al que apunta un puntero hay que *desreferenciaro*,
para eso se utiliza el operador asterisco `*`

```c++
int a = 1;
int *p = &a;
std::cout << *p << std::endl; // Imprime el contenido de la variable
                              // que apunta p
```

### Punteros genéricos

Los punteros genéricos son punteros los cuales no tienen un tipo de dato
asignado. Todos los punteros a diferentes tipos de datos ocupan la misma
cantidad de memoria, un **Word**.

```c++
void *generic_pointer;
```

La ventaja de los punteros genéricos es que se puede usar un mismo puntero para
manipular diferentes tipos de datos, la desventaja es que para acceder al dato
apuntado por el puntero es necesario conocer el tamaño del tipo de dato al cual
apunta el puntero, ya que si se desreferencia un puntero genérico se produce un
error **grave** en el programa.

> No se puede desreferencia un puntero genérico a menos que se conozca el tipo
> de dato

```c++
int a = 1;
void *p = &a;

std::cout << *(int *)p << std::endl; // "cast" al puntero `p` a tipo int para
                                     // acceder a la memoria que apunta
```

## Memoria Dinámica

A diferencia de la memoria estática, que se localiza en el **stack**, la memoria
dinámica se localiza en el **heap**. Al finalizar el programa el stack vuelve
a su posición de origen y se eliminan todas las variables almacenadas allí,
liberando la memoria utilizada, el heap en cambio, se debe liberar por el
usuario antes de finalizado el programa, de lo contrario se produce una fuga de
memoria, un error típico y grave en lenguajes como C y C++.

El lenguaje C++ ofrece dos palabra reservadas para manipular el heap: `new` la
cual permite crear una nueva variable, y `delete` la cual permite eliminar una
variable, y por consiguiente liberar la memoria utilizada por dicha variable

### Sintaxis

La palabra `new` puede ser utilizada para almacenar memoria en el `heap`, la
memoria a almacenar puede ser utilizada para variables de tipo primitivo como
`int`, o variables más complejas como estructuras definidas por el usuario.

```c++
int *p = new int;
*p = 10;
std::cout << *p << std::endl;
delete p;
```

En el siguiente ejemplo se define un nuevo tipo de dato `Vec2i`, el cual
representa un vector de dos elementos de tipo `int`. Luego, en la función `main`
se utiliza el operador `new` para alocar la variable en el heap.

```c++
#include <iostream>

typedef struct {
    int x, y;
} Vec2i;

int main (void) {
    int *pos = new Vec2i;
    pos->x = 1;
    pos->y = 0;
    std::cout << "(" << p->x << "," << p->y << ")\n";
    delete Vec2i;
}
```
