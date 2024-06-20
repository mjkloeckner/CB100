#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "barrio.h"
#include "parada.h"

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

void delSurroundingChar(std::string &str, char c) {
	str.erase(0, 1);
	str[str.size() - 1] = '\0';
} 

int main (void) {
	std::ifstream inputFile;
	std::string line, token;
	std::stringstream lineStream;

	int comuna, alturaPlano;
	double coordX, coordY;
	std::string barrioName, calle, direccion;

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
		lineStream.str(line);

		for(size_t field = CALLE; std::getline(lineStream, token, CSV_DELIM); ++field) {
			// solucion a `token` es una cadena que contiene CSV_DELIM
			while((token[0] == '"') && (token[token.size() - 1] != '"')) {
				std::string nextToken;
				std::getline(lineStream, nextToken, CSV_DELIM);
				token += CSV_DELIM + nextToken;
			}

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
				barrioName = token;
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
