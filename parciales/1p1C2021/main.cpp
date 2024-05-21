#include <iostream>

int main(){
    int *A, *C, *F, **B, H;
    char *D, *E, G;

    H = 65;
    G = 'C';
    F = new int[3]; // arreglo de 3 enteros

    for (int i = 0; i < 3; i++) {
        F[i] = H + i; // asigna a cada valor de F (65 + `i`)
    }

    H++;   // incrementa la variable H
    A = F; // el puntero A apunte al primer elemento de F
           //
    C = new int; // se crea un nuevo entero el cual es apuntado por C

    (*C) = A[1]; // se asigna el valor del primer elemento de A,
                 // el cual apunta al primer elemento de F, a la variable que
                 // apunta C

    A = F + 2; // es equivalente a A = F[2];

    // imprime el primer valor de F, el primer valor de C y A
    std::cout << (*F) << (*C) << A[0] << std::endl;

    B = &C; // *B apunta al primer elemento de C
    A = C;  // A apunta al primer elemento de C

    C = F + 1; // equivalente a C = F[1];

    (**B) = H + 2;  // lo que apunta *B (primer elemento de C) ahora vale `H+2`

    std::cout <<  (*C) <<  (**B) << (*A) << std::endl; 

    // `cast` de la variable apuntada por A a tipo char
    D = (char*) A;
    E = (char*) *B;

    // el primer elemento de F ahora vale `70`;
    F[1] = 70; 

    std::cout << (*D) << (*E) << (*A) << std::endl; 

    E = &G; // `E` ahora apunta a la direccion de memoria de `G`
    H++;    // se incrementa el contenido de la variable `H`

    G = (char) H; // `G` ahora contiene el valor de `H` "casteado" a `char`

    H++; // se incrementa el contenido de la variable `H`,
         // esto no afecta a `G` ya que `G` no es puntero

    (*A) = H; // el contenido de la variable apuntada por `A` ahora 
              // es igual a `H`

    E = D; // ahora el puntero `E` apunta a la misma direccion que `D`

    std::cout << (*E)++ << (*D)++ << G << std::endl; 

    delete A;
    delete[] F;
    return 0;
}
