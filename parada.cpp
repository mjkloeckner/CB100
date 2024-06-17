#include "parada.h"

Parada::Parada(string calle, int alturaPlano, string direccion, unsigned int coord_x, unsigned int coord_y) {

	this->alturaPlano = alturaPlano;
	this->calle = calle;
	this->coord_x = coord_x;
	this->coord_y = coord_y;
	this->direccion = direccion;
	this->lineas = new list<Linea*>(); // crea la lista para las lineas

}

string Parada::getCalle(){
	return this->calle;
}

int Parada::getAlturaPlano(){
	return this->alturaPlano;
}

string Parada::getDireccion(){
	return this->direccion;
}

unsigned int Parada::getCoord_X(){
	return this->coord_x;
}

unsigned int Parada::getCoord_y(){
	return this->coord_y;
}

list<Linea*>* Parada::getLineas(){
	return this->lineas;
}

void Parada::appendLineas(int numero, bool sentido){

	this->lineas->insert(new Linea(numero,sentido))

}

Parada::~Parada() {

	delete lineas;

}

