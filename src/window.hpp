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

	void zoom(int step) {
		int halfWidth = (this->cantoSuperiorDireito.getX()
				- this->cantoInferiorEsquerdo.getX()) / 2;
		int halfHeight = (this->cantoSuperiorDireito.getY()
				- cantoInferiorEsquerdo.getY()) / 2;

		double xFactor = 0.0;
		if (halfWidth - 1 > halfWidth * step / 100.0) {
			xFactor = halfWidth * step / 100.0;
		} else {
			xFactor = halfWidth - 1;
		}

		double yFactor = 0.0;
		if (halfHeight - 1 > halfHeight * step / 100.0) {
			yFactor = halfHeight * step / 100.0;
		} else {
			yFactor = halfHeight - 1;
		}

		this->cantoInferiorEsquerdo.add(xFactor, yFactor);
		this->cantoSuperiorDireito.add(xFactor, yFactor);
	}

	int Xmin() {
		return this->cantoInferiorEsquerdo.getX();
	}

	int Ymin() {
		return this->cantoInferiorEsquerdo.getY();
	}

	int Xmax() {
		return this->cantoSuperiorDireito.getX();
	}

	int Ymax() {
		return this->cantoSuperiorDireito.getY();
	}

private:
	Coordenada cantoInferiorEsquerdo;
	Coordenada cantoSuperiorDireito;
};

#endif
