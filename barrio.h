#ifndef BARRIO_H_
#define BARRIO_H_

#include <string>

#include "list.h"
#include "parada.h"

class Barrio {
private:

	string nombre;
	int comuna;
	list<Parada*>* paradas;

public:
	/*
	 *post: Deja creado la clase con los parametros dados
	 */
	Barrio(string nombre, int comuna);

	/*
	 * post: Vacia y elimina el Barrio
	 */
	virtual ~Barrio();
	/*
	 * post: Devuelve el numero de comuna del Barrio
	 */
	int getComuna();

	/*
	 * post: Devuelve el nombre del Barrio
	 */
	string getNombre();

	/*
	 * post: Devuelve una lista con todos las paradas de ese Barrio
	 */
	list<Parada*>* obtenerParadas();

	/*
	 * post: Agrega una para nueva
	 */
	void appendParada(string calle, int alturaPlano, string direccion, unsigned int coord_x, unsigned int coord_y);
};

#endif /* BARRIO_H_ */
