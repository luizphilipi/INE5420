#ifndef GEOMETRIA
#define GEOMETRIA

#include "listaEnc.hpp"

const int MAX_OBJECTS = 100;

struct Coordenada {

	Coordenada(int x, int y) :
			x(x), y(y) {
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	void add(int x, int y) {
		this->x += x;
		this->y += y;
	}

private:
	int x;
	int y;
};

enum tipoGeometria {
	PONTO, LINHA, POLIGONO
};

class ObjetoGrafico {
protected:
	ObjetoGrafico(char const* nome, tipoGeometria tipo) :
			nome(nome), tipo(tipo) {
		pontos = new ListaEnc<Coordenada>();
	}

	ObjetoGrafico(char const* nome, tipoGeometria tipo,
			ListaEnc<Coordenada> *pontos) :
			nome(nome), tipo(tipo), pontos(pontos) {
	}

	char const *nome;
	tipoGeometria tipo;
	ListaEnc<Coordenada> *pontos;

public:
	char const* getNome() {
		return nome;
	}

	tipoGeometria getTipo() {
		return tipo;
	}

	int getQuantidadePontos() {
		return pontos->getSize();
	}

	ListaEnc<Coordenada> * getPontos() {
		return pontos;
	}

	Coordenada getPonto(int i) {
		return pontos->recuperaDaPosicao(i);
	}
};

#endif
