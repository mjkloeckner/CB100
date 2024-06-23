#include "parada.h"

Parada::Parada(std::string calle,
		std::string direccion,
		double coordX, double coordY, std::vector<int> lineas) {

	this->calle = calle;
	this->coordX = coordX;
	this->coordY = coordY;
	this->direccion = direccion;
	this->lineas = new std::vector<int>(lineas);
}

std::string Parada::getCalle() {
	return this->calle;
}

std::string Parada::getDireccion() {
	return this->direccion;
}

double Parada::getCoordX() {
	return this->coordX;
}

double Parada::getCoordY() {
	return this->coordY;
}

std::vector<int> *Parada::getLineas() {
	return this->lineas;
}

void Parada::addLinea(int numero) {
	this->lineas->push_back(numero);
}

Parada::~Parada() {
	delete lineas;
}
