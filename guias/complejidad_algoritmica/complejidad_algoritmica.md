# Guía complejidad algorítmica

Algoritmos y Estructuras de Datos (CB100) - FIUBA  
Martin Klöckner - [mklockner@fi.uba.ar](mailto:mklockner@fi.uba.ar)

> 1. Un algoritmo divide un problema de tamaño $n$ en dos subproblemas de tamaño
> $n/2$ con un costo constante en cada paso adicional, obtener la complejidad
> sabiendo que el costo real $T(n)$ es: 
> \vspace{-0.65em}
> $$T(n) = 2T\left(\frac{n}{2}\right) + \mathcal{O}(1)$$

Como la función de costo real $T(n)$ depende de la misma función $T(n)$ pero con
una entrada menor $n/2$ se trata de un algoritmo recursivo o iterativo. Por el
método de expansion, el orden se calcula siguiendo los procedimientos a
continuación. De la expresión de $T(n)$:

$$\begin{align}
T(n) = 2T\left(\frac{n}{2}\right) + \mathcal{O}(1)
\end{align}$$

De la ecuación anterior se puede obtener $T\left(\frac{n}{2}\right)$
reemplazando $n$ con $n/2$:

$$\begin{align}
T\left(\frac{n}{2}\right) = 2T\left(\frac{n}{4}\right) +
\mathcal{O}(1)
\end{align}$$

Por lo tanto reemplazando $(2)$ en $(1)$ resulta:

$$\begin{align}
T(n) &= 2\cdotp \left[2T\left(\frac{n}{4}\right) + \mathcal{O}(1)\right] + \mathcal{O}(1) \nonumber\\
     &= 4T\left(\frac{n}{4}\right) + 2\mathcal{O}(1) + \mathcal{O}(1) \nonumber\\
     &= 4T\left(\frac{n}{4}\right) + 3\mathcal{O}(1)
\end{align}$$

Pero de $(1)$ también se puede obtener $T\left(\frac{n}{4}\right)$:

$$\begin{align}
T\left(\frac{n}{4}\right) = 2T\left(\frac{n}{8}\right) + \mathcal{O}(1)
\end{align}$$

Y reemplazando $(4)$ en la ecuación $(3)$:

$$\begin{align}
T(n) &= 4\cdotp \left[2T\left(\frac{n}{8}\right) + \mathcal{O}(1)\right]  + 2\mathcal{O}(1) + \mathcal{O}(1) \nonumber\\
     &= 8T\left(\frac{n}{8}\right) + 4\mathcal{O}(1) + 2\mathcal{O}(1) + \mathcal{O}(1)\nonumber\\
     &= 8T\left(\frac{n}{8}\right) + 7\mathcal{O}(1)
\end{align}$$

Se puede ver que luego de realizar $k$ veces el mismo procedimiento resulta:

$$\begin{align}
T(n) = 2^{k}\cdotp T\left(\frac{n}{2^k}\right) + (2^{k}-1)\cdotp \mathcal{O}(1)
\end{align}$$

Pero las iteraciones se terminan cuando el numero de entradas es $1$, entonces
en $(6)$:

$$\begin{align}
\frac{n}{2^k} = 1 \Rightarrow n = 2^k \Rightarrow \boxed{log_{2}(n) = k}
\end{align}$$

Con $(7)$ en $(6)$ resulta

$$T(n) = n\cdotp T(1) + (n - 1)\cdotp \mathcal{O}(1)$$

De la expresión anterior, suponiendo $T(1) = \mathcal{O}(1)$ y aproximando, resulta

$$\begin{align*}
T(n) &= n\cdotp \mathcal{O}(1) + (n - 1)\cdotp \mathcal{O}(1) \\
     &= \mathcal{O}(n) + \mathcal{O}(n) \Rightarrow \boxed{T(n)     = \mathcal{O}(n)}
\end{align*}$$

Es decir la complejidad resulta $\mathcal{O}(n)$. El mismo problema se podría haber
resuelto utilizando el teorema maestro para la reducción por division, el cual
en primer lugar dice que dado un algoritmo con función de costo real $T(n)$ de
la siguiente forma: 

$$T(n) = 
\begin{cases}
\hspace{0.75em} c\cdotp n^{k}                                     & \text{si } 1\leq n < b \\
\hspace{0.75em} a\cdotp T\left(\frac{n}{b}\right) + c\cdotp n^{k} & \text{si } n \geq b
\end{cases}$$

La complejidad algorítmica, o la solución de la ecuación de recurrencia $T(n)$
resulta:

$$T(n) = 
\begin{cases}
\hspace{0.75em} \mathcal{O}(n^k)                & \text{si } a < b^{k} \\
\hspace{0.75em} \mathcal{O}(n^{k}\cdotp log(n)) & \text{si } a = b^{k} \\
\hspace{0.75em} \mathcal{O}(n^{log_{b}(a)})     & \text{si } a > b^{k}
\end{cases}$$

En este caso se tiene que $T(n)$ es

$$T(n) = 2T\left(\frac{n}{2}\right) + \mathcal{O}(1)$$

Y es de la forma

$$a\cdotp T\left(\frac{n}{b}\right) + c\cdotp n^{k}$$

Con $a=2$, $b=2$, $c=1$ y $k=0$. Por lo tanto, la solución de la ecuación de
recurrencia, o la complejidad sale directamente, siendo esta:

$$T(n) = \mathcal{O}(n^{log_{b}(a)}) = \mathcal{O}(n^{log_{2}(2)}) \Rightarrow \boxed{T(n) = \mathcal{O}(n)}$$

Resultando de igual forma que para la complejidad hallada mediante el método de
expansión.

> 2. Un algoritmo busca un valor en un array ordenado reduciendo el problema a
>    la mitad en cada paso, con un costo constante para la comparación
>    \vspace{-0.65em}
>    $$T(n) = T\left(\frac{n}{2}\right) + \mathcal{O}(1)$$

Para obtener la complejidad algorítmica, utilizo el método de expansión:

$$\begin{align}
T(n) = T\left(\frac{n}{2}\right) + \mathcal{O}(1)
\end{align}$$

Pero $T\left(\frac{n}{2}\right)$ resulta de reemplazar $n$ por $\frac{n}{2}$ en
$T(n)$, entonces:

$$\begin{align}
T\left(\frac{n}{2}\right) = T\left(\frac{n}{4}\right) + \mathcal{O}(1)
\end{align}$$

Reemplazando $(9)$ en $(8)$ resulta

$$\begin{align}
T(n) &= T\left(\frac{n}{4}\right) + \mathcal{O}(1) + \mathcal{O}(1) \nonumber\\
     &= T\left(\frac{n}{4}\right) + 2\mathcal{O}(1)
\end{align}$$

Realizando una iteración mas reemplazando $n = \frac{n}{4}$ en $(8)$ resulta

$$\begin{align}
T\left(\frac{n}{4}\right) = T\left(\frac{n}{8}\right) + \mathcal{O}(1)
\end{align}$$

Y con $(11)$ en $(10)$:

$$\begin{align}
T(n) &= T\left(\frac{n}{8}\right) + \mathcal{O}(1) + \mathcal{O}(1) + \mathcal{O}(1) \nonumber\\
     &= T\left(\frac{n}{8}\right) + 3\mathcal{O}(1)
\end{align}$$

Se puede ver que luego de $k$ veces (o iteraciones) de repetir el procedimiento
resulta

$$\begin{align}
T(n) &= T\left(\frac{n}{2^k}\right) + k\cdotp \mathcal{O}(1)
\end{align}$$

Pero las iteraciones se terminan cuando se llega al caso base, esto es, cuando
$\frac{n}{2^k} = 1$ entonces:

$$\begin{align}
\frac{n}{2^k} &= 1 \Rightarrow 2^k = n \Rightarrow \boxed{k = log_{2}(n)}
\end{align}$$

Reemplazando $(14)$ en $(13)$

$$\begin{align}
T(n) &= T(1) + log_{2}(n)\cdotp \mathcal{O}(1)
\end{align}$$

Suponiendo $T(1) = \mathcal{O}(1)$ resulta que

$$\begin{align}
T(n) &= \mathcal{O}(1) + log_{2}(n)\cdotp \mathcal{O}(1)
\end{align}$$

Por lo tanto la complejidad algorítmica resulta:

$$\boxed{T(n) = \mathcal{O}(log(n))}$$

De manera análoga utilizando el teorema maestro, la expresión de $T(n)$ es de la
forma

$$a\cdotp T\left(\frac{n}{b}\right) + c\cdotp n^{k}$$

Con $a = 1$, $b = 2$, $c=1$ y $k=0$, por lo tanto aplicando el teorema maestro
para la reducción por division resulta que la complejidad es:

$$T(n) = \mathcal{O}(n^{k}\cdotp log(n)) = \mathcal{O}(n^{0}\cdotp log(n))$$

$$\Rightarrow\boxed{T(n) = \mathcal{O}(log(n))}$$

> 3. Un algoritmo suma los elementos de una lista de $n$ números dividiendo la
>    lista en dos partes de igual tamaño. 
>    \vspace{-0.25em}
>    $$T(n) = 2T\left(\frac{n}{2}\right) + \mathcal{O}(n)$$

En este caso aplico el teorema maestro en caso de poder aplicarse primero y
luego comparo con el método de expansión. Se puede ver que $T(n)$ es de la forma

$$a\cdotp T\left(\frac{n}{b}\right) + c\cdotp n^{k}$$

Con $a=2$, $b=2$, $c=1$ y $k=1$, por lo tanto se puede aplicar el teorema
maestro y la complejidad algorítmica resulta;

$$T(n) = \mathcal{O}(n^{k}\cdotp log(n)) = \mathcal{O}(n^{1}\cdotp log(n))$$

$$\Rightarrow\boxed{T(n) = \mathcal{O}(n\cdotp log(n))}$$

De manera análoga, utilizando el método de expansion:

$$\begin{align}
T(n) = 2T\left(\frac{n}{2}\right) + \mathcal{O}(n)
\end{align}$$

Pero $T\left(\frac{n}{2}\right)$ resulta de reemplazar $n =
\frac{n}{2}$ en $(17)$, de lo cual resulta

$$\begin{align}
T\left(\frac{n}{2}\right) = 2T\left(\frac{n}{4}\right) + \mathcal{O}\left(\frac{n}{2}\right)
\end{align}$$

Entonces de $(18)$ en $(17)$

$$\begin{align}
T(n) &= 2\cdotp \left[2 T\left(\frac{n}{4}\right) + \mathcal{O}\left(\frac{n}{2}\right)\right] + \mathcal{O}(n) \nonumber \\
     &= 4\cdotp T\left(\frac{n}{4}\right) + 2\cdotp \mathcal{O}\left(\frac{n}{2}\right) + \mathcal{O}(n)
\end{align}$$

Realizando una iteración más $T\left(\frac{n}{4}\right)$ resulta de reemplazar $n =
\frac{n}{4}$ en $(17)$, de lo cual resulta

$$\begin{align}
T\left(\frac{n}{4}\right) = 2T\left(\frac{n}{8}\right) + \mathcal{O}\left(\frac{n}{4}\right)
\end{align}$$

Y de $(20)$ en $(19)$

$$\begin{align}
T(n) &= 4\cdotp \left[ 2T\left(\frac{n}{8}\right) +
            \mathcal{O}\left(\frac{n}{4}\right) \right] + 2\cdotp
            \mathcal{O}\left(\frac{n}{2}\right) + \mathcal{O}(n) \nonumber \\
     &= 8\cdotp T\left(\frac{n}{8}\right) +
            4\cdotp \mathcal{O}\left(\frac{n}{4}\right) +
            2\cdotp \mathcal{O}\left(\frac{n}{2}\right) + \mathcal{O}(n)
\end{align}$$

Es decir, luego de $k$ iteraciones se llega a:

$$\begin{align}
T(n) &= 2^{k}\cdotp T\left(\frac{n}{2^{k}}\right) +
            \sum^{k-1}_{i=0} 2^{i} \cdotp \mathcal{O}\left(\frac{n}{2^{i}}\right) \nonumber \\
     &= 2^{k}\cdotp T\left(\frac{n}{2^{k}}\right) +
            \sum^{k-1}_{i=0} \mathcal{O}(n)
\end{align}$$

Pero cuando se llega al caso base se cumple:

$$\begin{align}
\frac{n}{2^{k}} = 1 \Rightarrow 2^{k} = n \Rightarrow\boxed{k = log_{2}(n)}
\end{align}$$

De $(23)$ en $(22)$:

$$\begin{align*}
T(n) &= n\cdotp T(1) + \sum^{log_{2}(n-1)}_{i=0} \mathcal{O}(n) \\
     &= n\cdotp T(1) + log_{2}(n-1) \cdotp \mathcal{O}(n) \\
     &= \mathcal{O}(n) + \mathcal{O}(n\cdotp log(n))
\end{align*}$$

El termino dominante de la expresión anterior es $n\cdotp log(n)$ entonces:

$$\Rightarrow\boxed{T(n) = \mathcal{O}(n\cdotp log(n))}$$

La expresión anterior coincide con la complejidad algorítmica hallada mediante
el método de aplicar el teorema maestro, pero se es evidente que el método de
expansion en algunos casos se puede volver mucho mas tedioso en comparación a
aplicar el teorema.
