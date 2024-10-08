#ifndef PARADA_H_
#define PARADA_H_

#include <string>
#include <vector>

#include "list.h"

class Parada {
private:
	double coordX, coordY;
	std::vector<int> *lineas;
	std::string calle, direccion;
	// List<Linea*> *lineas;  // lineas que tienen sentido y numero

public:
	/*
	 * post: Deja creado la parada con sus parametros
	 */
	Parada(std::string calle,
			std::string direccion,
			double coordX, double coordY, std::vector<int> lineas);

	/*
	 * post: Devuelve el numero de la calle
	 */
	std::string getCalle();

	/*
	 * post: Devuelve la dirrecion
	 */
	std::string getDireccion();

	/*
	 * post: Devuelve la coordenada en X de la parada
	 */
	double getCoordX();

	/*
	 * post: Devuelve la coordenada en Y de la parada
	 */
	double getCoordY();

	/*
	 * post: Devuelve una lista con las lineas de esa parada
	 */
	std::vector<int> *getLineas();

	/*
	 * post: Setea las lineas de esa parada
	 */
	void addLinea(int numero);

	/*
	 * post: Elimina y vacia la parada y sus lineas
	 */
	virtual ~Parada(); //agregar las lineas
};

#endif /* PARADA_H_ */
