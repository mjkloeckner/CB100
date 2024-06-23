#include "menu.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iomanip>

void Menu::imprimirCantidadDeParadasPorBarrio() {
	Barrio *barrio;

	std::cout << std::endl;
	std::cout << std::setw(10);
	std::cout.fill(' ');

	std::cout << std::left << std::setw(18) << std::left << "Barrio";
	std::cout << std::right << std::setw(20) << "Cantidad de Paradas" << std::endl;
	std::cout.fill('=');
	std::cout << std::left << std::setw(38) << std::left << "=" << std::endl;

	std::cout.fill('.');
	this->barrios->startCursor();
	while(this->barrios->forwardCursor()) {
		barrio = this->barrios->getCursorData();
		std::cout << std::left << std::setw(18) << barrio->getNombre()
				 << std::right << std::setw(20) << barrio->getSizeListaDeParadas()
				 << std::endl;
	}

	std::cout << std::endl;
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

	paradas->startCursor();
	while(paradas->forwardCursor()){
		paradaAux = paradas->getCursorData();

		vectorLineasAux = paradaAux->getLineas();
		agregarElementoSinRepetir(this->lineas, vectorLineasAux);
	}
}

void Menu::imprimirCantidadParadasPorLinea(std::vector<int>* lineas){
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
	Barrio *barrio;

	this->lineas->clear();
	this->barrios->startCursor();

	while(this->barrios->forwardCursor()){
		barrio = this->barrios->getCursorData();

		lineasPorParada(barrio->getParadas());
	}
}

Menu::Menu() {
	this->barrios = new List<Barrio*>;
	this->lineas = new std::vector<int>;

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

	int fields, linea;
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
			barrio->addParada(calle, direccion, coordX, coordY, lineasEnParada);
			barrios->insert(barrio);
		} else {
			// barrio ya existe
			barrio->addParada(calle, direccion, coordX, coordY, lineasEnParada);
		}
	}

	inputFile.close();
}

void Menu::mostrarMenu() {
	bool terminarPrograma = false;
	std::string opcion;
	int linea;
	double lat, lon; // lat -> Y; lon -> X;
	std::string barrio, barrioNombre, lineaAImprimir;

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
				imprimirCantidadDeParadasPorBarrio();
				break;
			case '2':
				do {
					std::cin.clear();
					std::string line;
					std::getline(std::cin, line);
					std::cout << "latitud> ";
					std::cin >> lat;
				} while(std::cin.fail());

				do {
					std::cin.clear();
					std::string line;
					std::getline(std::cin, line);
					std::cout << "longitud> ";
					std::cin >> lon;
				} while(std::cin.fail());

				std::cout << "latitud: " << lat << "; longitud: " << lon << "\n";

				Parada *parada;
				parada = paradaMasCercanaPorCoordenada(lon, lat);
				if(parada == NULL) {
					std::cout << "Parada inaccessible";
					break;
				}

				std::cout << "La parada mas cercana esta en: `" << parada->getDireccion()
						<< "` (" << parada->getCoordX() << ", " << parada->getCoordY() << ")\n";
				break;
			case '3':
				List<Parada*> *paradas;

				do {
					std::cin.clear();
					std::string line;
					std::getline(std::cin, line);
					std::cout << "linea> ";
					std::cin >> linea;
				} while(std::cin.fail());

				paradas = buscarParadas(barrios, linea);
				if(paradas == NULL) {
					std::cout << "no hay paradas de la linea indicada\n";
					break;
				}
				std::cout << "La linea `" << linea << "` tiene `"
					<< paradas->getSize() << "` paradas en CABA\n";

				paradas->startCursor();
				while(paradas->forwardCursor()) {
					std::cout << " · " << paradas->getCursorData()->getDireccion() << "\n";
				}

				// paradasPorLinea(this->linea);
				// imprimirParadasPorLinea(this->paradasPorCadaLinea);
				break;
			case '4':
				cantidadDeParadasPorLinea();

				std::cout << std::endl;
				std::cout << std::setw(10);
				std::cout.fill(' ');

				std::cout << std::left << std::setw(18) << std::left << "Linea";
				std::cout << std::right << std::setw(20) << "Cantidad de Paradas" << std::endl;
				std::cout.fill('=');

				std::cout << std::left << std::setw(38) << std::left << "=" << std::endl;
				std::cout.fill('.');

				for(size_t i = 0; i < this->lineas->size(); ++i) {
					paradas = buscarParadas(barrios, (*this->lineas)[i]);
					if(paradas == NULL) {
						std::cout << "no hay paradas de la linea indicada\n";
						break;
					}

					std::ostringstream sstream;
					sstream << "Linea " << (*this->lineas)[i];
					lineaAImprimir = sstream.str();

					std::cout << std::left << std::setw(18) << lineaAImprimir
							 << std::right << std::setw(20) << paradas->getSize()
							 << std::endl;
				}

				std::cout << std::endl;

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
				// std::cin >> lon;
				lon = 0.0f;

				// std::cout<<"Indique la coordenada en Y: ";
				// std::cin >> lat;
				lat = 0.0f;

				Barrio *barrio;
				List<Parada*> *paradasDeLaLinea;

				barrio = getBarrioPorNombre(barrioNombre);

				paradasDeLaLinea = barrio->listaDeParadasPorLinea(this->linea);

				// ordenar de mayor a menor `paradasDeLaLinea`
				ordenarParadasPorDistanciaACoordenada(paradasDeLaLinea, lon, lat);

				double distancia;
				Parada *actual;

				paradasDeLaLinea->startCursor();
				while(paradasDeLaLinea->forwardCursor()) {
					actual = paradasDeLaLinea->getCursorData();
					distancia = getDistancia(actual->getCoordX(), actual->getCoordY(), lon, lat);
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
