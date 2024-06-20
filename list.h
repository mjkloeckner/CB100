#ifndef LIST_H_
#define LIST_H_

#include "node.h"

template <typename Type>
class List {
private:
	Node<Type> *first;
	Node<Type> *cursor;
	unsigned int size;

public:
	/*
	 * pos: crea una lista vacia
	 */
	List();

	/*
	 * pos: elimina la memoria de la lista, no de los datos
	 */
	virtual ~List();

	/*
	 * pos: indica si la Lista tiene algún elemento
	 */
	bool isEmpty();

	/*
	 * pos: devuelve la cantidad de elementos que tiene la Lista
	 */
	unsigned int getSize();

	/*
	 * pos: inserta el dato `element` al comienzo de la lista
	 */
	void insert(Type element);

	/*
	 * pos: inicializa el cursor
	 */
	void startCursor();

	/* pre: el cursor ha sido inicializado
	 * pos: avanza el cursor al siguiente elemento de la lista, devuelviendo
	 *      falso si no quedan nodos por recorrer
	 *      recorre la lista en desde el ultimo ingresado al primero
	 */
	bool forwardCursor();

	/*
	 * pre: el cursor ha sido inicializado y está posicionado sobre une
	 *      elemento de la lista
	 * pos: devuelve una referencia al nodo en el cual se encuentra el cursor
	 */
	Node<Type> *getCursor();

	/*
	 * pre: el cursor ha sido inicializado y está posicionado sobre une
	 *      elemento de la lista
	 * pos: devuelve el dato del nodo en el cual se encuentra el cursor
	 */
	Type getCursorData();
};

template <typename Type>
List<Type>::List() {
	this->first = NULL;
	this->size = 0;
	this->cursor = NULL;
}

template <typename Type>
List<Type>::~List() {
	while (this->first != NULL) {
		Node<Type> *delNode = this->first;
		this->first = delNode->getNext();
		delete delNode;
		this->size--;
	}
}

template <typename Type>
bool List<Type>::isEmpty() {
	return (this->size == 0);
}

template <typename Type>
unsigned int List<Type>::getSize() {
	return this->size;
}

template <typename Type>
void List<Type>::insert(Type element) {
	Node<Type> *newNode = new Node<Type>(element);
	newNode->setNext(this->first);
	this->first = newNode;
	this->size++;
}

template<class Type>
void List<Type>::startCursor() {
	this->cursor = NULL;
}

template<class Type>
bool List<Type>::forwardCursor() {
	this->cursor = this->cursor == NULL ? this->first : this->cursor->getNext();

	return (this->cursor != NULL);
}

template<class Type>
Node<Type> *List<Type>::getCursor() {
	return this->cursor;
}

template<class Type>
Type List<Type>::getCursorData() {
	return this->cursor->getData();
}

#endif /* LIST_H_ */
