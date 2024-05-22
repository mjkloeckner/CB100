#include <iostream>
#include <string>

class Comentario { 
	std::string comment;
	int score;

public: 
	// post: inicializa el Comentario con el contenido y calificación 0.
	Comentario(std::string contenido) {
		this->comment = contenido;
	}

	std::string obtenerContenido() {
		return comment;
	}

	// post: devuelve la calificación [1 a 10] asociada,
	//       o 0 si el Comentario no tiene calificación
	int obtenerCalificacion() {
		return this->score;
	}

	// pre: calificacion está comprendido entre 1 y 10
	// post: cambia la calificación del Comentario
	void calificar(int calificacion) {
		this->score = calificacion;
	}
};

template <typename Type>
class Lista {
private:
	Nodo<Type> *lista;
	unsigned int length;

public:
	Lista() {
		this->current = new Type;
		this->next = NULL;
	}

	virtual ~Lista() {
		delete this->next;
		this->next = NULL;
	}

	void Add(Type node) {
		this->next = new Type;
	}
};

class Imagen {
private:
	std::string url;
public: 
	// post: inicializa la Imagen alojada en la URL indicada
	Imagen(std::string url) {
		this->url = url;
	}

	// post: devuelve la URL en la que está alojada
	std::string obtenerUrl(); 

	// post: devuelve los comentarios asociados
	Lista<Comentario*> *obtenerComentarios(); 

	virtual ~Imagen() {}
}; 


class Editor {
public: 
	// post: selecciona de ‘imagenesDisponibles’ aquella que tenga por lo
	//       menos tantos Comentarios como los indicados y
	//       el promedio de calificaciones sea máximo. Ignora los
	//       Comentarios sin calificación. 
	Imagen *seleccionarImagen(Lista<Imagen*> *availableImgs, int commentsLen) {
		if(commentsLen < 0) {
			throw "`commentsLen` no puede ser negativo";
		}

		while(availableImgs->obtenerComentarios() != NULL) {
			if(availableImgs->obtenerComentarios()) {
				return NULL;
			}
		}
	}
}; 

int main () {
	std::cout << "Hello, World!\n";
	return 0;
}
