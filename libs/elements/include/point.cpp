#ifndef POINT
#define POINT

class Point: public Geometria {
public:
	Point(char const* nome, int x, int y) :
			Geometria(nome, PONTO) {
		pontos.adiciona(BasePoint(x, y));
	}

	int getX() {
		return pontos.recuperaDaPosicao(0).getX();
	}

	int getY() {
		return pontos.recuperaDaPosicao(0).getY();
	}
};
#endif
