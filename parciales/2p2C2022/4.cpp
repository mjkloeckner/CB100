#include <iostream>
#include <string>

class Colecta {
private:
	double total, maxDonacion, objetivo;
	unsigned int cantDonaciones;

public:
	Colecta() {
		this->objetivo = this->total = this->maxDonacion = this->cantDonaciones = 0;
	}

	Colecta(double objetivo, double total, double maxDonacion, size_t cantDonaciones) {
		this->objetivo = objetivo;
		this->total = total;
		this->maxDonacion = maxDonacion;
		this->cantDonaciones = cantDonaciones;
	}

	virtual ~Colecta() {}

	void setObjetivo(long objetivo) {
		this->objetivo = objetivo;
	}

	double getObjetivo() {
		return this->objetivo;
	}

	double calcularRecaudacion() {
		return this->total;
	}

	void donar(double amount) {
		if(amount < 0) {
			throw "El monto a donar no puede ser negativo";
		} else if(amount > maxDonacion) {
			maxDonacion = amount;
		}

		this->total += amount;
		this->cantDonaciones++;
	}

	unsigned int contarDonaciones() {
		return this->cantDonaciones;
	}

	double calcularDonacionMaxima() {
		return this->maxDonacion;
	}

	double calcularRecaudacionFaltante() {
		double faltante = (this->objetivo - this->calcularDonacionMaxima());
		return (faltante < 0) ? 0 : faltante;
	}
};

void printStatus(Colecta colecta) {
	std::cout << "Objetivo: `" << colecta.getObjetivo() << "`\n";
	std::cout << "Cant. de donaciones: `" 
		<< colecta.contarDonaciones() << "`\n";
	std::cout << "Maxima donacion: `" 
		<< colecta.calcularDonacionMaxima() << "`\n";
	std::cout << "Faltante: `" 
		<< colecta.calcularRecaudacionFaltante() << "`\n";
}

int main() {
	Colecta c;
	c.setObjetivo(100000.0);
	printStatus(c);
	std::cout << "\n";

	c.donar(91.52);
	printStatus(c);
	std::cout << "\n";

	c.donar(1020.00);
	printStatus(c);
	std::cout << "\n";

	c.donar(20.00);
	printStatus(c);
	std::cout << "\n";
	return 0;
}
