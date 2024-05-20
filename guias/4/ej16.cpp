#include <iostream>

class Rectangle {
private:
	float base;
	float height;

public:
	/**
	 * post: inicializa el rectangulo con sus atributos a `0.0f`
	 */
	Rectangle() {
		this->base = 0.0f;
		this->height = 0.0f;
	}

	/**
	 * post: inicializa el rectangulo con `base` y `altura`
	 */
	Rectangle(float base, float height) {
		this->base = base;
		this->height = height;
	}

	/**
	 * post: libera la memoria
	 */
	virtual ~Rectangle() {}

	/**
	 * pre: el rectangulo debe estar inicializado
	 * post: cambia la base del rectangulo por `base`
	 */
	void setBase(float base) {
		this->base = base;
	}

	/**
	 * pre: el rectangulo debe estar inicializado
	 * post: cambia la altura del rectangulo por `height`
	 */
	void setHeight(float height) {
		this->height = height;
	}

	/**
	 * pre: el rectangulo debe estar inicializado
	 * post: devuelve la base del rectangulo
	 */
	float getBase() {
		return this->base;
	}

	/**
	 * pre: el rectangulo debe estar inicializado
	 * post: devuelve la altura del rectangulo
	 */
	float getHeight() {
		return this->height;
	}

	/**
	 * pre: el rectangulo debe estar inicializado
	 * post: devuelve el perimetro del rectangulo
	 */
	float getPerimeter() {
		return 2*(this->base + this->height);
	}

	/**
	 * pre: el rectangulo debe estar inicializado
	 * post: devuelve el area del rectangulo
	 */
	float getArea() {
		return this->base * this->height;
	}

	/**
	 * pre:  el rectangulo debe estar inicializada
	 * post: imprime la base y altura del rectangulo en formato (b,h)
	 */
	void print() {
		std::cout << "(" << this->base << ", " << this->height << ")\n";
	}
};

int main (void) {
	Rectangle r(2,2);
	r.print();
	std::cout << "Perimetro = " << r.getPerimeter() << std::endl;
	std::cout << "Area = " << r.getArea() << std::endl;
	std::cout << "Base = " << r.getBase() << std::endl;
	std::cout << "Altura = " << r.getHeight() << std::endl;
	return 0;
}
