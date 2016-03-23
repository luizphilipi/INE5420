#ifndef PONTO_HPP
#define PONTO_HPP

#include "objetografico.hpp"

class Ponto: public ObjetoGrafico {
public:
	Ponto(char const* nome, Coordenada coord) :
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
