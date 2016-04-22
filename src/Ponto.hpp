#ifndef PONTO_HPP
#define PONTO_HPP

#include "ObjetoGrafico.hpp"

class Ponto: public ObjetoGrafico {
public:
	Ponto(std::string nome, Coordenada coord) :
			ObjetoGrafico(nome, PONTO) {
		coordenadasMundo.push_back(coord);
	}

	int getX() {
		return coordenadasMundo[0]._x;
	}

	int getY() {
		return coordenadasMundo[0]._y;
	}

	std::vector<Coordenada> clip(int status) {
		if (status) {
			Coordenada coord = coordenadasTela[0];
			if (coord._x < -1 || coord._x > 1 || coord._y < -1
					|| coord._y > 1) {
				return std::vector<Coordenada>();
			}
		}
		return coordenadasTela;
	}
};
#endif
