/*
 * Parada.h
 *
 *  Created on: 16/06/2024
 *      Author: algo2
 */

#include <string>
#include <list.h>
#ifndef PARADA_H_
#define PARADA_H_

class Parada {

private:

	string calle;
	int alturaPlano;
	string direccion;
	unsigned int coord_x;
	unsigned int coord_y;
	list<Linea*>* lineas;	//porque por cada parada hay tambien distintas lineas que tienen sentido y numero

public:

	/*
	 * post: Deja creado la parada con sus parametros
	 */
	Parada(string calle, int alturaPlano, string direccion, unsigned int coord_x, unsigned int coord_y);

	/*
	 * post: Devuelve el numero de la calle
	 */
	string getCalle();

	/*
	 * post: Devuelve la altura del plano
	 */
	int getAlturaPlano();

	/*
	 * post: Devuelve la dirrecion
	 */
	string getDireccion();

	/*
	 * post: Devuelve la coordenada en X de la parada
	 */
	unsigned int getCoord_X();

	/*
	 * post: Devuelve la coordenada en Y de la parada
	 */
	unsigned int getCoord_y();

	/*
	 * post: Devuelve una lista con las lineas de esa parada
	 */
	list<Linea*>* getLineas();

	/*
	 * post: Setea las lineas de esa parada
	 */
	void appendLineas(int numero, bool sentido);

	/*
	 * post: Elimina y vacia la parada y sus lineas
	 */
	virtual ~Parada(); //agregar las lineas
};

#endif /* PARADA_H_ */
