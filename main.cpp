#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

#include "barrio.h"

#define CSV_DELIM ','

enum {
	CALLE = 0,
	ALT_PLANO,
	DIRECCION,
	COORD_X,
	COORD_Y,
	COMUNA,
	BARRIO,
	LINEA_1,
	LINEA_1_SENTIDO,
	LINEA_2,
	LINEA_2_SENTIDO,
	LINEA_3,
	LINEA_3_SENTIDO,
	LINEA_4,
	LINEA_4_SENTIDO,
	LINEA_5,
	LINEA_5_SENTIDO,
	LINEA_6,
	LINEA_6_SENTIDO
};

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

// busca el barrio en la lista de barrios, si no lo encuentra devuelve NULL
Barrio *getBarrioPorNombre(std::string nombre, List<Barrio*> *barrios) {
	if(barrios == NULL) {
		return NULL;
	}

	Barrio *res = NULL;

	barrios->startCursor();
	while(barrios->forwardCursor()) {
		if(barrios->getCursorData()->getNombre() == nombre) {
			res = barrios->getCursorData();
		}
	}

	return res;
}

Parada *paradaMasCercanaPorCoordenada(List<Barrio*> *barrios, double x, double y) {
	double distancia;
	double distanciaMinima;
	Parada *resultado, *paradaActual;

	distancia = distanciaMinima = 0.0f;
	resultado = paradaActual = NULL;

	barrios->startCursor();
	while(barrios->forwardCursor()) {
		Barrio *barrioAux = barrios->getCursorData();

		if(resultado == NULL) {
			resultado = barrioAux->paradaMasCercana(x, y);
			if(resultado == NULL) {
				return NULL;
			}
			distanciaMinima = barrioAux->getDistancia(x, y, resultado->getCoordX(), resultado->getCoordY());
			continue;
		}
		paradaActual = barrioAux->paradaMasCercana(x, y);
		if(paradaActual == NULL) {
			continue;
		}
		distancia = barrioAux->getDistancia(x, y, paradaActual->getCoordX(), paradaActual->getCoordY());
		if(distanciaMinima > distancia) {
			distanciaMinima = distancia;
			resultado = paradaActual;
		}
	}

	std::cout << "distancia: " << distancia << std::endl;
	return resultado;
}

List<Parada*> *buscarParadas(List<Barrio*> *barrios, int linea) {
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

int main (void) {
	std::ifstream inputFile;
	std::string token, line;
	std::vector<std::string> tokens;
	Barrio *barrio;
	List<Barrio*> *barrios;

	int comuna, alturaPlano, fields;
	double coordX, coordY;
	std::string barrioNombre, calle, direccion;
	std::vector<int> lineasEnParada;

	const char *inputFilePath = "paradas-de-colectivo.csv";

	inputFile.open(inputFilePath);
	if(!inputFile.is_open()) {
		std::cout << "No se pudo abrir el archivo `" << inputFilePath << "`\n";
		return 1;
	}

	comuna = alturaPlano = 0;
	coordX = coordY = 0.0f;
	barrios = new List<Barrio*>;

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
					delSurroundingChar(token, '"');
					comuna = std::atoi(token.c_str());
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

		barrio = getBarrioPorNombre(barrioNombre, barrios);
		if(barrio == NULL) {
			// std::cout << "Creando nuevo barrio `" << barrioNombre << "`\n";
			barrio = new Barrio(barrioNombre, comuna);
			barrio->addParada(calle, alturaPlano, direccion, coordX, coordY, lineasEnParada);
			barrios->insert(barrio);
		} else {
			// barrio ya existe
			barrio->addParada(calle, alturaPlano, direccion, coordX, coordY, lineasEnParada);
		}
	}

	inputFile.close();

	bool terminarPrograma = false;
	std::string opcion;
	int linea;

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
				barrios->startCursor();
				while(barrios->forwardCursor()) {
					std::cout << "`" << barrios->getCursorData()->getNombre() << "`\n";
				}
				std::cout << std::endl;
				break;
			case '1':
				barrios->startCursor();
				while(barrios->forwardCursor()) {
					barrio = barrios->getCursorData();
					std::cout << "`" << barrio->getNombre() << "`: "
						<< barrio->getSizeListaDeParadas() << "\n";
				}
				std::cout << std::endl;
				break;
			case '2':
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
				parada = paradaMasCercanaPorCoordenada(barrios, x, y);
				if(parada == NULL) {
					std::cout << "NULL POINTER";
					break;
				}
				std::cout << parada->getDireccion()
					<< " (" << parada->getCoordX() << ", " << parada->getCoordY() << ")\n";
				break;
			case '3':
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
				break;
			case '5':
				std::cout << "linea> ";
				opcion.clear();
				std::cin >> linea;

				paradas = buscarParadas(barrios, linea);
				if(paradas == NULL) {
					std::cout << "no hay paradas de la linea indicada\n";
					break;
				}
				std::cout << "existen `" << paradas->getSize() << "` paradas de la linea indicada\n";

				break;
			case 'q':
				terminarPrograma = true;
				break;
			default: 
				std::cout << "opcion `" << opcion[0] << "` no definida\n";
				break;
		}
	}

	// std::cout << "Total barrios creados: " << barrios->getSize() << std::endl;

	barrios->startCursor();
	while(barrios->forwardCursor()) {
		// std::cout << "Eliminando barrio `" << barrios->getCursorData()->getNombre() << "`\n";
		delete barrios->getCursorData();
	}

	delete barrios;
	return 0;
}
