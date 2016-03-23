#ifndef WINDOW
#define WINDOW

#include "objetografico.hpp"

class Window {
public:
	Window(Coordenada cantoInferiorEsquerdo, Coordenada cantoSuperiorDireito) :
			cantoInferiorEsquerdo(cantoInferiorEsquerdo), cantoSuperiorDireito(
					cantoSuperiorDireito) {
	}

	void move(Coordenada step) {
		double xFactor = (this->cantoSuperiorDireito.getX()
				- this->cantoInferiorEsquerdo.getX()) * step.getX() / 100.0;
		double yFactor = (this->cantoSuperiorDireito.getY()
				- this->cantoInferiorEsquerdo.getY()) * step.getY() / 100.0;

		this->cantoInferiorEsquerdo.add(xFactor, yFactor);
		this->cantoSuperiorDireito.add(xFactor, yFactor);
	}

	void zoom(double step) {
		double halfWidth = (this->cantoSuperiorDireito.getX()
				- this->cantoInferiorEsquerdo.getX()) / 2;
		double halfHeight = (this->cantoSuperiorDireito.getY()
				- cantoInferiorEsquerdo.getY()) / 2;

		double xFactor = 0.0;
		if ((halfWidth - 1) > (halfWidth * step / 100.0)) {
			xFactor = halfWidth * step / 100.0;
		} else {
			xFactor = halfWidth - 1;
		}

		double yFactor = 0.0;
		if ((halfHeight - 1) > (halfHeight * step / 100.0)) {
			yFactor = halfHeight * step / 100.0;
		} else {
			yFactor = halfHeight - 1;
		}

		std::cout << "Zoom anterior:" << std::endl;
		std::cout << "inferior(" << this->cantoInferiorEsquerdo.getX() << ", " << this->cantoInferiorEsquerdo.getY() << ")" << std::endl;
		std::cout << "superior(" << this->cantoSuperiorDireito.getX() << ", " << this->cantoSuperiorDireito.getY() << ")" << std::endl;

		this->cantoInferiorEsquerdo.add(xFactor, yFactor);
		this->cantoSuperiorDireito.add(xFactor, yFactor);

		std::cout << "Zoom posterior:" << std::endl;
		std::cout << "inferior(" << this->cantoInferiorEsquerdo.getX() << ", " << this->cantoInferiorEsquerdo.getY() << ")" << std::endl;
		std::cout << "superior(" << this->cantoSuperiorDireito.getX() << ", " << this->cantoSuperiorDireito.getY() << ")" << std::endl;
	}

	double Xmin() {
		return this->cantoInferiorEsquerdo.getX();
	}

	double Ymin() {
		return this->cantoInferiorEsquerdo.getY();
	}

	double Xmax() {
		return this->cantoSuperiorDireito.getX();
	}

	double Ymax() {
		return this->cantoSuperiorDireito.getY();
	}

private:
	Coordenada cantoInferiorEsquerdo;
	Coordenada cantoSuperiorDireito;
};

#endif
