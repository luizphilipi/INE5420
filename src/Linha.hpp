#ifndef LINE
#define LINE

#include "ObjetoGrafico.hpp"

class Linha: public ObjetoGrafico {
public:
	Linha(string nome, Coordenada coord1, Coordenada coord2) :
			ObjetoGrafico(nome, LINHA) {
		listaCoords->adiciona(coord1);
		listaCoords->adiciona(coord2);
	}

	Coordenada getPonto1() {
		return listaCoords->recuperaDaPosicao(0);
	}

	Coordenada getPonto2() {
		return listaCoords->recuperaDaPosicao(1);
	}
};
#endif
