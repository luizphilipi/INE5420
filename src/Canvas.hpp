#ifndef CANVAS
#define CANVAS

#include "ObjetoGrafico.hpp"
#include <math.h>

class Canvas {
public:
	Canvas(double largura, double altura) :
			largura(largura), altura(altura), _centro(0, 0), vupVector(0, 1) {
	}

	void move(Coordenada passo) {
		double xFactor = largura * passo.getX() / 100.0;
		double yFactor = altura * passo.getY() / 100.0;

		_centro += Coordenada(xFactor, yFactor);
	}

	void zoom(double passo) {
		double xFactor = xOffset() * passo / 100.0;
		if (xFactor > xOffset()) {
			xFactor = xOffset();
		}

		double yFactor = yOffset() * passo / 100.0;
		if (yFactor > yOffset()) {
			yFactor = yOffset();
		}

		largura -= 2 * xFactor;
		altura -= 2 * yFactor;
	}

	void rotacionar(double angulo) {
		Matriz matrizRotacao = MatrizUtil::matrizRotacao(3, 3, angulo);
		Matriz matrizVUP = Matriz(vupVector);
		Matriz result = matrizVUP * matrizRotacao;

		vupVector._x = result(0, 0);
		vupVector._y = result(0, 1);
	}

	Coordenada centro() {
		return this->_centro;
	}

	double xOffset() {
		return this->largura / 2;
	}

	double yOffset() {
		return this->altura / 2;
	}

	double zOffset() {
		return 1;
	}

	// Matriz que contem a transformação que precisa ser feita para rotacionar e mover os objetos para a sua posição original
	Matriz matrizTransformacaoCanvas() {
		double radianos = vupVector.angleWith(Coordenada(0, 1));

		double angulo = radianos / PI * 180.0;

		// gambi do joão pra fazer funcionar a rotação total e não só meia lua :v
		if (vupVector._x < 0) {
			angulo = 360 - angulo;
		}

		Matriz matrizTranslacao = MatrizUtil::matrizTranslacao(3, 3,
				_centro.negativa());
		Matriz matrizRotacao = MatrizUtil::matrizRotacao(3, 3, angulo);
		Matriz translationBackMatrix = MatrizUtil::matrizTranslacao(3, 3,
				centro());

		return matrizTranslacao * matrizRotacao * translationBackMatrix;
	}

private:
	double altura, largura;
	Coordenada _centro;
	// View-Up Vector - vetor que guarda a referência de "pra cima" do nosso canvas.
	Coordenada vupVector;
};

#endif
