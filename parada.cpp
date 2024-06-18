#include "parada.h"

Parada::Parada(std::string calle,
		int alturaPlano,
		std::string direccion,
		double coordX, double coordY) {

	this->alturaPlano = alturaPlano;
	this->calle = calle;
	this->coordX = coordX;
	this->coordY = coordY;
	this->direccion = direccion;
	this->lineas = new List<Linea*>(); // crea la lista para las lineas
}

std::string Parada::getCalle() {
	return this->calle;
}

int Parada::getAlturaPlano() {
	return this->alturaPlano;
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

List<Linea*> *Parada::getLineas() {
	return this->lineas;
}

void Parada::addLinea(int numero, bool sentido) {
	this->lineas->insert(new Linea(numero, sentido));
}

Parada::~Parada() {
	delete lineas;
}

