#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

#include "barrio.h"
#include "menu.h"

int main (void) {
	Menu *menu = new Menu(1);
	menu->cargarDatos();

	menu->mostrarMenu();

	delete menu;
	return 0;
}
