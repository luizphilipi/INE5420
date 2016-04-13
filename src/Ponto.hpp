#ifndef PONTO_HPP
#define PONTO_HPP

#include "ObjetoGrafico.hpp"

class Ponto: public ObjetoGrafico {
public:
	Ponto(string nome, Coordenada coord) :
			ObjetoGrafico(nome, PONTO) {
		coordenadasMundo->adiciona(coord);
	}

	int getX() {
		return coordenadasMundo->recuperaDaPosicao(0).getX();
	}

	int getY() {
		return coordenadasMundo->recuperaDaPosicao(0).getY();
	}

};
#endif
