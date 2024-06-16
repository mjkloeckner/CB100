#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "list.h"

#define INPUT_FILE_DELIM ','

int main (void) {
	std::ifstream inputFile;
	std::istringstream iss;
	std::string line;
	std::string token;
	List<std::string> tokens;

	const char *file_path = "paradas-de-colectivo.csv";

	inputFile.open(file_path);
	if(!inputFile.is_open()) {
		std::cout << "No se pudo abrir el archivo `" << file_path << "`\n";
		return 1;
	}

	std::getline(inputFile, line); // saltea la primer linea
	while(std::getline(inputFile, line)) {
		iss.str(line);
		while(std::getline(iss, token, INPUT_FILE_DELIM)) {
			tokens.insert(token);
		}
		iss.clear();
	}

	inputFile.close();

	tokens.startCursor();
	while(tokens.forwardCursor()) {
		token = tokens.getCursorData();
		std::cout << ((token == "") ? "" : token.append("\n"));
	}

	return 0;
}
