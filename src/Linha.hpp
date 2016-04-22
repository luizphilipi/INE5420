#ifndef LINE
#define LINE

#include "ObjetoGrafico.hpp"

class Linha: public ObjetoGrafico {
public:
	Linha(std::string nome, Coordenada coord1, Coordenada coord2) :
			ObjetoGrafico(nome, LINHA) {
		coordenadasMundo.push_back(coord1);
		coordenadasMundo.push_back(coord2);
	}

	Coordenada getPonto1() {
		return coordenadasMundo[0];
	}

	Coordenada getPonto2() {
		return coordenadasMundo[1];
	}

	std::vector<Coordenada> clip(int status) {
		if (status == 1) {
			return cohenSutherland();
		} else if (status == 2) {
			return liangBarsky();
		} else {
			return coordenadasTela;
		}
	}

private:
	// Representação em int dos códigos de C-S
	int LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;
	// Tela vai de (-1,-1) até (1,1);
	int xmin = -1, ymin = -1, xmax = 1, ymax = 1;

	//Peform Bitwise OR to get outcode
	int getcode(Coordenada coord) {
		int code = 0;

		if (coord._x < xmin) {
			code |= LEFT;
		} else if (coord._x > xmax) {
			code |= RIGHT;
		}

		if (coord._y > ymax) {
			code |= TOP;
		} else if (coord._y < ymin) {
			code |= BOTTOM;
		}

		return code;
	}

	// implementação baseada na wikipedia: https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm
	std::vector<Coordenada> cohenSutherland() {
		Coordenada c1 = coordenadasTela[0];
		Coordenada c2 = coordenadasTela[1];

		int outcode1 = getcode(c1);
		int outcode2 = getcode(c2);

		std::cout << outcode1 << std::endl;
		std::cout << outcode2 << std::endl;

		bool aceita = false;

		//decides if line is to be drawn
		while (true) {
			double m = (c2._y - c1._y) / (c2._x - c1._x);
			if (outcode1 == 0 && outcode2 == 0) {
				aceita = true;
				break;
			} else if (outcode1 & outcode2) {
				break;
			} else {
				double x, y;
				int pontoFora = outcode1 ? outcode1 : outcode2;

				if (pontoFora & TOP) {
					x = c1._x + (ymax - c1._y) / m;
					y = ymax;
				} else if (pontoFora & BOTTOM) {
					x = c1._x + (ymin - c1._y) / m;
					y = ymin;
				} else if (pontoFora & LEFT) {
					x = xmin;
					y = c1._y + m * (xmin - c1._x);
				} else if (pontoFora & RIGHT) {
					x = xmax;
					y = c1._y + m * (xmax - c1._x);
				}
				if (pontoFora == outcode1) {
					c1 = Coordenada(x, y);
					outcode1 = getcode(c1);
				} else {
					c2 = Coordenada(x, y);
					outcode2 = getcode(c2);
				}
			}
		}
		if (aceita) {
			std::vector<Coordenada> novasCoordenadas;
			novasCoordenadas.push_back(c1);
			novasCoordenadas.push_back(c2);

			return novasCoordenadas;
		}
		return std::vector<Coordenada>();
	}

	std::vector<Coordenada> liangBarsky() {
		Coordenada c1 = coordenadasTela[0];
		Coordenada c2 = coordenadasTela[1];

		double dx = c2._x - c1._x;
		double dy = c2._y - c1._y;

		double p[4], q[4];

		p[0] = -dx;
		p[1] = dx;
		p[2] = -dy;
		p[3] = dy;

		q[0] = c1._x - xmin;
		q[1] = xmax - c1._x;
		q[2] = c1._y - ymin;
		q[3] = ymax - c1._y;

		for (int i = 0; i < 4; i++) {
			if (p[i] == 0 && q[i] < 0) {
				return std::vector<Coordenada>();
			}
		}

		double x, y;
		double coef1 = coeficiente1(p, q);
		double coef2 = coeficiente2(p, q);

		if (coef1 > coef2) {
			return std::vector<Coordenada>();
		}

		std::vector<Coordenada> clippedCoords;

		if (coef1 > 0) {
			x = c1._x + coef1 * dx;
			y = c1._y + coef1 * dy;

			clippedCoords.push_back(Coordenada(x, y));
		} else {
			clippedCoords.push_back(c1);
		}

		if (coef2 < 1) {
			x = c1._x + coef2 * dx;
			y = c1._y + coef2 * dy;

			clippedCoords.push_back(Coordenada(x, y));
		} else {
			clippedCoords.push_back(c2);
		}

		return clippedCoords;
	}

	double coeficiente1(double p[], double q[]) {
		double r1 = (p[0] < 0) ? (q[0] / p[0]) : (q[1] / p[1]);
		double r2 = (p[2] < 0) ? (q[2] / p[2]) : (q[3] / p[3]);

		r1 = (!std::isfinite(r1)) ? 0.0 : r1;
		r2 = (!std::isfinite(r2)) ? 0.0 : r2;

		return std::max(0.0, std::max(r1, r2));
	}

	double coeficiente2(double p[], double q[]) {
		double r1 = (p[1] < 0) ? (q[0] / p[0]) : (q[1] / p[1]);
		double r2 = (p[3] < 0) ? (q[2] / p[2]) : (q[3] / p[3]);

		r1 = (!std::isfinite(r1)) ? 1.0 : r1;
		r2 = (!std::isfinite(r2)) ? 1.0 : r2;

		return std::min(1.0, std::min(r1, r2));
	}
};
#endif
