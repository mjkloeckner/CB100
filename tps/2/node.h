#ifndef NODE_H_
#define NODE_H_

#include <iostream>

template <typename Type>
class Node {
private:
	Type data;
	Node<Type> *next;

public:
	/*
	 * pos: el nodo resulta inicializado con el dato dado y sin nodo siguiente
	 */
	Node(Type newData);

	/*
	 * pos: se libera la memoria utilizada
	 */
	virtual ~Node();

	/*
	 * pos: devuelve el dato almacenado en el nodo
	 */
	Type getData();

	/*
	 * pos: cambia el dato almacendo en el nodo por `data`
	 */
	void setData(Type newData);

	/*
	 * pos: devuelve una referencia al nodo siguiente
	 */
	Node<Type>* getNext();

	/*
	 * pos: cambia el nodo siguiente por `next`
	 */
	void setNext(Node<Type> *newNext);
};

template <typename Type>
Node<Type>::Node(Type newData) {
	this->data = newData;
	this->next = NULL;
}

template <typename Type>
Node<Type>::~Node() {}

template <typename Type>
Type Node<Type>::getData() {
	return this->data;
}

template <typename Type>
void Node<Type>::setData(Type newData) {
	this->data = newData;
}

template <typename Type>
Node<Type> *Node<Type>::getNext() {
	return this->next;
}

template <typename Type>
void Node<Type>::setNext(Node<Type> *newNext) {
	this->next = newNext;
}

#endif
