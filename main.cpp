#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main (void) {
	std::ifstream inputFile;
	std::istringstream iss;
	std::string token;
	std::string line;

	const char *file_path = "paradas-de-colectivo.csv";

	inputFile.open(file_path);
	if(!inputFile.is_open()) {
		std::cout << "No se pudo abrir el archivo `" << file_path << "`\n";
	}

	std::getline(inputFile, line); // saltea la primer linea
	while(std::getline(inputFile, line)) {
		iss.str(line);
		while(std::getline(iss, token, ',')) {
			std::cout << ((token == "") ? "" : token.append("\n"));
		}
		iss.clear();
	}

	inputFile.close();
	return 0;
}
