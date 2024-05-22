#include <iostream>

#define	ULTIMO_DIGITO_PADRON	8

int main(){
	int *A, *C, *F;
	int **B;
	int H = 20 + ULTIMO_DIGITO_PADRON;

	A = new int[3];

	for (int i = 0; i < 3; i++) {
		A[i] = H + i;
	}

	C = new int;
	(*C) = A[1]; // C = 20 + ULTIMO_DIGITO_PADRON + 1
	F = A + 2;   // es equivalente a F = &A[2] (aritmética de punteros)

	std::cout << (*F) << (*C) << A[0] << std::endl;
	// (*F) = A[2] == 20 + ULTIMO_DIGITO_PADRON + 2 == 30
	// (*C) = A[1] == 20 + ULTIMO_DIGITO_PADRON + 1 == 29
	// A[0] = 20 + ULTIMO_DIGITO_PADRON = 28
	// la linea anterior imprime `302928\n`

	B = new int*[3]; // arreglo de punteros a int
	B[0] = C;        // B[0] = C = A + 1
	B[1] = F;        // B[1] = F = A + 2
	B[2] = &H;       // B[2] = *(B + 2) = &H = 20 + ULTIMO_DIGITO_PADRON

	std::cout << *B[1] << **B << *B[2] << std::endl;
	// *B[1] = *(*(B + 1)) = *F = A[2] = 20 + ULTIMO_DIGITO_PADRON + 2
	//   **B = *(B[0]) = *C = A[1] = 20 + ULTIMO_DIGITO_PADRON + 1
	// *B[2] = H = 20 + ULTIMO_DIGITO_PADRON
	// la linea anterior imprime `302928\n`

	(*B[0]) = (*F) + 3; // *B[0] = *F + 3 == A[2] + 3
	H++;
	A[2] = (*C) + 1;    // A[2] = *C + 1 = A[1] + 1 == 29 + 1

	std::cout << *C << *B[1] <<  *B[2] << std::endl;
	// *C = *B[0] = (*F) + 3 = A[2] + 3 == 20 + ULTIMO_DIGITO_PADRON + 2 + 3
	// *B[1] = *F = A[2] = (*C) + 1 = *(B[0]) + 1 == 33 + 1
	// *B[2] = H = 20 + ULTIMO_DIGITO_PADRON + 1 (++);
	// la linea anterior imprime `333429\n`

	F = C;
	C = A + 2;
	(**B) = A[0];
	A[2] = ** (B + 2);

	std::cout << H << (*C) << (*F) << std::endl;
	// H == 20 + ULTIMO_DIGITO_PADRON + 1 (++)
	// *C = A[2] = *(*(B+2)) = *B[2] = H = 20 + ULTIMO_DIGITO_PADRON + 1 (++)
	// *F = *C = 20 + ULTIMO_DIGITO_PADRON
	// la linea anterior imprime `292928\n`

	delete[] B;
	delete F;
	delete[] A;
	return 0;
}
