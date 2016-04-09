#ifndef PONTO_HPP
#define PONTO_HPP

#include "ObjetoGrafico.hpp"

class Ponto: public ObjetoGrafico {
public:
	Ponto(string nome, Coordenada coord) :
			ObjetoGrafico(nome, PONTO) {
		listaCoords->adiciona(coord);
	}

	int getX() {
		return listaCoords->recuperaDaPosicao(0).getX();
	}

	int getY() {
		return listaCoords->recuperaDaPosicao(0).getY();
	}

};
#endif
