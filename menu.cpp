#include "menu.h"


void Menu::cantidadDeParadasPorBarrio(){

	this->barrios->startCursor();

	while(this->barrios->forwardCursor()){

		Barrio * barrioAux = this->barrios->getCursorData();

		std::cout<<"La cantidad de paradas que hay en el barrio "
				 <<&barrioAux
				 <<" es: "
				 <<barrioAux->getSizeListaDeParadas()
				 <<std::endl;
		}
	}

void Menu::paradaMasCercanaPorCoordenada(double coordX,double coordY){

	double distanciaMinima;
	double distancia;

	Parada * paradaResultado = NULL;
	Parada * paradaActual = NULL;

	this->barrios->startCursor();

	while(this->barrios->forwardCursor()){


		Barrio * barrioAux = this->barrios->getCursorData();

		if(paradaResultado == NULL){

			paradaResultado = barrioAux->paradaMasCercana(coordX,coordY);
			distanciaMinima = barrioAux->getDistancia(coordX,coordY,paradaResultado->getCoordX(),paradaResultado->getCoordY());
		}
		else {

			paradaActual= barrioAux->paradaMasCercana(coordX,coordY);
			distancia = barrioAux->getDistancia(coordX,coordY,paradaActual->getCoordX(),paradaActual->getCoordY());

			if(distanciaMinima > distancia){

				distanciaMinima = distancia;
				paradaResultado = paradaActual;
			}
		}
	}

	std::cout<<"La parada mas cercana esta en: "
			 <<paradaResultado->getDireccion()
			 <<std::endl
			 <<"en la coordenada X: "
			 <<paradaResultado->getCoordX()
			 <<std::endl
			 <<"en la coordenada Y:"
			 <<paradaResultado->getCoordY()
			 <<std::endl;
}

void Menu::agregarElementosDeLista(List<Parada*>* listaAux,List<Parada*>* listaResultado){

	listaAux->startCursor();
	while(listaAux->forwardCursor()){

		Parada * paradaAux = listaAux->getCursorData();

		listaResultado->insert(paradaAux);
	}

}

void Menu::imprimirParadasPorLinea(List<Parada*>* listaDeParadas){

	if(listaDeParadas->getSize() == 0){
		std::cout<<"No se econtro ninguna parada para esta linea";
		throw "No se econtro ninguna parada para esta linea";
	}

	listaDeParadas->startCursor();
		while(listaDeParadas->forwardCursor()){

			Parada * paradaAux = listaDeParadas->getCursorData();

			std::cout<<"La parada esta en: "
					 <<paradaAux->getDireccion()
					 <<std::endl
					 <<"en la coordenada X: "
					 <<paradaAux->getCoordX()
					 <<std::endl
					 <<"en la coordenada Y:"
					 <<paradaAux->getCoordY()
					 <<std::endl;
		}
}



void Menu::paradasPorLinea(int linea){

	if(linea >= 0){
		std::cout<<"La linea no existe, no puede ser menor o igual a cero";
		throw "La linea no existe, no puede ser menor o igual a cero";
	}

	this->paradasPorCadaLinea = NULL;

	List<Parada*>* listaAux = new List<Parada*>();

	this->barrios->startCursor();

	while(this->barrios->forwardCursor()){

		Barrio * barrioAux = this->barrios->getCursorData();

		listaAux = barrioAux->listaDeParadasPorLinea(linea);



		agregarElementosDeLista(listaAux, this->paradasPorCadaLinea);

	}

	imprimirParadasPorLinea(this->paradasPorCadaLinea);
}

void Menu::cantidadDeParadasPorLinea(){

	this->barrios->startCursor();
	while(this->barrios->forwardCursor()){

	Barrio * barrioAux = this->barrios->getCursorData();

	List<Parada*>* listaParadas = barrioAux->getParadas();

	 // Falta terminar

	}







}





Menu::Menu(int opcion) {

	this->opcion = opcion;
	this->barrios = new List<Barrio*>();

	// agregar barrios a la lista con tda archivos(main modularizado)



	if(opcion < 1 && opcion > 5){
	std::cout<<"No se ingreso una opcion valida"<<std::endl;
	throw "No se ingreso una opcion valida";
	}

	std::cout<<"1) Listado de cantidad de paradas por Barrio"<<std::endl  //HECHO!!!!!!!!!!
			 <<"2) Parada mas cercana a una coordenada ingresada por teclado"<<std::endl //HECHO!!!!!!!!!!
			 <<"3) Listado de paradas de una linea de colectivo"<<std::endl //HECHO!!!!!!!!!!
			 <<"4) Listado de cantidad de paradas por linea de colectivo"<<std::endl
			 <<"5) Dado un barrio y linea de colectivo, imprimir las paradas ordenadas por distancia"<<std::endl;

	if(opcion == 1){
		cantidadDeParadasPorBarrio();
	}

	else if(opcion == 2){

		std::cout<<"Indique la coordenada en X: ";
		std::cin>>this->coordX;

		std::cout<<"Indique la coordenada en Y: ";
		std::cin>>this->coordY;

		paradaMasCercanaPorCoordenada(this->coordX,this->coordY);
	}

	else if(opcion == 3){

		std::cout<<"Indique la Linea: ";
				std::cin>>this->linea;

		paradasPorLinea(this->linea);

	}

	else if(opcion == 4){

		cantidadDeParadasPorLinea();


	}

	else if(opcion == 5){

		//completar


	}

}

Menu::~Menu() {
	// TODO Auto-generated destructor stub
}

