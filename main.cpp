#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

#include "barrio.h"

#define CSV_DELIM ','

enum {
	CALLE,
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
		tokens.push_back(token);
	}

	return field;
}

void delSurroundingChar(std::string &str, char c) {
	str.erase(0, 1);
	str[str.size() - 1] = '\0';
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

int main (void) {
	std::ifstream inputFile;
	std::string token, line;
	std::vector<std::string> tokens;

	int comuna, alturaPlano;
	double coordX, coordY;
	std::string barrioNombre, calle, direccion;

	const char *inputFilePath = "paradas-de-colectivo.csv";

	inputFile.open(inputFilePath);
	if(!inputFile.is_open()) {
		std::cout << "No se pudo abrir el archivo `" << inputFilePath << "`\n";
		return 1;
	}

	comuna = alturaPlano = 0;
	coordX = coordY = 0.0f;

	std::getline(inputFile, line); // saltea la primer linea

	while(std::getline(inputFile, line)) {
		tokens.clear();
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
					break;
				case LINEA_1_SENTIDO:
					break;
				case LINEA_2:
					break;
				case LINEA_2_SENTIDO:
					break;
				case LINEA_3:
					break;
				case LINEA_3_SENTIDO:
					break;
				case LINEA_4:
					break;
				case LINEA_4_SENTIDO:
					break;
				case LINEA_5:
					break;
				case LINEA_5_SENTIDO:
					break;
				case LINEA_6:
					break;
				case LINEA_6_SENTIDO:
					break;
				default:
					break;
			}
		}

		std::cout << "{\n    \"barrio\": " << barrioName << ",\n"
			<< "    \"calle\": \"" << calle << "\",\n"
			<< "    \"comuna\": " << comuna << ",\n"
			<< "    \"direccion\": \"" << direccion << "\",\n"
			<< "    \"coordenada x\": " << coordX << ",\n"
			<< "    \"coordenada y\": " << coordY << ",\n"
			<< "    \"alturaPlano\": " << alturaPlano << "\n},\n";
		lineStream.clear();
	}

	inputFile.close();
	return 0;
}
