/*
 * Linea.cpp
 *
 *  Created on: 16/06/2024
 *      Author: algo2
 */

#include "Linea.h"

Linea::Linea(int numero, bool sentido) {

	this->numero = numero;
	this->sentido = sentido;

}

int Linea::getNumero(){
	return this->numero;
}

bool Linea::getSentido(){
	return this->sentido;
}

Linea::~Linea() {
}

