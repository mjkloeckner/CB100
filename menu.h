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
	List<Barrio*> *barrios;
	std::vector<int> *lineas;

private: 
	double getDistancia(double x1, double y1, double x2, double y2);

public:
	/*
	 * pos: Crea una lista de Barrios y un vector de Lineas en el heap
  		Inicializa la linea,coordX, y la coordY en 0
	 */
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

	/*
	 * pos: Abre el archivo "paradas-de-colectivo.csv"
	 */
	void cargarDatos();

	/*
	 * pos: Muestra por pantalla las opciones a elegir del menú y recibe un parametro. En base al parametro, ejecuta una funcion
	 *      Esto ocurre hasta que el usuario ingrese la letra "q" cuando esta en el menu de opciones 
  	*/
	void mostrarMenu();

	/*
 	 * pre: Recibe una lista de Barrios y una Linea
	 * pos: Devuelve una lista de Paradas de todos los Barrios que tengan a la Linea
	 */
	List<Parada*> *buscarParadas(List<Barrio*> *barrios, int linea);

	/*
	 * pos: Busca el barrio en la lista de barrios, si no lo encuentra devuelve NULL
	 */
	Barrio *getBarrioPorNombre(std::string nombre);
};

#endif
