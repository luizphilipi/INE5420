#ifndef LINE
#define LINE

#include "objetografico.hpp"

class Linha: public ObjetoGrafico {
public:
	Linha(const char* nome, Coordenada p1, Coordenada p2) :
			ObjetoGrafico(nome, LINHA) {
		pontos->adiciona(p1);
		pontos->adiciona(p2);
	}

	Coordenada getPonto1() {
		return pontos->recuperaDaPosicao(0);
	}

	Coordenada getPonto2() {
		return pontos->recuperaDaPosicao(1);
	}
};
#endif
