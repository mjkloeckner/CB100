# Guía 4: Tipos de Datos Abstractos

> ¿Qué es un TDA?

Los tipos de datos abstractos son tipos ajenos al lenguaje de programación, se
definen de acuerdo a un comportamiento especifico el cual se espera que tenga el
tipo de dato, y desde el punto de vista del usuario no importa la manera en la
que esté implementado.

> ¿Qué paradigmas de programación se utilizaron antes de TDA?

El principal paradigma de programación utilizado previamente es el paradigma
procedural, en el cual se separa la ejecución del código en funciones o
"subrutinas".

> ¿Cuáles eran sus principales problemas?

Uno de los mayores problemas es que se debe invocar a cada función pasando como
parámetros los recursos a los cuales se pretende que la función acceda, a menos
que se utilicen variables globales, lo cual soluciona en parte este
inconveniente pero es una mala práctica, ya que se permite el acceso a esas
variables globales a cualquier función que esté en el mismo alcance que la
variable definida.

> ¿Qué es una clase?

Las clases se utilizan como plantilla o molde, para definir un tipo de dato
abstracto u objeto. Una clase combina una serie de atributos a los cuales
caracterizan un tipo de dato.

> ¿Qué es un objeto?

Un objeto es un tipo de dato que tiene un conjunto de atributos y un
comportamiento determinado.

> ¿Cuáles son las principales características de TDA?

Las principales características de los TDAs son sus propiedades y atributos ya
que el valor de estos define el estado del mismo en un determinado momento.

Dentro de los atributos principela se encuentra el nombre del TDA, las
invariantes del mismo y sus operaciones y axiomas.

* El nombre nos indica al tipo que nos referimos, es el nombre del tipo de dato
  y debe ser único en el espacio del nombre.
* Las invariantes son condiciones que deben cumplir los atributos que
  pertenezcan al TDA.
* Las operaciones (o métodos) del TDA definen el comportamiento del mismo, se
  indican con su nombre (o signo), los parámetros que recibe y su valor de
  retorno, también se indica las Pre- y Post-condiciones, los cuales son los
  axiomas.

> ¿Cómo se debe encarar un problema en TDA?

Se debe arrancar definiendo las características que debe tener el TDA, su
nombre, sus atributos y sus funciones u operaciones, independientemente del
lenguaje de programación a utilizar.

> ¿Qué significa `public` y `private`?

Las palabras reservadas `public` y `private` se utilizan para definir el alcance
de los atributos cuando se define una clase. `public` como hace referencia su
nombre, permite que los atributos puedan ser accedidos y modificados, en caso de
ser variables, luego de definida la clase, mientras que `private` no
permite al usuario acceder ni modificar los atributos definidos como tal, solo
pueden ser modificados dentro de la definición de la clase.

> ¿Qué significa `static`? ¿Desde dónde conviene acceder a un atributo de tipo
> `static`? Dar un ejemplo de su uso.

La palabra reservada `static` permite que una variable permanezca en memoria
durante toda la ejecución del programa, incluso si la variable se define dentro
de una función, por dar un ejemplo, y la función termina su ejecución, en ese
caso, si se vuelve a invocar la función, esa variable contendrá el valor que
contenía al finalizar la ejecución anterior.

En el caso de definirlas dentro de una clase, conviene accederlas utilizando
métodos.

> ¿Qué es un constructor?

Un constructor es un método u operación de un TDA cuya misión es inicializar un
objeto de una clase. En el constructor se asignan los valores iniciales del
nuevo objeto.

En el caso de C++, los constructores poseen el mismo nombre de la clase a la
cual pertenece y no puede devolver ningún valor (tampoco se puede especificar la
palabra reservada `void`).

> ¿Qué es un destructor? ¿Cuándo se debe programar uno?

Un destructor es un método de un objeto, al igual que el constructor, solo que
en lugar de asignar memoria e inicializar variables, libera recursos, como
cerrar archivos, liberar memoria dinámica utilizada, etc.

Los destructores no deben ser llamados en forma explícita, se llaman
automáticamente cuando se termina el ámbito en donde el objeto fue definido o,
cuando se ejecuta la instrucción `delete`, en el caso de haber sido creado el
objeto con el operador `new`, utilizando memoria dinámica.

> ¿Qué es la sobrecarga de métodos?

La sobrecarga de métodos permite definir múltiples métodos con el mismo nombre
pero que difieren en los argumentos, esto resulta útil, por ejemplo, para
definir múltiples métodos con igual nombre y distinto tipo de argumentos.

> ¿Qué es el objeto `this`?

El objeto `this` en C++ es una referencia (puntero) que poseen todos los objetos
la cual apunto a sí mismo, se genera de manera automática al invocar un método y
se utiliza para resolver ambigüedades en los nombres del alcance del método.

> ¿Qué son las Pre y Post condiciones? ¿Para qué sirven?

Las Pre y Post son comentarios que se indican ante cada método y permiten al
programador detectar la condición previa y posterior que tendrá el objeto al
cual pertenece el método.

No son necesarios para la ejecución de la aplicación pero es una buena práctica.
