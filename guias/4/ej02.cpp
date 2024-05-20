#include <iostream>

// https://en.wikipedia.org/wiki/Greatest_common_divisor
int find_gcd(int a, int b) {
	return (!b) ? a : find_gcd(b, a % b);
}

class Fraction {
public:
	Fraction() {
		this->numerator = 0;
		this->divisor = 1;
	}

	Fraction(int numerator, int divisor) {
		this->numerator = numerator;
		this->divisor = divisor;
	}

	virtual ~Fraction() {}

	void setNumerator(int numerator) {
		this->numerator = numerator;
	}

	void setDivisor(int divisor) {
		this->divisor = divisor;
	}

	void set(int numerator, int divisor) {
		this->setNumerator(numerator);
		this->setDivisor(divisor);
	}

	int getNumerator() {
		return this->numerator;
	}

	int getDivisor() {
		return this->divisor;
	}

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

	void multiply(Fraction f) {
		this->numerator *= f.numerator;
		this->divisor *= f.divisor;
	}

	void divide(Fraction f) {
		this->numerator *= f.divisor;
		this->divisor *= f.numerator;
	}

	void simplify() {
		int gcd = find_gcd(this->numerator, this->divisor);
		this->numerator /= gcd;
		this->divisor   /= gcd;
	}

	void print() {
		std::cout << this->numerator << "/" << this->divisor << std::endl;
	}

private:
	int numerator;
	int divisor;
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
