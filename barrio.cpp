#include "barrio.h"
#include <cmath>

Barrio::Barrio(std::string nombre) {
	this->nombre = nombre;
	this->paradas = new List<Parada*>; // crea la lista para las paradas
}

std::string Barrio::getNombre() {
	return this->nombre;
}

List<Parada*> *Barrio::getParadas() {
	return this->paradas;
}

void Barrio::addParada(std::string calle,
		std::string direccion,
		double coordX, double coordY, std::vector<int> lineas) {

	this->paradas->insert(new Parada(calle, direccion, coordX, coordY, lineas));
}

int Barrio::getSizeListaDeParadas() {  // CONSIGNA 1
	return this->paradas->getSize();
}

double Barrio::getDistancia(double x1,double y1,double x2,double y2){ //CONSIGAN 2
	double dX = (x2 - x1);
	double dY = (y2 - y1);

	return std::sqrt(dX*dX + dY*dY);
}

// lon -> X; lat -> Y;
Parada *Barrio::paradaMasCercana(double lon, double lat) { //CONSIGNA 2
	double distancia;
	double distanciaMin;

	Parada *resultado, *aux;

	resultado = aux = NULL;

	this->paradas->startCursor();
	while(this->paradas->forwardCursor()){
		aux = this->paradas->getCursorData();

		if(resultado == NULL) {
			resultado = aux;
			distanciaMin = getDistancia(lon, lat, aux->getCoordX(), aux->getCoordY());
		}
		else {
			distancia = getDistancia(lon, lat, aux->getCoordX(),aux->getCoordY());

			if(distancia < distanciaMin) {
				resultado = aux;
				distanciaMin = distancia;
			}
		}
	}

	return resultado;
}

bool Barrio::lineaEnParada(int linea, std::vector<int> *listaDeLineas) { //CONSIGNA 3
	if(listaDeLineas == NULL) {
		return false;
	}

	for(size_t i = 0; i < listaDeLineas->size(); ++i) {
		if((*listaDeLineas)[i] == linea) {
			return true;
		}
	}

	return false;
}

List<Parada*> *Barrio::listaDeParadasPorLinea(int linea) { //CONSIGNA 3
	Parada *parada;
	List<Parada*> *resultado;
	std::vector<int> *listaDeLineas;

	resultado = new List<Parada*>;

	this->paradas->startCursor();
	while(this->paradas->forwardCursor()){
		parada = this->paradas->getCursorData();
		listaDeLineas = parada->getLineas();

		if(lineaEnParada(linea, listaDeLineas)) {
			resultado->insert(parada);
		}
	}

	if(resultado->getSize() == 0) {
		delete resultado;
		return NULL;
	}

	return resultado;
}

unsigned int Barrio::getCantidadDeParadasPorLinea(int linea) { //CONSIGNA 4
	Parada *parada;
	unsigned int cantidadDeParadas;

	cantidadDeParadas = 0;

	this->paradas->startCursor();
	while(this->paradas->forwardCursor()) {
		parada = this->paradas->getCursorData();
		for(size_t i = 0; i < parada->getLineas()->size(); ++i) {
			if((*parada->getLineas())[i] == linea) {
				cantidadDeParadas++;
			}
		}
	}

	return cantidadDeParadas;
}

Barrio::~Barrio() {
	Parada *delParada;

	this->paradas->startCursor();
	while(this->paradas->forwardCursor()){
		delParada = this->paradas->getCursorData();
		// std::cout << "Eliminando parada `" << delParada->getDireccion() << "`\n";
		delete delParada;
	}

	delete this->paradas;
}
