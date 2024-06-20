#include "barrio.h"
#include <cmath>

Barrio::Barrio(std::string nombre, int comuna) {
	this->nombre = nombre;
	this->comuna = comuna;
	this->paradas = new List<Parada*>(); // crea la lista para las paradas
}

int Barrio::getComuna() {
	return this->comuna;
}

std::string Barrio::getNombre() {
	return this->nombre;
}

List<Parada*> *Barrio::getParadas() {
	return this->paradas;
}

void Barrio::addParada(std::string calle,
		int alturaPlano,
		std::string direccion,
		double coordX, double coordY) {

	this->paradas->insert(new Parada(calle, alturaPlano, direccion, coordX, coordY));
}

int Barrio::getSizeListaDeParadas() {  // CONSIGNA 1
	return this->paradas->getSize();
}

double Barrio::getDistancia(double x1,double y1,double x2,double y2){ //CONSIGAN 2
	double dX = (x2 - x1);
	double dY = (y2 - y1);

	return std::sqrt(dX*dX + dY*dY);
}


Parada *Barrio::paradaMasCercana(double coordX, double coordY) { //CONSIGNA 2
	this->paradas->startCursor();
	Parada * resultado = NULL;
	double distancia;
	double distanciaMinima;

	while(this->paradas->forwardCursor()){
		Parada *aux = this->paradas->getCursorData();

		if(resultado == NULL) {
			resultado = aux;
			distanciaMinima = getDistancia(coordX,coordY,aux->getCoordX(),aux->getCoordY());
		}
		else {
			distancia = getDistancia(coordX,coordY,aux->getCoordX(),aux->getCoordY());

			if(distancia < distanciaMinima) {
				resultado = aux;
				distanciaMinima = distancia;
			}
		}
	}

	return resultado;
}

bool Barrio::lineaEnParada(int linea,List<Linea*> *listaDeLineas ) { //CONSIGNA 3
	listaDeLineas->startCursor();

	while(listaDeLineas->forwardCursor()) {
		Linea *lineaActual = listaDeLineas->getCursorData();

		if(lineaActual->getNumero() == linea) {
			return true;
		}
	}
	return false;
}

List<Parada*> *Barrio::listaDeParadasPorLinea(int linea) { //CONSIGNA 3
	List<Parada*> *resultado = NULL;

	this->paradas->startCursor();
	while(this->paradas->forwardCursor()){
		Parada *paradaActual = this->paradas->getCursorData();

		List<Linea*> *listaDeLineas = paradaActual->getLineas();

		if(lineaEnParada(linea, listaDeLineas)){
			resultado->insert(paradaActual);
		}
	}

	return resultado;
}

unsigned int Barrio::getCantidadDeParadasPorLinea(int linea) { //CONSIGNA 4
	List<Parada*> *auxiliar = listaDeParadasPorLinea(linea);
	return auxiliar->getSize();
}

Barrio::~Barrio() {
	delete paradas;
}
