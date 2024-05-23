#include <iostream>
#include <string>

template <typename Type>
class Node {
private:
	Node<Type> *next;
	Type data;

public:
	Node() {
		this->next = NULL;
	}

	Node(Type data) {
		this->next = NULL;
		this->data = data;
	}

	Node<Type> *getNext() {
		return this->next;
	}

	virtual ~Node() {}

	Type getData() {
		return this->data;
	}
};

template <typename Type>
class List {
private:
	Node<Type> *first;
	Node<Type> *last;
	Node<Type> *cursor;
	unsigned int len;

public:
	List() {
		this->first = new Type;
		this->last = this->first;
	}

	virtual ~List() {
		Node<Type> *curr = this->first;
		Node<Type> *prev = curr;
		while(curr->getNext() != NULL) {
			prev = curr;
			curr = curr->getNext();
			delete prev;
		}
	}

	void Add(Type data) {
		this->last = new Node<Type>(data);
	}

	void startCursor() {
		this->cursor = this->first;
	}

	bool forwardCursor() {
		return (((this->cursor = this->cursor->getNext()) == NULL) ? true : false);
	}

	Node<Type> *getCursor() {
		return this->cursor;
	}

	unsigned int size() {
		return this->len;
	}
};

class Comment {
	std::string comment;
	int score;

public:
	/*
	 * post: inicializa el Comentario con el contenido y calificación 0.
	 */
	Comment(std::string contenido) {
		this->comment = contenido;
	}

	std::string getContent() {
		return this->comment;
	}

	/*
	 * post: devuelve la calificación [1 a 10] asociada,
	 *       o 0 si el Comentario no tiene calificación
	 */
	int getScore() {
		return this->score;
	}

	/*
	 * pre: calificacion está comprendido entre 1 y 10
	 * post: cambia la calificación del Comentario
	 */
	void setScore(int calificacion) {
		this->score = calificacion;
	}
};

class Image {
private:
	std::string url;
public:
	/*
	 * post: inicializa la Imagen alojada en la URL indicada
	 */
	Image(std::string url) {
		this->url = url;
	}

	virtual ~Image() {}

	/*
	 * post: devuelve la URL en la que está alojada
	 */
	std::string getUrl();

	/*
	 * post: devuelve los comentarios asociados
	 */
	List<Comment*> *getComments();
};

class Editor {
public:

	/*
	 * post: devuelve de `imgComments` aquel comentario que tenga por lo menos 
	 *       `scoreCount` calificaciones y ademas tenga el promedio de
	 *       calificaciones maximo. Debe recorrer toda la lista para hallar el
	 *       el comentario con mayor promedio de calificacion
	 */
	Comment *getCommentWithHighestScore(List<Comment *> *imgComments) {
		Comment *returnComment;
		Comment *currentComment;
		int currentScore, maxScore;

		returnComment = currentComment = NULL;
		currentScore = maxScore = 0;
		imgComments->startCursor();

		while(imgComments->forwardCursor()) {
			currentComment = imgComments->getCursor()->getData();
			currentScore = returnComment->getScore();
			if(currentScore > 0) {
				if(currentScore > maxScore) {
					maxScore = currentScore;
					returnComment = currentComment;
				}
			}
		}
		return returnComment;
	}

	/*
	 * post: selecciona de `availableImages` aquella que tenga por lo
	 *       menos tantos Comentarios como los indicados en `commentsCount` y
	 *       el promedio de calificaciones sea máximo. Ignora los
	 *       Comentarios sin calificación.
	 */
	Image *seleccionarImagen(List<Image*> *availableImages, int commentsCount) {
		if(commentsCount < 0) {
			throw "la cantidad de comentarios no puede ser negativo";
		} else if(availableImages == NULL) {
			throw "puntero `NULL`";
		}

		Image *returnImg;
		Image *currentImg;
		List<Comment*> *currentImgComments;

		returnImg = currentImg = NULL;

		// se iteran las imagenes
		availableImages->startCursor();
		while(availableImages->forwardCursor()) {
			currentImg = availableImages->getCursor()->getData();
			currentImgComments = currentImg->getComments();
			if(currentImgComments->size() > (unsigned int)commentsCount) {
				// iteran los comentarios de la imagen y se obtiene el 
				// comentario con mas calificaciones
				if(this->getCommentWithHighestScore(currentImgComments) != NULL) {
					return returnImg = currentImg;
				}
			}
		}
	}
};

int main () {
	Editor *e = new Editor;
	delete e;
	return 0;
}
