#include "menu.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath>


void Menu::cantidadDeParadasPorBarrio() {
	this->barrios->startCursor();

	while(this->barrios->forwardCursor()) {
		Barrio * barrioAux = this->barrios->getCursorData();
		std::cout << "La cantidad de paradas que hay en el barrio "
				  << barrioAux->getNombre()
				  << " es: "
				  << barrioAux->getSizeListaDeParadas()
				  << std::endl;
		}
}


Parada *Menu::paradaMasCercanaPorCoordenada(double coordX, double coordY) {
	double distanciaMinima;
	double distancia;

	Parada *paradaResultado = NULL;
	Parada *paradaActual = NULL;

	this->barrios->startCursor();
	while(this->barrios->forwardCursor()) {
		Barrio *barrioAux = this->barrios->getCursorData();

		if(paradaResultado == NULL) {
			paradaResultado = barrioAux->paradaMasCercana(
					coordX, coordY, barrioAux->getParadas());

			distanciaMinima = barrioAux->getDistancia(
					coordX, coordY,
					paradaResultado->getCoordX(),paradaResultado->getCoordY());
		}
		else {
			paradaActual= barrioAux->paradaMasCercana(
					coordX, coordY, barrioAux->getParadas());

			distancia = barrioAux->getDistancia(
					coordX, coordY,
					paradaActual->getCoordX(), paradaActual->getCoordY());

			if(distanciaMinima > distancia) {
				distanciaMinima = distancia;
				paradaResultado = paradaActual;
			}
		}
	}

	std::cout<< "La parada mas cercana esta en: "
			 << paradaResultado->getDireccion()
			 << std::endl
			 << "en la coordenada X: "
			 << paradaResultado->getCoordX()
			 << std::endl
			 << "en la coordenada Y:"
			 << paradaResultado->getCoordY()
			 << std::endl;

	return paradaResultado;
}

void Menu::agregarElementosDeLista(List<Parada*>* listaAux, List<Parada*>* listaResultado) {
	listaAux->startCursor();
	while(listaAux->forwardCursor()) {
		Parada *paradaAux = listaAux->getCursorData();

		listaResultado->insert(paradaAux);
	}
}

void Menu::imprimirParadasPorLinea(List<Parada*> *listaDeParadas) {
	if(listaDeParadas->getSize() == 0) {
		std::cout<<"No se econtro ninguna parada para esta linea";
		throw "No se econtro ninguna parada para esta linea";
	}

	listaDeParadas->startCursor();
		while(listaDeParadas->forwardCursor()){
			Parada *paradaAux = listaDeParadas->getCursorData();

			std::cout << "La parada esta en: "
					  << paradaAux->getDireccion()
					  << std::endl
					  << "en la coordenada X: "
					  << paradaAux->getCoordX()
					  << std::endl
					  << "en la coordenada Y:"
					  << paradaAux->getCoordY()
					  << std::endl;
		}
}

List<Parada*> *Menu::paradasPorLinea(int linea) {
	// this->paradasPorCadaLinea = NULL;
	List<Parada*> *listaAux = new List<Parada*>;
	List<Parada*> *resultado = new List<Parada*>;

	this->barrios->startCursor();
	while(this->barrios->forwardCursor()){
		Barrio *barrioAux = this->barrios->getCursorData();

		listaAux = barrioAux->listaDeParadasPorLinea(linea);

		std::cout << "listaAux->getSize(): " << listaAux->getSize() << "\n";
		// agregarElementosDeLista(listaAux, resultado);
	}

	if(resultado->getSize() == 0) {
		delete resultado;
		return NULL;
	}
	return resultado;
}

void Menu::agregarElementoSinRepetir(std::vector<int> *lineas, std::vector<int> *vectorLineasAux) {
	unsigned int contador = 0;
	size_t lineaTope = vectorLineasAux->size();

	bool seRepite = false;
	for(size_t i = 0; i < lineaTope; i++) {
		for(size_t j = 0; j < lineas->size(); j++) {
			if((*vectorLineasAux)[i] == (*lineas)[j]) {
				seRepite = true;
			}
		}
		if(seRepite == false) {
			lineas->push_back((*vectorLineasAux)[i]);
		}
	}

	return;
}

void Menu::lineasPorParada(List<Parada*> *paradas) {
	Parada *paradaAux;
	std::vector<int> *vectorLineasAux = new std::vector<int>;

	// vectorLineasAux->push_back(10);
	// vectorLineasAux->push_back(20);
	// vectorLineasAux->push_back(30);

	paradas->startCursor();
	while(paradas->forwardCursor()){
		paradaAux = paradas->getCursorData();

		// std::cout << "direccion: " << paradaAux->getDireccion() << std::endl;

		vectorLineasAux = paradaAux->getLineas();

		// for(size_t i = 0; i < vectorLineasAux->size(); ++i) {
		// 	std::cout << (*vectorLineasAux)[i] << std::endl;
		// }

		agregarElementoSinRepetir(this->lineas, vectorLineasAux);
	}
}

void Menu::imprimirCantidadParadasPorLinea(std::vector<int>* lineas){
	// std::cout << "lineas->size(): " << lineas->size() << std::endl;
	List<Parada*> *paradas;

	for(size_t i=0; i < lineas->size(); i++) {
		paradas = paradasPorLinea((*lineas)[i]);
		if(paradas == NULL) {
			std::cout << "no hay paradas de la liena especificada\n";
			continue;
		}
		std::cout << (*lineas)[i] <<" : " << paradas->getSize() <<std::endl;
		delete paradas;
	}
}

void Menu::cantidadDeParadasPorLinea() {
	Barrio *barrioAux;

	this->lineas->clear();
	this->barrios->startCursor();

	while(this->barrios->forwardCursor()){
		barrioAux = this->barrios->getCursorData();
		// std::cout << barrioAux->getNombre() << std::endl;

		lineasPorParada(barrioAux->getParadas());
	}
}

// 9 -> 8 -> 7 -> 6 -> 5 -> 4 -> 3 -> 2 -> 1
void Menu::removerParadaMasCercana(List<Parada*> *listaAux, Parada *paradaCercana){
	Parada *paradaAux;
	unsigned int posicion = 0;

	listaAux->startCursor();
	while(listaAux->forwardCursor()) {
		posicion++;
		paradaAux = listaAux->getCursorData();

		if(paradaAux == paradaCercana) {
			listaAux->remove(posicion);
			std::cout << "Removiendo: `" << paradaAux->getDireccion() << "`\n";
		}
	}
}

// 9 -> 8 -> 7 -> 6 -> 5 -> 4 -> 3 -> 2 -> 1
void Menu::listaOrdenadaPorDistancia(List<Parada*> *listaDeParadasDeLinea,
		double coordX, double coordY, Barrio *barrioAux) {

	// listaDeParadasDeLinea -> lista de paradas por linea
	List<Parada*>* listaDeParadasCercanas;
	Parada *paradaAux;

	listaDeParadasCercanas = new List<Parada*>;
	size_t cantidadDeParadas = listaDeParadasDeLinea->getSize();

	// listaDeParadasDeLinea->remove(1);
	// listaDeParadasDeLinea->startCursor();
	// while(listaDeParadasDeLinea->forwardCursor()) {
	// 	std::cout << listaDeParadasDeLinea->getCursorData()->getDireccion() << std::endl;
	// }

	return;
	for(size_t i = 1; i < cantidadDeParadas + 1; i++) {
		// probar cuantas iteraciones hacer
		Parada *paradaCercana = barrioAux->paradaMasCercana(coordX, coordY, listaDeParadasDeLinea);
		// std::cout << paradaCercana->getDireccion() << std::endl;
		listaDeParadasDeLinea->remove(i);
		// removerParadaMasCercana(listaAux, paradaCercana);
		imprimirParadasPorLinea(listaDeParadasDeLinea);

		// listaDeParadasDeLinea->startCursor();
		// while(listaDeParadasDeLinea->forwardCursor()) {
		// 	std::cout << listaDeParadasDeLinea->getCursorData()->getDireccion() << std::endl;
		// }


		// listaDeParadasCercanas->startCursor();
		// while(listaDeParadasCercanas->forwardCursor()) {
		// 	std::cout << listaDeParadasCercanas->getCursorData()->getDireccion() << std::endl;
		// }

		/*
		unsigned int posicion = 0;

		listaAux->startCursor();
		while(listaAux->forwardCursor()) {
			posicion++;
			paradaAux = listaAux->getCursorData();

			if(paradaAux == paradaCercana) {
				listaAux->remove(posicion);
				std::cout << "Removiendo: `" << paradaAux->getDireccion() << "`\n";
			}
		}
		*/
	}
}

void Menu::paradasMasCercanasPorBarrio(std::string barrio,
		int linea, double coordX, double coordY) {

	List<Parada*>* listaAux;
	listaAux = new List<Parada*>;

	this->barrios->startCursor();
	while(this->barrios->forwardCursor()) {
		Barrio * barrioAux = this->barrios->getCursorData();

		// std::cout << "analizando: `" <<  barrioAux->getNombre() << "`\n";

		if(barrio == barrioAux->getNombre()) {
			std::cout << "se encontro barrio con el mismo nombre\n";
			listaAux = barrioAux->listaDeParadasPorLinea(linea);
			listaOrdenadaPorDistancia(listaAux, coordX, coordY, barrioAux);
		}
	}
}

Menu::Menu() {
	this->barrios = new List<Barrio*>;
	this->lineas = new std::vector<int>;
	this->paradasPorCadaLinea = new List<Parada*>;
	this->cantidadDeParadasPorCadaLinea = new List<Parada*>;
	this->listaDeParadasCercanasOrdenadas = new List<Parada*>;
	std::vector<int> *lineas = new std::vector<int>;

	this->linea = 0;
	this->coordX = this->coordY = 0.0f;
}

void delSurroundingChar(std::string &str, char c) {
	str.erase(0, 1);
	str[str.size() - 1] = '\0';
}

size_t getTokens(std::string line, std::vector<std::string> &tokens) {
	std::string token;
	std::stringstream lineStream;
	size_t field;

	lineStream.clear();
	lineStream.str(line);

	for(field = CALLE; std::getline(lineStream, token, CSV_DELIM); ++field) {
		// solucion a `token` es una cadena que contiene CSV_DELIM
		while((token[0] == '"') && (token[token.size() - 1] != '"')) {
			std::string nextToken;
			std::getline(lineStream, nextToken, CSV_DELIM);
			token += CSV_DELIM + nextToken;
		}
		if(token[0] == '"' && token[token.size() - 1] == '"') {
			delSurroundingChar(token, '"');
		}
		tokens.push_back(token);
	}

	return field;
}

List<Parada*> *Menu::buscarParadas(List<Barrio*> *barrios, int linea) {
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


// busca el barrio en la lista de barrios, si no lo encuentra devuelve NULL
Barrio *Menu::getBarrioPorNombre(std::string nombre) {
	Barrio *res, *barrio;

	res = NULL;
	this->barrios->startCursor();

	while(this->barrios->forwardCursor()) {
		barrio = this->barrios->getCursorData();
		if(barrio->getNombre() == nombre) {
			res = this->barrios->getCursorData();
			break;
		}
	}

	return res;
}

double getDistancia(double x1, double y1, double x2, double y2) {
	double dX = (x2 - x1);
	double dY = (y2 - y1);

	return std::sqrt(dX*dX + dY*dY);
}

void ordenarParadasPorDistanciaACoordenada(List<Parada*> *paradas, double x, double y) {
	Node<Parada*> *actual;
	Node<Parada*> *minimo;
	Node<Parada*> *siguiente;
	double distanciaActual, distanciaSiguiente;

	paradas->startCursor();
	while(paradas->forwardCursor()) {
		actual = paradas->getCursor();
		minimo = actual;
		siguiente = actual->getNext();

		distanciaActual = getDistancia(actual->getData()->getCoordX(), actual->getData()->getCoordY(), x, y);

		while (siguiente != NULL) {
			distanciaSiguiente = getDistancia(siguiente->getData()->getCoordX(), siguiente->getData()->getCoordY(), x, y);
			if (distanciaSiguiente < distanciaActual) {
				minimo = siguiente;
			}
			siguiente = siguiente->getNext();
		}

		if (minimo != actual) {
			Parada *temp = actual->getData();
			actual->setData(minimo->getData());
			minimo->setData(temp);
		}
	}
}

void Menu::cargarDatos() {
	std::ifstream inputFile;
	std::string token, line;
	std::vector<std::string> tokens;
	std::vector<int> lineasEnParada;
	Barrio *barrio;

	const char *inputFilePath = "paradas-de-colectivo.csv";

	int alturaPlano, fields;
	std::string barrioNombre, calle, direccion;

	inputFile.open(inputFilePath);
	if(!inputFile.is_open()) {
		std::cout << "No se pudo abrir el archivo `" << inputFilePath << "`\n";
	}

	std::getline(inputFile, line); // saltea la primer linea

	while(std::getline(inputFile, line)) {
		tokens.clear();
		lineasEnParada.clear();
		fields = getTokens(line, tokens);

		for(int field = CALLE; field <= fields; ++field) {
			token = tokens[field];
			switch(field) {
				case CALLE:
					calle = token;
					break;
				case ALT_PLANO:
					delSurroundingChar(token, '"');
					alturaPlano = std::atoi(token.c_str());
					break;
				case DIRECCION:
					if(token == "") {
						break;
					}
					direccion = token;
					break;
				case COORD_X:
					coordX = std::atof(token.c_str());
					break;
				case COORD_Y:
					coordY = std::atof(token.c_str());
					break;
				case COMUNA:
					break;
				case BARRIO:
					barrioNombre = token;
					if(barrioNombre == "") {
						barrioNombre = "NOMBRE SIN DEFINIR";
					}
					break;
				case LINEA_1:
				case LINEA_2:
				case LINEA_3:
				case LINEA_4:
				case LINEA_5:
				case LINEA_6:
					if(token == "") {
						break;
					}
					int linea;
					linea = std::atoi(token.c_str());
					lineasEnParada.push_back(linea);
					break;
				case LINEA_1_SENTIDO:
				case LINEA_2_SENTIDO:
				case LINEA_3_SENTIDO:
				case LINEA_4_SENTIDO:
				case LINEA_5_SENTIDO:
				case LINEA_6_SENTIDO:
					break;
				default:
					break;
			}
		}

		barrio = getBarrioPorNombre(barrioNombre);
		if(barrio == NULL) {
			// std::cout << "Creando nuevo barrio `" << barrioNombre << "`\n";
			barrio = new Barrio(barrioNombre);
			barrio->addParada(calle, alturaPlano, direccion, coordX, coordY, lineasEnParada);
			barrios->insert(barrio);
		} else {
			// barrio ya existe
			barrio->addParada(calle, alturaPlano, direccion, coordX, coordY, lineasEnParada);
		}
	}

	inputFile.close();
}

void Menu::mostrarMenu() {
	bool terminarPrograma = false;
	std::string opcion;
	int linea;
	Barrio *barrioActual;
	std::string barrio, barrioNombre;

	while(!terminarPrograma) {
		std::cout << "`1` Cantidad de paradas por barrio\n";
		std::cout << "`2` Parada mas cercana a una coordenada\n";
		std::cout << "`3` Listado de paradas de una linea de colectivo\n";
		std::cout << "`4` Listado de cantidad de paradas por linea de colectivo\n";
		std::cout << "`5` Listado de paradas de una linea mas cercano a una coordenada\n";
		std::cout << "`b` Imprimir barrios\n";
		std::cout << "`q` Salir\n";
		std::cout << "opcion> ";

		opcion.clear();
		std::cin >> opcion;

		if(opcion[0] == '\n') {
			continue;
		}
		switch(opcion[0]) {
			case 'b':
				this->barrios->startCursor();
				while(this->barrios->forwardCursor()) {
					std::cout << "`" << this->barrios->getCursorData()->getNombre() << "`\n";
				}
				std::cout << std::endl;
				break;
			case '1':
				cantidadDeParadasPorBarrio();
				break;
			case '2':
				/*
				double x, y;

				std::cout << "latitud> ";
				opcion.clear();
				std::cin >> opcion;
				y = std::atof(opcion.c_str());

				std::cout << "longitud> ";
				opcion.clear();
				std::cin >> opcion;
				x = std::atof(opcion.c_str());
				
				std::cout << "latitud: " << y << "; longitud: " << x << std::endl;

				Parada *parada;
				parada = paradaMasCercanaPorCoordenada(x, y);
				if(parada == NULL) {
					std::cout << "NULL POINTER";
					break;
				}
				std::cout << parada->getDireccion()
					<< " (" << parada->getCoordX() << ", " << parada->getCoordY() << ")\n";
				*/
				std::cout<<"Indique la coordenada en X: ";
				std::cin >> this->coordX;
				std::cout<<"Indique la coordenada en Y: ";
				std::cin >> this->coordY;

				paradaMasCercanaPorCoordenada(this->coordX, this->coordY);
				break;
			case '3':
				// std::cout<<"Indique la Linea: ";
				// std::cin >> this->linea;

				// paradasPorLinea(this->linea);
				// imprimirParadasPorLinea(this->paradasPorCadaLinea);

				List<Parada*> *paradas;

				std::cout << "linea> ";
				opcion.clear();
				std::cin >> linea;
				paradas = buscarParadas(barrios, linea);
				if(paradas == NULL) {
					std::cout << "no hay paradas de la linea indicada\n";
					break;
				}
				std::cout << "se encontraron `" << paradas->getSize() << "` paradas de la linea indicada\n";

				paradas->startCursor();
				while(paradas->forwardCursor()) {
					std::cout << "* `" << paradas->getCursorData()->getDireccion() << "`\n";
				}
				break;
			case '4':
				cantidadDeParadasPorLinea();

				// List<Parada*> *paradas;
				for(size_t i = 0; i < this->lineas->size(); ++i) {
					paradas = buscarParadas(barrios, (*this->lineas)[i]);
					if(paradas == NULL) {
						std::cout << "no hay paradas de la linea indicada\n";
						break;
					}
					std::cout << "se encontraron `" << paradas->getSize()
						<< "` paradas de la linea `" << (*this->lineas)[i] << " ` \n";
				}

				// imprimirCantidadParadasPorLinea(this->lineas);
				break;
			case '5':
				/* 
				 * [X] 0: obtener del usuario `barrio`, `linea` y `coordenadas`
				 * [X] 1: iterar sobre los barrios para hallar el `barrio`
				 * [X] 2: crear una lista de las paradas en el `barrio` que contienen la `linea`
				 * [X] 3: ordenar la lista de menor a mayor con respecto a la distancia a `coordenadas`
				*/

				// std::cout << "Indique el Barrio: ";
				// std::cin.ignore(1);
				// std::getline(std::cin, barrio, '\n');
				barrioNombre = "CONSTITUCION";

				// std::cout<<"Indique la Linea: ";
				// std::cin >> this->linea;
				this->linea = 154;

				// std::cout<<"Indique la coordenada en X: ";
				// std::cin >> this->coordX;
				this->coordX = 0.0f;

				// std::cout<<"Indique la coordenada en Y: ";
				// std::cin >> this->coordY;
				this->coordY = 0.0f;

				Barrio *barrio;
				List<Parada*> *paradasDeLaLinea;

				barrio = getBarrioPorNombre(barrioNombre);

				paradasDeLaLinea = barrio->listaDeParadasPorLinea(this->linea);

				// ordenar de mayor a menor `paradasDeLaLinea`
				ordenarParadasPorDistanciaACoordenada(paradasDeLaLinea, this->coordX, this->coordY);

				double distancia;
				Parada *actual;

				paradasDeLaLinea->startCursor();
				while(paradasDeLaLinea->forwardCursor()) {
					actual = paradasDeLaLinea->getCursorData();
					distancia = getDistancia(actual->getCoordX(), actual->getCoordY(), this->coordX, this->coordY);
					std::cout << actual->getDireccion() << " (distancia: `" << distancia << " `)" << std::endl;
				}

				// delete paradasDeLaLinea;

				// imprimir paradasDeLaLineaOrdenada

				// delete paradasDeLaLineaOrdenada;

				// paradasMasCercanasPorBarrio(barrio,this->linea,this->coordX,this->coordY);
				// imprimirParadasPorLinea(this->listaDeParadasCercanasOrdenadas);
				break;
			case 'q':
				terminarPrograma = true;
				break;
			default: 
				std::cout << "opcion `" << opcion[0] << "` no definida\n";
				break;
		}
	}
}

Menu::~Menu() { }
