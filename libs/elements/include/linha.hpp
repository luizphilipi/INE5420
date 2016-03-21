#ifndef LINE
#define LINE

#include "basepoint.hpp"

class Linha: public Geometria {
public:
	Linha(char const* nome, int x1, int y1, int x2, int y2) :
			Geometria(nome, LINHA) {
		pontos->adiciona(BasePoint(x1, y1));
		pontos->adiciona(BasePoint(x2, y2));
	}

	Linha(char* nome, BasePoint p1, BasePoint p2) :
			Geometria(nome, LINHA) {
		pontos->adiciona(p1);
		pontos->adiciona(p2);
	}

	BasePoint getPonto1() {
		return pontos->recuperaDaPosicao(0);
	}

	BasePoint getPonto2() {
		return pontos->recuperaDaPosicao(1);
	}
};
#endif
