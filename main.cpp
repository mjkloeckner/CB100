#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define INPUT_FILE_DELIM ','

int main (void) {
	std::ifstream inputFile;
	std::istringstream iss;
	std::string token;
	std::string line;

	const char *file_path = "paradas-de-colectivo.csv";

	inputFile.open(file_path);
	if(!inputFile.is_open()) {
		std::cout << "No se pudo abrir el archivo `" << file_path << "`\n";
		return 1;
	}

	std::getline(inputFile, line); // saltea la primer linea
	while(std::getline(inputFile, line)) {
		iss.str(line);
			std::cout << ((token == "") ? "" : token.append("\n"));
		while(std::getline(iss, token, INPUT_FILE_DELIM)) {
		}
		iss.clear();
	}

	inputFile.close();
	return 0;
}
