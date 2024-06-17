#include "parada.h"

Parada::Parada(std::string calle,
		int alturaPlano,
		std::string direccion,
		int coord_x, int coord_y) {

	this->alturaPlano = alturaPlano;
	this->calle = calle;
	this->coord_x = coord_x;
	this->coord_y = coord_y;
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

int Parada::getCoord_X() {
	return this->coord_x;
}

int Parada::getCoord_y() {
	return this->coord_y;
}

List<Linea*> *Parada::getLineas() {
	return this->lineas;
}

void Parada::appendLineas(int numero, bool sentido) {
	this->lineas->insert(new Linea(numero, sentido))
}

Parada::~Parada() {
	delete lineas;
}

