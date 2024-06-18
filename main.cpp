#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "barrio.h"
#include "parada.h"

#define INPUT_FILE_DELIM ','

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

int main (void) {
	std::ifstream inputFile;
	std::string line;
	std::stringstream lineStream;
	std::string token;

	const char *inputFilePath = "paradas-de-colectivo.csv";

	inputFile.open(inputFilePath);
	if(!inputFile.is_open()) {
		std::cout << "No se pudo abrir el archivo `" << inputFilePath << "`\n";
		return 1;
	}

	int comuna, alturaPlano;
	double coordX, coordY;

	comuna = alturaPlano = 0;
	coordX = coordY = 0.0f;
	std::string barrioName, calle, direccion;

	std::getline(inputFile, line); // saltea la primer linea
	while(std::getline(inputFile, line)) {
		lineStream.str(line);

		size_t field = CALLE;
		while(std::getline(lineStream, token, INPUT_FILE_DELIM)) {
			// verifico que si `token` es una cadena y contiene INPUT_FILE_DELIM
			while((token[0] == '"') && (token[token.size() - 1] != '"')) {
				std::string nextToken;
				std::getline(lineStream, nextToken, INPUT_FILE_DELIM);
				token += INPUT_FILE_DELIM + nextToken;
			}

			switch(field) {
				case CALLE:
					calle = token;
					break;
				case ALT_PLANO:
					token.erase(0, 1);
					token[token.size() - 1] = '\0';
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
					token.erase(0, 1);
					token[token.size() - 1] = '\0';
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
			field++;
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
