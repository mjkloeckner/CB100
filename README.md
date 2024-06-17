# Trabajo Práctico 2

Este es el segundo trabajo practico de la materia Algoritmos y Estructura de
Datos de [FIUBA](https://en.wikipedia.org/wiki/Faculty_of_Engineering,_University_of_Buenos_Aires) curso Schmidt

El trabajo práctico se trata de una aplicación de consola interactiva que
analiza un archivo de datos en formato de valores separados por coma (CSV) y
genera un menu de opciones basados en esos datos

El archivo de datos contiene todas las paradas de colectivos de la Ciudad de
Buenos Aires, el barrio al que pertenece, sus coordenadas y otros datos
adicionales, la aplicación analiza esos datos y luego muestra un menu con
opciones relacionadas a esos datos, por ejemplo, que paradas existen en un
barrio, o que linea esta más cerca de una cierta coordenada, entre otras

## Obtención de Datos 

Los datos son públicos en la pagina oficial del Gobierno de la Ciudad de Buenos
Aires y se encuentran en el siguiente [link](https://data.buenosaires.gob.ar/dataset/colectivos-paradas)

## Inicio Rápido

### Sistemas Operativos Basados en Unix 

Clone el repositorio con el siguiente comando

```console
$ git clone https://github.com/mjkloeckner/CB100-tp2.git
```

Luego navegue al directorio del repositorio clonado

```console
$ cd CB100-tp2
```

Compile la aplicacion utilizando la herramienta `make`

```console
$ make
```

Finalmente corra la aplicación con el siguiente comando: 

```console
./main
```

### Windows

En el caso de windows puede instalar
[WSL](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux), para hacerlo
puede seguir la [guia oficial de
Microsoft](https://learn.microsoft.com/en-us/windows/wsl/install). Una vez
instalado WSL siga los pasos para los [Sistemas Operativos Basados en
UNIX](#sistemas-operativos-basados-en-unix)

## Integrantes

[Martin J. Klöckner](https://github.com/mjkloeckner)

[Ignacio A. Cettour](https://github.com/IgnacioCettour)

Camila Anahi Wilverht Rohr

[Carlos Reyes](https://github.com/reyesito)
