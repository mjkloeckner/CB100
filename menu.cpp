#include "menu.h"

void Menu::cantidadDeParadasPorBarrio() {
	this->barrios->startCursor();

	while(this->barrios->forwardCursor()) {
		Barrio * barrioAux = this->barrios->getCursorData();
		std::cout << "La cantidad de paradas que hay en el barrio "
				  << &barrioAux
				  << " es: "
				  << barrioAux->getSizeListaDeParadas()
				  << std::endl;
		}
}


void Menu::paradaMasCercanaPorCoordenada(double coordX,double coordY){
	double distanciaMinima;
	double distancia;

	Parada *paradaResultado = NULL;
	Parada *paradaActual = NULL;

	this->barrios->startCursor();
	while(this->barrios->forwardCursor()) {
		Barrio *barrioAux = this->barrios->getCursorData();

		if(paradaResultado == NULL) {
			paradaResultado = barrioAux->paradaMasCercana(coordX,coordY,barrioAux->getParadas());
			distanciaMinima = barrioAux->getDistancia(coordX,coordY,paradaResultado->getCoordX(),paradaResultado->getCoordY());
		}
		else {
			paradaActual= barrioAux->paradaMasCercana(coordX,coordY,barrioAux->getParadas());
			distancia = barrioAux->getDistancia(coordX,coordY,paradaActual->getCoordX(),paradaActual->getCoordY());

			if(distanciaMinima > distancia) {
				distanciaMinima = distancia;
				paradaResultado = paradaActual;
			}
		}
	}

	std::cout<< "La parada mas cercana esta en: "
			 << paradaResultado->getDireccion()
			 << std::endl
			 << "en la coordenada X: "
			 << paradaResultado->getCoordX()
			 << std::endl
			 << "en la coordenada Y:"
			 << paradaResultado->getCoordY()
			 << std::endl;
}

void Menu::agregarElementosDeLista(List<Parada*>* listaAux,List<Parada*>* listaResultado) {
	listaAux->startCursor();

	while(listaAux->forwardCursor()) {
		Parada *paradaAux = listaAux->getCursorData();

		listaResultado->insert(paradaAux);
	}
}

void Menu::imprimirParadasPorLinea(List<Parada*>* listaDeParadas) {
	if(listaDeParadas->getSize() == 0){
		std::cout<<"No se econtro ninguna parada para esta linea";
		throw "No se econtro ninguna parada para esta linea";
	}

	listaDeParadas->startCursor();
		while(listaDeParadas->forwardCursor()){
			Parada *paradaAux = listaDeParadas->getCursorData();

			std::cout << "La parada esta en: "
					  << paradaAux->getDireccion()
					  << std::endl
					  << "en la coordenada X: "
					  << paradaAux->getCoordX()
					  << std::endl
					  << "en la coordenada Y:"
					  << paradaAux->getCoordY()
					  << std::endl;
		}
}

void Menu::paradasPorLinea(int linea){
	if(linea >= 0){
		std::cout<<"La linea no existe, no puede ser menor o igual a cero";
		throw "La linea no existe, no puede ser menor o igual a cero";
	}

	this->paradasPorCadaLinea = NULL;
	List<Parada*> *listaAux = new List<Parada*>();

	this->barrios->startCursor();
	while(this->barrios->forwardCursor()){
		Barrio *barrioAux = this->barrios->getCursorData();

		listaAux = barrioAux->listaDeParadasPorLinea(linea);
		agregarElementosDeLista(listaAux, this->paradasPorCadaLinea);
	}

}

void Menu::agregarElementoSinRepetir(std::vector<int>* lineas, std::vector<int>* vectorLineasAux){

	unsigned int contador = 0;
	size_t lineaTope = lineas->size();

	for(size_t i=0; i<lineaTope;i++){

		for(size_t j=0; j<vectorLineasAux->size();j++){

			if((*vectorLineasAux)[j] == (*lineas)[i]){

				contador++;

			}

			if(contador == 0){
				lineas->push_back((*vectorLineasAux)[j]);
			}
			contador = 0;

		}
	}
}


void Menu::lineasPorParada(List<Parada*>* paradas){

	paradas->startCursor();
	while(paradas->forwardCursor()){

		Parada * paradaAux = paradas->getCursorData();

		std::vector<int>* vectorLineasAux = paradaAux->getLineas();

		agregarElementoSinRepetir(this->lineas, vectorLineasAux);


	}

}

void Menu::imprimirCantidadParadasPorLinea(std::vector<int>* lineas){

	for(size_t i=0;i<lineas->size();i++){

		paradasPorLinea((*lineas)[i]);
		std::cout<<(*lineas)[i]
			     <<" : "
				 <<this->paradasPorCadaLinea->getSize()
				 <<std::endl;
	}
}


void Menu::cantidadDeParadasPorLinea(){

	this->lineas = NULL;
	this->barrios->startCursor();

	while(this->barrios->forwardCursor()){

		Barrio * barrioAux = this->barrios->getCursorData();

		lineasPorParada(barrioAux->getParadas());

	}

}

void Menu::removerParadaMasCercana(List<Parada*>*listaAux,Parada * paradaCercana){

	listaAux->startCursor();
	unsigned int posicion = 0;

	while(listaAux->forwardCursor()){

		posicion ++;
		Parada * paradaAux = listaAux->getCursorData();

		if(paradaAux == paradaCercana){

			listaAux->remove(posicion);

	 }
	}
}

void Menu::listaOrdenadaPorDistancia(List<Parada*>* listaAux,double coordX,double coordY, Barrio * barrioAux){

	List<Parada*>* listaDeParadasCercanas = NULL;
	size_t tamanioListaAux = listaAux->getSize();

	for(size_t i=0;i<tamanioListaAux;i++){ //probar cuantas iteraciones hacer

		Parada * paradaCercana = barrioAux->paradaMasCercana(coordX,coordY,listaAux);
		listaDeParadasCercanas->insert(paradaCercana);
		removerParadaMasCercana(listaAux, paradaCercana);

	}

}


void Menu::paradasMasCercanasPorBarrio(std::string barrio,int linea,double coordX,double coordY){

	this->barrios->startCursor();
	List<Parada*>* listaAux = NULL;

	while(this->barrios->forwardCursor()){

		Barrio * barrioAux = this->barrios->getCursorData();

		if(barrio == barrioAux->getNombre())

			listaAux = barrioAux->listaDeParadasPorLinea(linea);

			listaOrdenadaPorDistancia(listaAux,coordX,coordY, barrioAux);

	}

}


Menu::Menu(int opcion) {
	this->opcion = opcion;
	this->barrios = new List<Barrio*>;
	this->lineas = new std::vector<int>;
	//inicializar las demas listas!!!!!!!!

	std::cout << "1) Listado de cantidad de paradas por Barrio"<<std::endl  //HECHO!!!!!!!!!!
			  << "2) Parada mas cercana a una coordenada ingresada por teclado"<<std::endl //HECHO!!!!!!!!!!
			  << "3) Listado de paradas de una linea de colectivo"<<std::endl //HECHO!!!!!!!!!!
			  << "4) Listado de cantidad de paradas por linea de colectivo"<<std::endl //HECHO!!!!!!!!!!
			  << "5) Dado un barrio, linea de colectivo y una coord, imprimir las paradas ordenadas por distancia"<<std::endl;

	switch(opcion) {
	case 1:
		cantidadDeParadasPorBarrio();
		break;
	case 2:
		std::cout<<"Indique la coordenada en X: ";
		std::cin >> this->coordX;
		std::cout<<"Indique la coordenada en Y: ";
		std::cin >> this->coordY;

		paradaMasCercanaPorCoordenada(this->coordX, this->coordY);
		break;
	case 3:
		std::cout<<"Indique la Linea: ";
		std::cin >> this->linea;

		paradasPorLinea(this->linea);
		imprimirParadasPorLinea(this->paradasPorCadaLinea);

		break;
	case 4:
		cantidadDeParadasPorLinea();
		imprimirCantidadParadasPorLinea(this->lineas);
		break;
	case 5:

		std::cout<<"Indique el Barrio: ";
		std::cin >> this->barrio;
		std::cout<<"Indique la Linea: ";
		std::cin >> this->linea;
		std::cout<<"Indique la coordenada en X: ";
		std::cin >> this->coordX;
		std::cout<<"Indique la coordenada en Y: ";
		std::cin >> this->coordY;

		paradasMasCercanasPorBarrio(this->barrio,this->linea,this->coordX,this->coordY);

		imprimirParadasPorLinea(this->listaDeParadasCercanas);

		break;
	default:
		std::cerr << "Opcion invalida\n";
		break;
	}
}

Menu::~Menu() { }
