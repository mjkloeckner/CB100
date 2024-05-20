#include <iostream>

// https://en.wikipedia.org/wiki/Greatest_common_divisor
int find_gcd(int a, int b) {
	return (!b) ? a : find_gcd(b, a % b);
}

class Fraction {
private:
	int numerator;
	int divisor;

public:
	/**
	 * post: inicializa la fraccion a `0/1`
	 */
	Fraction() {
		this->numerator = 0;
		this->divisor = 1;
	}

	/**
	 * post: inicializa la fraccion a `numerador/divisor`
	 */
	Fraction(int numerator, int divisor) {
		this->numerator = numerator;
		this->divisor = divisor;
	}

	/**
	 * post: libera la memoria
	 */
	virtual ~Fraction() {}

	/**
	 * post: cambia el numerador de la fraccion a `numerator`
	 */
	void setNumerator(int numerator) {
		this->numerator = numerator;
	}

	/**
	 * post: cambia el divisor de la fraccion a `divisor`
	 */
	void setDivisor(int divisor) {
		this->divisor = divisor;
	}

	/**
	 * post: cambia el numerador y divisor de la fraccion a `numerator` y 
	 *       `divisor` respectivamente
	 */
	void set(int numerator, int divisor) {
		this->setNumerator(numerator);
		this->setDivisor(divisor);
	}

	/**
	 * post: devuelve el numerador de la fracción
	 */
	int getNumerator() {
		return this->numerator;
	}

	/**
	 * post: devuelve el divisor de la fracción
	 */
	int getDivisor() {
		return this->divisor;
	}

	/**
	 * pre:  la fracción debe estar inicializada
	 * post: suma los valores de la fracción `f` a la fracción actual
	 */
	void add(Fraction f) {
		if(this->divisor == f.divisor) {
			this->numerator += f.numerator;
		} else {
			this->numerator *= f.divisor;
			this->divisor *= f.divisor;

			f.numerator *= (this->divisor / f.divisor);
			f.divisor *= (this->divisor / f.divisor);

			this->numerator += f.numerator;
		}
	}

	/**
	 * pre:  la fracción debe estar inicializada
	 * post: resta los valores de la fracción `f` a la fracción actual
	 */
	void substract(Fraction f) {
		if(this->divisor == f.divisor) {
			this->numerator -= f.numerator;
		} else {
			this->numerator *= f.divisor;
			this->divisor *= f.divisor;

			f.numerator *= (this->divisor / f.divisor);
			f.divisor *= (this->divisor / f.divisor);

			this->numerator -= f.numerator;
		}
	}

	/**
	 * pre:  la fracción debe estar inicializada
	 * post: multiplica los valores de la fracción `f` a la fracción actual
	 */
	void multiply(Fraction f) {
		this->numerator *= f.numerator;
		this->divisor *= f.divisor;
	}

	/**
	 * pre:  la fracción debe estar inicializada
	 * post: divide los valores de la fracción `f` a la fracción actual
	 */
	void divide(Fraction f) {
		this->numerator *= f.divisor;
		this->divisor *= f.numerator;
	}

	/**
	 * pre:  la fracción debe estar inicializada
	 * post: simplifica la fracción a su mínima expresión
	 */
	void simplify() {
		int gcd = find_gcd(this->numerator, this->divisor);
		this->numerator /= gcd;
		this->divisor   /= gcd;
	}

	/**
	 * pre:  la fracción debe estar inicializada
	 * post: imprime el contenido de la fracción
	 */
	void print() {
		std::cout << this->numerator << "/" << this->divisor << std::endl;
	}
};

int main (void) {
	Fraction a(1,2);
	Fraction b(1,3);

	a.print();
	b.print();
	a.add(b);
	a.print();

	a.set(1,3);
	a.print();
	a.simplify();
	a.print();
	return 0;
}
