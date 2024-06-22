#include "menu.h"

int main (void) {
	Menu *menu = new Menu();

	menu->cargarDatos();
	menu->mostrarMenu();

	delete menu;
	return 0;
}
