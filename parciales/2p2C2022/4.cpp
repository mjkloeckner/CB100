#include <iostream>
#include <string>

class Colecta {
private:
	double total, maxDonacion, objetivo;
	unsigned int cantDonaciones;

public:
	/**
	 * post: inicializa `Colecta`
	 */
	Colecta() {
		this->objetivo = this->total = this->maxDonacion = this->cantDonaciones = 0;
	}

	/**
	 * post: inicializa `Colecta` con los atributos pasados como argumento
	 *       `objetivo`, `total`, `maxDonacion`, `cantDonaciones`
	 */
	Colecta(double objetivo, double total, double maxDonacion, size_t cantDonaciones) {
		this->objetivo = objetivo;
		this->total = total;
		this->maxDonacion = maxDonacion;
		this->cantDonaciones = cantDonaciones;
	}

	/**
	 * post: libera la memoria de Colecta
	 */
	virtual ~Colecta() {}

	/**
	 * pre: `Colecta` debe estar inicializado
	 * post: asigna `objetivo` al atributo `objetivo` de la clase
	 */
	void setObjetivo(long objetivo) {
		this->objetivo = objetivo;
	}

	/**
	 * pre: `Colecta` debe estar inicializado
	 * post: devuelve el atributo `objetivo` de la clase
	 */
	double getObjetivo() {
		return this->objetivo;
	}

	/**
	 * pre: `Colecta` debe estar inicializado
	 * post: devuelve el atributo `total` de la clase
	 */
	double calcularRecaudacion() {
		return this->total;
	}

	/**
	 * pre: `Colecta` debe estar inicializado
	 * post: incrementa `total` en `monto` solo si `monto` es mayor a 0,
	 *       ademas si `monto` es mayor a la donacion maxima lo guarda
	 *       en `maxDonacion`
	 */
	void donar(double monto) {
		if(monto < 0) {
			throw "El monto a donar no puede ser negativo";
		} else if(monto > maxDonacion) {
			maxDonacion = monto;
		}

		this->total += monto;
		this->cantDonaciones++;
	}

	/**
	 * pre: `Colecta` debe estar inicializado
	 * post: devuelve el atributo `cantDonaciones` de la clase
	 */
	unsigned int contarDonaciones() {
		return this->cantDonaciones;
	}

	/**
	 * pre: `Colecta` debe estar inicializado
	 * post: devuelve el atributo `maxDonacion` de la clase
	 */
	double calcularDonacionMaxima() {
		return this->maxDonacion;
	}

	/**
	 * pre: `Colecta` debe estar inicializado
	 * post: devuelve el monto faltante para llegar a `objetivo`, devuelve 0
	 *       si el monto faltante es 0 o menor a cero (en case de excedente)
	 */
	double calcularRecaudacionFaltante() {
		double faltante = (this->objetivo - this->total);
		return (faltante < 0) ? 0 : faltante;
	}
};

void printStatus(Colecta colecta) {
	std::cout << "Total:    `" << colecta.calcularRecaudacion() << "`\n";
	std::cout << "Objetivo: `" << colecta.getObjetivo() << "`\n";
	std::cout << "Faltante: `" 
		<< colecta.calcularRecaudacionFaltante() << "`\n";
	std::cout << "Maxima donacion: `" 
		<< colecta.calcularDonacionMaxima() << "`\n";
	std::cout << "Cant. de donaciones: `" 
		<< colecta.contarDonaciones() << "`\n";
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
