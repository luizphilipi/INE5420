#ifndef LINE
#define LINE

#include "ObjetoGrafico.hpp"

class Linha: public ObjetoGrafico {
public:
	Linha(string nome, Coordenada coord1, Coordenada coord2) :
			ObjetoGrafico(nome, LINHA) {
		coordenadasMundo->adiciona(coord1);
		coordenadasMundo->adiciona(coord2);
	}

	Coordenada getPonto1() {
		return coordenadasMundo->recuperaDaPosicao(0);
	}

	Coordenada getPonto2() {
		return coordenadasMundo->recuperaDaPosicao(1);
	}
};
#endif
