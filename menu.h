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
	 * pre: Recibe como parametro el numero de la linea
	 * pos: devuelve una lista de paradas que incluyen la linea
	 */
	// void paradasPorLinea(int linea); //CONSIGNA 3
	List<Parada*> *paradasPorLinea(int linea);

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
	 * pos: Imprime por pantalla un listado de cantidad de paradas por donde pasan todas las lineas
	 */
	void cantidadDeParadasPorLinea(); //CONSIGNA 4

	/*
	 * pos: Agrega lineas sin repetir al vector lineas
	 */
	void agregarElementoSinRepetir(std::vector<int>* lineas, std::vector<int>* vectorLineasAux);

	/*
	 * pos: Recorre una lista de paradas y accede a todas las lineas de las paradas dadas
	 */
	void lineasPorParada(List<Parada*>* paradas);

	/*
	 * pos: Imprime por pantalla la linea y la cantidad de paradas por las que pasa
	 */
	void imprimirCantidadParadasPorLinea(std::vector<int>* lineas);

	/*
	 * pre: Recibe el nombre del Barrio, la linea, y una coordenada
	 * pos: Agrega las paradas ordenadas por distancia de un barrio con respecto a una coord a la lista de paradas cercanas
	 */
	void paradasMasCercanasPorBarrio(std::string barrio,int linea,double coordX,double coordY);

	/*
	 *
	 */
	void listaOrdenadaPorDistancia(List<Parada*>* listaAux,double coordX,double coordY, Barrio * barrioAux);

	/*
	 *
	 */
	void removerParadaMasCercana(List<Parada*>*listaAux,Parada * paradaCercana);

	void cargarDatos();

	void mostrarMenu();


	List<Parada*> *buscarParadas(List<Barrio*> *barrios, int linea);

	Barrio *getBarrioPorNombre(std::string nombre);

	// List<Parada*> *buscarParadas(int linea);
};

#endif
