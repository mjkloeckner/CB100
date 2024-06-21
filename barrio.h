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
	/*
	 *pos: deja creado la clase con los parametros dados
	 */
	Barrio(std::string nombre, int comuna);

	/*
	 * pos: libera la memoria
	 */
	virtual ~Barrio();

	/*
	 * pos: devuelve la distancia entre la coordenadas dadas
	 */
	double getDistancia(double x1, double y1, double x2, double y2);

	/*
	 * pre: `listaDeLineas` es un vector no nulo
	 * pos: devuelve `true` si la linea se encuentra en listaDeLineas, sino devuelve False
	 */
	bool lineaEnParada(int linea, std::vector<int> *listaDeLineas);

	/*
	 * pos: devuelve el nombre del Barrio
	 */
	std::string getNombre();

	/*
	 * pos: devuelve una lista con todos las paradas de ese Barrio
	 */
	List<Parada*> *getParadas();

	/*
	 * pos: agrega una para nueva
	 */
	void addParada(std::string calle, int alturaPlano, std::string direccion,
			double coordX, double coordY, std::vector<int> lineas);

	/*
	 * pos: devuelve el numero total de paradas que hay en el barrio
	 */
	int getSizeListaDeParadas(); //CONSIGNA 1

	/*
	 * pos: devuelve la parada mas cercana a una coordenada dada
	 */
	Parada *paradaMasCercana(double coordX, double coordY);

	/*
	 * pre: recibe el numero de una Linea
	 * pos: devuelve una lista con todas las paradas del numero dado en caso de
	 *      que la linea no posea paradas devuelve NULL
	 */
	List<Parada*> *listaDeParadasPorLinea(int linea);

	/*
	 * pre: recibe el numero de una linea
	 * pos: devuelve la cantidad de paradas por linea
	 */
	unsigned int getCantidadDeParadasPorLinea(int linea);
};

#endif /* BARRIO_H_ */
