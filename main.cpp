#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

#include "barrio.h"
#include "menu.h"

/*

// busca el barrio en la lista de barrios, si no lo encuentra devuelve NULL
Barrio *getBarrioPorNombre(std::string nombre, List<Barrio*> *barrios) {
	if(barrios == NULL) {
		return NULL;
	}

	Barrio *res = NULL;

	barrios->startCursor();
	while(barrios->forwardCursor()) {
		if(barrios->getCursorData()->getNombre() == nombre) {
			res = barrios->getCursorData();
		}
	}

	return res;
}

Parada *paradaMasCercanaPorCoordenada(List<Barrio*> *barrios, double x, double y) {
	double distancia;
	double distanciaMinima;
	Parada *resultado, *paradaActual;

	distancia = distanciaMinima = 0.0f;
	resultado = paradaActual = NULL;

	barrios->startCursor();
	while(barrios->forwardCursor()) {
		Barrio *barrioAux = barrios->getCursorData();

		if(resultado == NULL) {
			resultado = barrioAux->paradaMasCercana(x, y);
			if(resultado == NULL) {
				return NULL;
			}
			distanciaMinima = barrioAux->getDistancia(x, y, resultado->getCoordX(), resultado->getCoordY());
			continue;
		}
		paradaActual = barrioAux->paradaMasCercana(x, y);
		if(paradaActual == NULL) {
			continue;
		}
		distancia = barrioAux->getDistancia(x, y, paradaActual->getCoordX(), paradaActual->getCoordY());
		if(distanciaMinima > distancia) {
			distanciaMinima = distancia;
			resultado = paradaActual;
		}
	}

	std::cout << "distancia: " << distancia << std::endl;
	return resultado;
}

List<Parada*> *buscarParadas(List<Barrio*> *barrios, int linea) {
	List<Parada*> *resultado, *paradasPorBarrio;
	Barrio *barrio;

	resultado = new List<Parada*>;

	barrios->startCursor();
	while(barrios->forwardCursor()) {
		barrio = barrios->getCursorData();
		paradasPorBarrio = barrio->listaDeParadasPorLinea(linea);
		if(paradasPorBarrio == NULL) {
			// no hay paradas de la linea
			continue;
		}

		paradasPorBarrio->startCursor();
		while(paradasPorBarrio->forwardCursor()) {
			resultado->insert(paradasPorBarrio->getCursorData());
		}

		delete paradasPorBarrio;
	}

	if(resultado->getSize() == 0) {
		delete resultado;
		return NULL;
	}

	return resultado;
}

*/

int main (void) {
	Menu *menu = new Menu(1);
	menu->cargarDatos();

	menu->mostrarMenu();

	// std::cout << "Total barrios creados: " << barrios->getSize() << std::endl;

	/*
	barrios->startCursor();
	while(barrios->forwardCursor()) {
		// std::cout << "Eliminando barrio `" << barrios->getCursorData()->getNombre() << "`\n";
		delete barrios->getCursorData();
	}

	delete barrios;
	*/

	/*
	List<int> *lista;

	lista = new List<int>;

	for(size_t i = 0; i < 10; i++) {
		lista->insert(i);
	}

	lista->startCursor();
	for(size_t i = 0; lista->forwardCursor(); i++) {
		std::cout << lista->getCursorData() << ((i == 8) ? "\n" : " -> ");
	}

	lista->remove(2);
	lista->remove(3);

	lista->startCursor();
	for(size_t i = 0; lista->forwardCursor(); i++) {
		std::cout << lista->getCursorData() << ((i == 8) ? "\n" : " -> ");
	}
	*/

	delete menu;
	return 0;
}
