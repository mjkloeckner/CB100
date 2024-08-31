#include "menu.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cctype>

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
	double distanciaMin;
	double distancia;

	Parada *res, *parada;
	Barrio *barrio;

	res = NULL;
	this->barrios->startCursor();
	while(this->barrios->forwardCursor()) {
		barrio = this->barrios->getCursorData();

		if(res == NULL) {
			res = barrio->paradaMasCercana(coordX, coordY);
			distanciaMin = getDistancia(coordX, coordY, res->getCoordX(), res->getCoordY());
		}
		else {
			parada = barrio->paradaMasCercana(coordX, coordY);
			distancia = getDistancia(coordX, coordY, parada->getCoordX(), parada->getCoordY());

			if(distanciaMin > distancia) {
				distanciaMin = distancia;
				res = parada;
			}
		}
	}

	return res;
}

void Menu::agregarElementoSinRepetir(std::vector<int> *lineas, std::vector<int> *vectorLineasAux) {
	size_t lineaTope = vectorLineasAux->size();

	for(size_t i = 0; i < lineaTope; i++) {
		bool seRepite = false;
		for(size_t j = 0; j < lineas->size(); j++) {
			if((*vectorLineasAux)[i] == (*lineas)[j]) {
				seRepite = true;
			}
		}
		if(seRepite == false) {
			lineas->push_back((*vectorLineasAux)[i]);
		}
	}
}

void Menu::lineasPorParada(List<Parada*> *paradas) {
	Parada *paradaAux;
	std::vector<int> *vectorLineasAux;

	paradas->startCursor();
	while(paradas->forwardCursor()){
		paradaAux = paradas->getCursorData();

		vectorLineasAux = paradaAux->getLineas();
		agregarElementoSinRepetir(this->lineas, vectorLineasAux);
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
}

std::string strToLowercase(std::string str) {
	std::string res;
	for(size_t i = 0; i < str.size(); ++i) {
		res += std::tolower(str[i]);
	}

	return res;
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
	token.clear();

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
		if(strToLowercase(barrio->getNombre()) == strToLowercase(nombre)) {
			res = this->barrios->getCursorData();
			break;
		}
	}

	return res;
}

double gradosARadianes(double grados) {
	return grados * M_PI / 180.0;
}

// lat -> y; lon -> x;
// calcula la distancia en km entre dos coordenadas usando la formula de Lambert
double getDistanciaEnKilometros(double x1, double y1, double x2, double y2) {
	const double R = 6371.0;  // radio de la tierra

	double x1Rad = gradosARadianes(x1);
	double y1Rad = gradosARadianes(y1);
	double x2Rad = gradosARadianes(x2);
	double y2Rad = gradosARadianes(y2);

	double dLon = x2Rad - x1Rad;
	double dLat = y2Rad - y1Rad;

	double a = sin(dLat / 2) * sin(dLat / 2) + cos(y1Rad) * cos(y2Rad) * sin(dLon / 2) * sin(dLon / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	double distancia = R * c;

	return distancia;
}

double Menu::getDistancia(double x1, double y1, double x2, double y2) {
	double dX = (x2 - x1);
	double dY = (y2 - y1);

	return std::sqrt(dX*dX + dY*dY);
}

void ordenarParadasPorDistanciaACoordenada(List<Parada*> *paradas, double x, double y) {
	Node<Parada*> *actual, *min, *sig;
	Parada *tmp;

	double distMin, distSig;

	paradas->startCursor();
	while(paradas->forwardCursor()) {
		actual = paradas->getCursor();
		min = actual;

		distMin = getDistanciaEnKilometros(min->getData()->getCoordX(), min->getData()->getCoordY(), x, y);

		sig = actual->getNext();
		while (sig != NULL) {
			distSig = getDistanciaEnKilometros(sig->getData()->getCoordX(), sig->getData()->getCoordY(), x, y);

			if (distSig < distMin) {
				min = sig;
				distMin = distSig;
			}
			sig = sig->getNext();
		}

		if (min != actual) {
			tmp = actual->getData();
			actual->setData(min->getData());
			min->setData(tmp);
		}
	}
}

int Menu::cargarDatos() {
	std::ifstream inputFile;
	std::string token, line;
	std::vector<std::string> tokens;
	std::vector<int> lineasEnParada;
	float coordX, coordY;
	Barrio *barrio;

	const char *inputFilePath = "paradas-de-colectivo.csv";

	int fields, linea;
	std::string barrioNombre, calle, direccion;

	inputFile.open(inputFilePath);
	if(!inputFile.is_open()) {
		std::cout << "No se pudo abrir el archivo `" << inputFilePath << "`\n";
		return -1;
	}

	coordX = coordY = 0.0f;

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
			barrio = new Barrio(barrioNombre);
			barrio->addParada(calle, direccion, coordX, coordY, lineasEnParada);
			barrios->insert(barrio);
		} else {
			// barrio ya existe
			barrio->addParada(calle, direccion, coordX, coordY, lineasEnParada);
		}
	}

	inputFile.close();
	return 0;
}

void Menu::mostrarMenu() {
	bool terminarPrograma = false;
	int linea;
	double lat, lon; // lat -> Y; lon -> X;
	double distanciaEnKm;

	std::string opcion, barrioNombre, lineaAImprimir, distanciaUnidad;
	List<Parada*> *paradas, *paradasDeLaLinea;
	Parada *actual;
	Barrio *barrio;

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
				// TODO: verificar que `latitud` y `longitud` sean validas
				std::cin.clear();
				std::cout << "latitud> ";
				std::cin >> lat;

				std::cin.clear();
				std::cout << "longitud> ";
				std::cin >> lon;

				// std::cout << "latitud: " << lat << "; longitud: " << lon << "\n";

				Parada *parada;
				parada = paradaMasCercanaPorCoordenada(lon, lat);
				if(parada == NULL) {
					std::cout << "Parada inaccessible";
					break;
				}

				distanciaEnKm = getDistanciaEnKilometros(lon, lat, parada->getCoordX(), parada->getCoordY());

				if(distanciaEnKm < 1) {
					distanciaEnKm *= 1000.0f;
					distanciaUnidad.assign("metros");
				} else {
					distanciaUnidad.assign("kilometros");
				}

				std::cout << "Parada mas cercana: `" << parada->getDireccion()
						<< "` (" << parada->getCoordX() << ", " << parada->getCoordY()
						<< ") a " << std::fixed << std::setprecision(2) << distanciaEnKm
						<< " " << distanciaUnidad << "\n";
				break;
			case '3':
				// TODO: verificar que `linea` sea valida

				std::cin.clear();
				std::cout << "linea> ";
				std::cin >> linea;

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
				delete paradas;
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

				paradas = NULL;
				for(size_t i = 0; i < this->lineas->size(); ++i) {
					paradas = buscarParadas(barrios, (*this->lineas)[i]);
					if(paradas == NULL) {
						std::cout << "no hay paradas de la linea indicada\n";
						continue;
					}

					std::ostringstream sstream;
					sstream << "Linea " << (*this->lineas)[i];
					lineaAImprimir = sstream.str();

					std::cout << std::left << std::setw(18) << lineaAImprimir
							 << std::right << std::setw(20) << paradas->getSize()
							 << std::endl;
				}

				std::cout << std::endl;
				if(paradas != NULL) {
					delete paradas;
				}
				break;
			case '5':
				std::cout << "barrio> ";
				std::cin.ignore(1);
				std::getline(std::cin, barrioNombre, '\n');

				std::cin.clear();
				std::cout << "linea> ";
				std::cin >> linea;
		
				// TODO: verificar que `latitud` y `longitud` sean validas
				std::cin.clear();
				std::cout << "latitud> ";
				std::cin >> lat;

				std::cin.clear();
				std::cout << "longitud> ";
				std::cin >> lon;

				if((barrio = getBarrioPorNombre(barrioNombre)) == NULL) {
					std::cout << "No se encontro el barrio `" << barrioNombre << "`\n";
					break;
				}

				paradasDeLaLinea = barrio->listaDeParadasPorLinea(linea);
				if(paradasDeLaLinea == NULL) {
					std::cout << "La linea `" << linea
						<< "` no tiene paradas en el barrio `" << barrioNombre << "`\n";
					break;
				}

				// ordenar de mayor a menor distancia a `lat, lon` la lista `paradasDeLaLinea`
				ordenarParadasPorDistanciaACoordenada(paradasDeLaLinea, lon, lat);

				std::cout << std::endl;
				std::cout.fill(' ');
				std::cout << std::left << std::setw(18) << std::left << "Direccion"
						<< std::right << std::setw(35) << "Distancia en Kilometros"
						<< std::right << std::setw(30) << "Coordenadas (lat, lon)" << std::endl;
				std::cout.fill('=');
				std::cout << std::left << std::setw(83) << std::left << "=" << std::endl;

				paradasDeLaLinea->startCursor();
				while(paradasDeLaLinea->forwardCursor()) {
					actual = paradasDeLaLinea->getCursorData();
					distanciaEnKm = getDistanciaEnKilometros(lon, lat, actual->getCoordY(), actual->getCoordX());

					std::string coord;
					coord += actual->getCoordX();

					std::cout.fill('.');
					std::cout << std::left << std::setw(33) << actual->getDireccion()
								<< std::right << std::setw(20)
								<< std::fixed << std::setprecision(2)
								<< distanciaEnKm;

					std::cout.fill('.');
					std::cout << std::right << std::setw(10) << std::setprecision(4)
								<< "(" << actual->getCoordX();

					std::cout.fill(' ');
					std::cout << "," << std::right << std::setw(10) << std::setprecision(4)
								<< actual->getCoordY() << ")" << std::endl;
				}
				std::cout << std::endl;

				delete paradasDeLaLinea;
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

Menu::~Menu() {
	Barrio *delBarrio;

	this->barrios->startCursor();
	while(this->barrios->forwardCursor()){
		delBarrio = this->barrios->getCursorData();
		delete delBarrio;
	}

	delete this->barrios;
	delete this->lineas;
}
