#include "barrio.h"

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

List<Parada*> *Barrio::obtenerParadas() {
	return this->paradas;
}

void Barrio::addParada(std::string calle,
		int alturaPlano,
		std::string direccion,
		int coord_x, int coord_y) {

	this->paradas->insert(new Parada(calle, alturaPlano, direccion, coord_x, coord_y));
}

Barrio::~Barrio() {
	delete paradas;
}

