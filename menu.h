#ifndef MENU_H_
#define MENU_H_

#include <vector>
#include "list.h"
#include "barrio.h"
#include "parada.h"

#define CSV_DELIM ','

enum {
	CALLE = 0,
	ALT_PLANO,
	DIRECCION,
	COORD_X,
	COORD_Y,
	COMUNA,
	BARRIO,
	LINEA_1,
	LINEA_1_SENTIDO,
	LINEA_2,
	LINEA_2_SENTIDO,
	LINEA_3,
	LINEA_3_SENTIDO,
	LINEA_4,
	LINEA_4_SENTIDO,
	LINEA_5,
	LINEA_5_SENTIDO,
	LINEA_6,
	LINEA_6_SENTIDO
};


class Menu {
private:
	int linea;
	List<Barrio*> *barrios;
	double coordX, coordY;
	std::vector<int> *lineas;

	double getDistancia(double x1, double y1, double x2, double y2);

public:
	Menu();

	/*
	 * pos: Libera la memoria
	 */
	virtual ~Menu();

	/*
	 * pos: Recorre la lista de barrios e imprime la cantidad de paradas de cada barrio
	 */
	void imprimirCantidadDeParadasPorBarrio(); // CONSIGA 1

	/*
	 * pre: Recibe como parametro las coordenadas en X e Y
	 * pos:	Imprime por pantalla la parada mas cercana a la coordenada dada
	 */
	Parada *paradaMasCercanaPorCoordenada(double coordX,double coordY); //CONSIGNA 2 si imprime

	/*
	 * pos: Agrega lineas sin repetir al vector lineas
	 */
	void agregarElementoSinRepetir(std::vector<int>* lineas, std::vector<int>* vectorLineasAux);

	/*
	 * pos: Imprime por pantalla un listado de cantidad de paradas por donde pasan todas las lineas
	 */
	void cantidadDeParadasPorLinea();

	/*
	 * pos: Recorre una lista de paradas y accede a todas las lineas de las paradas dadas
	 */
	void lineasPorParada(List<Parada*>* paradas);

	void cargarDatos();

	void mostrarMenu();

	List<Parada*> *buscarParadas(List<Barrio*> *barrios, int linea);

	Barrio *getBarrioPorNombre(std::string nombre);
};

#endif
