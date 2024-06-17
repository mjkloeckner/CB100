#ifndef BARRIO_H_
#define BARRIO_H_

#include <string>

#include "list.h"
#include "parada.h"

class Barrio {
private:
	std::string nombre;
	int comuna;
	List<Parada*> *paradas;

public:
	/*
	 *pos: Deja creado la clase con los parametros dados
	 */
	Barrio(std::string nombre, int comuna);

	/*
	 * pos: Vacia y elimina el Barrio
	 */
	virtual ~Barrio();
	/*
	 * pos: Devuelve el numero de comuna del Barrio
	 */
	int getComuna();

	/*
	 * pos: Devuelve el nombre del Barrio
	 */
	std::string getNombre();

	/*
	 * pos: Devuelve una lista con todos las paradas de ese Barrio
	 */
	List<Parada*> *getParadas();

	/*
	 * pos: Agrega una para nueva
	 */
	void addParada(std::string calle, int alturaPlano, std::string direccion, int coord_x, int coord_y);
};

#endif /* BARRIO_H_ */
