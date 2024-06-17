#include "barrio.h"

Barrio::Barrio(string nombre, int comuna){

	this->nombre = nombre;
	this->comuna = comuna;
	this-> paradas = new list<parada*>(); // crea la lista para las paradas

}

int Barrio::getComuna(){
	return this->comuna;
}

string Barrio::getNombre(){
	return this->nombre;
}

list<Parada*>* Barrio::obtenerParadas(){
	return this->paradas;
}

void Barrio::appendParada(string calle, int alturaPlano, string direccion, unsigned int coord_x, unsigned int coord_y){

	this->paradas->insent(new Parada(calle,alturaPlano,direccion,coord_x,coord_y)) //crea una para y la agrega a la lista de paradas
}

Barrio::~Barrio() {

	delete paradas;
}

