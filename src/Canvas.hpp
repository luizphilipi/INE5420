#ifndef CANVAS
#define CANVAS

#include "ObjetoGrafico.hpp"

class Canvas {
public:
	Canvas(Coordenada cantoInferiorEsquerdo, Coordenada cantoSuperiorDireito) :
			cantoInferiorEsquerdo(cantoInferiorEsquerdo), cantoSuperiorDireito(
					cantoSuperiorDireito) {
	}

	void move(Coordenada passo) {
		double xFactor = (this->cantoSuperiorDireito.getX()
				- this->cantoInferiorEsquerdo.getX()) * passo.getX() / 100.0;
		double yFactor = (this->cantoSuperiorDireito.getY()
				- this->cantoInferiorEsquerdo.getY()) * passo.getY() / 100.0;

		this->cantoInferiorEsquerdo.add(xFactor, yFactor);
		this->cantoSuperiorDireito.add(xFactor, yFactor);
	}

	void zoom(double passo) {
		double largura = (this->cantoSuperiorDireito.getX()
				- this->cantoInferiorEsquerdo.getX());
		double altura = (this->cantoSuperiorDireito.getY()
				- cantoInferiorEsquerdo.getY());

		double xFactor = largura * passo / 100.0;

		double yFactor = altura * passo / 100.0;

		this->cantoInferiorEsquerdo.add(xFactor, yFactor);
		this->cantoSuperiorDireito.sub(xFactor, yFactor);
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
