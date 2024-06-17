#ifndef PARADA_H_
#define PARADA_H_

#include <string>

#include "list.h"
#include "linea.h"

class Parada {
private:
	std::string calle;
	int alturaPlano;
	std::string direccion;
	int coord_x, coord_y;
	List<Linea*> *lineas;  // lineas que tienen sentido y numero

public:
	/*
	 * post: Deja creado la parada con sus parametros
	 */
	Parada(std::string calle,
			int alturaPlano,
			std::string direccion,
			int coord_x, int coord_y);

	/*
	 * post: Devuelve el numero de la calle
	 */
	std::string getCalle();

	/*
	 * post: Devuelve la altura del plano
	 */
	int getAlturaPlano();

	/*
	 * post: Devuelve la dirrecion
	 */
	std::string getDireccion();

	/*
	 * post: Devuelve la coordenada en X de la parada
	 */
	int getCoord_X();

	/*
	 * post: Devuelve la coordenada en Y de la parada
	 */
	int getCoord_y();

	/*
	 * post: Devuelve una lista con las lineas de esa parada
	 */
	List<Linea*> *getLineas();

	/*
	 * post: Setea las lineas de esa parada
	 */
	void addLinea(int numero, bool sentido);

	/*
	 * post: Elimina y vacia la parada y sus lineas
	 */
	virtual ~Parada(); //agregar las lineas
};

#endif /* PARADA_H_ */
