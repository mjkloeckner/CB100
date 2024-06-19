
#include "list.h"
#include "barrio.h"
#include "parada.h"
#ifndef CB100_TP2_MAIN_MENU_H_
#define CB100_TP2_MAIN_MENU_H_

class Menu {

private:

	int opcion;
	List<Barrio*>* barrios;
	double coordX;
	double coordY;
	int linea;
	List<Parada*>* paradasPorCadaLinea;
	List<Parada*>* cantidadDeParadasPorCadaLinea;


public:

	/*
	 *
	 */
	Menu(int opcion);

	/*
	 * pos: Recorre la lista de barrios e imprime la cantidad de paradas de cada barrio
	 */
	void cantidadDeParadasPorBarrio(); // CONSIGA 1

	/*
	 * pre: Recibe como parametro las coordenadas en X e Y
	 * pos:	Imprime por pantalla la parada mas cercana a la coordenada dada
	 */
	void paradaMasCercanaPorCoordenada(double coordX,double coordY); //CONSIGNA 2 si imprime

	/*
	 * pre: Recibe como parametro el numero de la linea
	 * pos: Imprime por pantalla un listado de paradas por donde pasa la linea
	 */
	void paradasPorLinea(int linea); //CONSIGNA 3

	/*
	 * pre: Recibe una lista de tipo parada
	 * pos: Imprime por pantalla la parada con su direcion y sus coordenadas en X e Y
	 */
	void imprimirParadasPorLinea(List<Parada*>* listaDeParadas);

	/*
	 * pre: Recibe como parametros dos listas
	 * pos: Agrega los elementos de la lista aux a la lista resultado
	 */
	void agregarElementosDeLista(List<Parada*>* listaAux,List<Parada*>* listaResultado);
	/*
	 * pre: Recibe como parametro el numero de la linea
	 * pos: Imprime por pantalla un listado de cantidad de paradas por donde pasa la linea
	 */
	void cantidadDeParadasPorLinea(); //CONSIGNA 4

	/*
	 *
	 */

	// HACER EL 5 (PREGUNTAR COMO HACERLO)

	/*
	 *
	 */
	virtual ~Menu();
};

#endif
