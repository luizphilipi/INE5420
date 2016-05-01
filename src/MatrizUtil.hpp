#ifndef __MATRIZ_UTIL_H
#define __MATRIZ_UTIL_H

#include "Matriz.h"
#include <cmath>
#define PI 3.14159265359

class MatrizUtil {

public:


	/* Matriz de Bezier
		 * |-1   3 -3  1|
		 * | 3  -6  3  0|
		 * |-3   3  0  0|
		 * | 1   0  0  0|
		 */
	static Matriz matrizBezier() {
		Matriz bezier = Matriz(4,4);
		bezier(0,0) = -1;
		bezier(1,0) = 3;
		bezier(2,0) = -3;
		bezier(3,0) = 1;

		bezier(0,1) = 3;
		bezier(1,1) = -6;
		bezier(2,1) = 3;
		bezier(3,1) = 0;

		bezier(0,2) = -3;
		bezier(1,2) = 3;
		bezier(2,2) = 0;
		bezier(3,2) = 0;

		bezier(0,3) = 1;
		bezier(1,3) = 0;
		bezier(2,3) = 0;
		bezier(3,3) = 0;

		return bezier;
	}

	/* Matriz T
			 * |t^3   t^2   t    1|
			 */
	static Matriz matrizT(double t) {
		Matriz T = Matriz(1,4);
		T(0,0) = pow(t, 3);
		T(0,1) = pow(t, 2);
		T(0,2) = t;
		T(0,3) = 1.0;

		return T;
	}

	/* Matriz de Translação
	 * | 1	0	0 |
	 * | 0	1	0 |
	 * | Dx	Dy	1 |
	 */
	static Matriz matrizTranslacao(int m, int n, Coordenada deslocamento) {
		Matriz matrizTransformacao = matrizIdentidade(m, n);

		matrizTransformacao(2, 0) = deslocamento.getX();
		matrizTransformacao(2, 1) = deslocamento.getY();

		return matrizTransformacao;
	}

	/* Matriz de Escalonamento
	 * | Sx	0	0 |
	 * | 0	Sy	0 |
	 * | 0	0	1 |
	 */
	static Matriz matrizEscalonamento(int m, int n, Coordenada fator) {
		Matriz matrizEscalonamento = matrizIdentidade(m, n);

		matrizEscalonamento(0, 0) = fator.getX();
		matrizEscalonamento(1, 1) = fator.getY();

		return matrizEscalonamento;
	}

	/* Matriz de Rotacao
	 * | cos(Θ)	-sin(Θ)	0 |
	 * | sin(Θ)	 cos(Θ)	0 |
	 * | 0		 0		1 |
	 */
	static Matriz matrizRotacao(int m, int n, double anguloGraus) {
		Matriz matrizRotacao = matrizIdentidade(m, n);
		double radianos = grausParaRadianos(anguloGraus);

		matrizRotacao(0, 0) = cos(radianos);
		matrizRotacao(0, 1) = -sin(radianos);
		matrizRotacao(1, 0) = sin(radianos);
		matrizRotacao(1, 1) = cos(radianos);

		return matrizRotacao;
	}

	static Matriz teste(int m, int n, double valor) {
		Matriz matrizRotacao = matrizIdentidade(m, n);

		matrizRotacao(0, 0) = cos(valor);
		matrizRotacao(0, 1) = sin(valor);
		matrizRotacao(1, 0) = -sin(valor);
		matrizRotacao(1, 1) = cos(valor);

		return matrizRotacao;
	}

	static double grausParaRadianos(double anguloGraus) {
		return anguloGraus * PI / 180;
	}

	static Matriz matrizIdentidade(int m, int n) {
		Matriz matrizIdentidade = Matriz(m, n);
		for (int i = 0; i < m; ++i) {
			matrizIdentidade(i, i) = 1;
		}

		return matrizIdentidade;
	}

};

#endif
