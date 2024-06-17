#ifndef LINEA_H_
#define LINEA_H_

#include <string>

class Linea {
private:

	int numero;
	bool sentido; // aca puede ser tambien un enum ?????? un bool con true y false porque en realidad es I o V

public:

	/*
	 * pre: Recibe como parametro el numero y el sentido de la linea
	 * post: crea la clase Linea con su numero y sentido
	 */
	Linea(int numero, bool sentido);

	/*
	 * post: Devuelve el numero de la linea
	 */
	int getNumero();

	/*
	 * post: Devuelve el sentido de la linea
	 */
	 bool getSentido();


	/*
	 *  post: Elimina la linea
	 */
	virtual ~Linea();
};

#endif /* LINEA_H_ */
