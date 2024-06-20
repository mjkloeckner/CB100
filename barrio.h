#ifndef BARRIO_H_
#define BARRIO_H_

#include <string>
#include <vector>

#include "list.h"
#include "parada.h"

class Barrio {
private:
	std::string nombre;
	int comuna;
	List<Parada*> *paradas;


public:

	 */
	double getDistancia(double x1,double y1,double x2,double y2);
	/*
	 * pos: Devuelve True si la linea se encuentra en listaDeLineas, sino devuelve False
	 */

	/*
	 *pos: Deja creado la clase con los parametros dados
	 */
	Barrio(std::string nombre, int comuna);

	/*
	 * pos: Vacia y elimina el Barrio
	 */
	virtual ~Barrio();
	bool lineaEnParada(int linea, std::vector<int> *listaDeLineas);

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
	void addParada(std::string calle, int alturaPlano, std::string direccion, double coordX, double coordY);

	/*
	 * pos: Devuelve el numero total de paradas que hay en el barrio
	 */
	int getSizeListaDeParadas(); //CONSIGNA 1

	/*
	 * pos: Devuelve la parada mas cercana a una coordenada dada
	 */
	Parada *paradaMasCercana(double coordX, double coordY);

	/*
	 * pre: Recibe el numero de una Linea
	 * pos: Devuelve una lista con todas las paradas del numero dado
	 */
	List<Parada*> *listaDeParadasPorLinea(int linea);

	/*
	 * pre: Recibe el numero de una linea
	 * pos:	Devuelve la cantidad de paradas por linea
	 */
	unsigned int getCantidadDeParadasPorLinea(int linea);

};

#endif /* BARRIO_H_ */
