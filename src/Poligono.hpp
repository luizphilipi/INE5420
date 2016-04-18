#ifndef POLYGON
#define POLYGON

#include "ObjetoGrafico.hpp"

class Poligono: public ObjetoGrafico {
public:
	Poligono(string nome, ListaEnc<Coordenada>* pontos, bool preenchimento, GdkRGBA cor) :
			ObjetoGrafico(nome, POLIGONO, pontos, preenchimento, cor) {
	}

	Poligono(string nome, ListaEnc<Coordenada>* pontos, bool preenchimento) :
			ObjetoGrafico(nome, POLIGONO, pontos, preenchimento) {
	}

	// baseado em https://rosettacode.org/wiki/Sutherland-Hodgman_polygon_clipping#Java
	ListaEnc<Coordenada>* clip() {
		ListaEnc<Coordenada> *resultado = new ListaEnc<Coordenada>();
		for (int i = 0; i < this->coordenadasTela->getSize(); ++i) {
			resultado->adiciona(this->coordenadasTela->recuperaDaPosicao(i));
		}

		int len = 4;
		for (int i = 0; i < len; i++) {

			int len2 = resultado->getSize();

			ListaEnc<Coordenada> *input = resultado;
			resultado = new ListaEnc<Coordenada>();

			Coordenada A = tela[(i + len - 1) % len];
			Coordenada B = tela[i];

			for (int j = 0; j < len2; j++) {

				Coordenada P = input->recuperaDaPosicao((j + len2 - 1) % len2);
				Coordenada Q = input->recuperaDaPosicao(j);

				if (isInside(A, B, Q)) {
					if (!isInside(A, B, P)) {
						resultado->adiciona(intersection(A, B, P, Q));
					}
					resultado->adiciona(Q);
				} else if (isInside(A, B, P)) {
					resultado->adiciona(intersection(A, B, P, Q));
				}
			}
		}
		return resultado;
	}
private:

	// Tela vai de (-1,-1) até (1,1);
	int xmin = -1, ymin = -1, xmax = 1, ymax = 1;
	Coordenada tela[4] = { Coordenada(xmin, ymin), Coordenada(xmax, ymin),
			Coordenada(xmax, ymax), Coordenada(xmin, ymax) };

	bool isInside(Coordenada a, Coordenada b, Coordenada c) {
		return (a._x - c._x) * (b._y - c._y) > (a._y - c._y) * (b._x - c._x);
	}

	Coordenada intersection(Coordenada a, Coordenada b, Coordenada p,
			Coordenada q) {
		double A1 = b._y - a._y;
		double B1 = a._x - b._x;
		double C1 = A1 * a._x + B1 * a._y;

		double A2 = q._y - p._y;
		double B2 = p._x - q._x;
		double C2 = A2 * p._x + B2 * p._y;

		double det = A1 * B2 - A2 * B1;
		double x = (B2 * C1 - B1 * C2) / det;
		double y = (A1 * C2 - A2 * C1) / det;

		return Coordenada(x, y);
	}
};
#endif
