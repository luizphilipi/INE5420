#ifndef __MATRIZ_UTIL_H
#define __MATRIZ_UTIL_H

#include "Matriz.h"
#include <cmath>
#define PI 3.14159265359

class MatrizUtil {

public:
	static Matriz matrizTranslacao(int m, int n, Coordenada deslocamento) {
		Matriz matrizTransformacao = matrizIdentidade(m, n);

		matrizTransformacao(2, 0) = deslocamento.getX();
		matrizTransformacao(2, 1) = deslocamento.getY();

		return matrizTransformacao;
	}

	static Matriz matrizEscalonamento(int m, int n, Coordenada fator) {
		Matriz matrizEscalonamento = matrizIdentidade(m, n);

		matrizEscalonamento(0, 0) = fator.getX();
		matrizEscalonamento(1, 1) = fator.getY();

		return matrizEscalonamento;
	}

	static Matriz matrizRotacao(int m, int n, double anguloGraus) {
		Matriz matrizRotacao = matrizIdentidade(m, n);
		double radianos = grausParaRadianos(anguloGraus);

		matrizRotacao(0, 0) = cos(radianos);
		matrizRotacao(0, 1) = -sin(radianos);
		matrizRotacao(1, 0) = sin(radianos);
		matrizRotacao(1, 1) = cos(radianos);

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
