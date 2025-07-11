# Teórica 13-03-24

## Introducción a la materia

* Se utilizara el lenguaje C++ versión ANSI C98
* Recomendado utilizar un entorno de desarrollo (IDE) por sobre un editor de
  texto y un compilador de linea de comandos
* Se recomienda compilar con la maquina virtual provista por el curso previo a
  entregar un trabajo práctico para corroborar que funcione correctamente en una
  computadora diferente

## El lenguaje de programación C++

### Convenciones utilizadas en el curso

* Capitalización de tipo *camelCase* para nombrar las variables
* Definir las constantes numéricas como `static const int valor = 1;` al
  comienzo del archivo
* Evitar el uso de *goto*


### Parámetros de función como referencias

El pasaje de variables a una función por referencia permite a las funciones
acceder a la memoria de la variable invocada y modificarla si la función lo
permite.

En el siguiente ejemplo la función `foo` recibe una variable `var` por
referencia, nótese que de esta manera la función no utiliza más memoria que la
dirección de memoria de la variable `var`, esto permite ahorrar memoria ya que
de pasar la variable `var` por valor, la función `foo` debería hacer una copia
local de la variable `var`

```c++
void foo(int &var) {
    return var + 1;
}
```

Una ventaja del pasaje por referencia es que permite agregar el prefijo `const`
el cual permite a la función acceder a la memoria del parámetro pero sin
modificar el contenido de la memoria. 

```c++
void foo(const int &var) {
    return var;
}
```
