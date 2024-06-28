#include "menu.h"

int main (void) {
	Menu *menu = new Menu();

	if(menu->cargarDatos() < 0) {
		return -1;
	}
	menu->mostrarMenu();

	delete menu;
	return 0;
}
