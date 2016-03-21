#ifndef GEOMETRIA
#define GEOMETRIA

#include "basepoint.hpp"
#include "listaEnc.hpp"

const int MAX_OBJECTS = 100;

enum tipoGeometria {
	PONTO, LINHA, POLIGONO
};

class Geometria {
protected:
	Geometria(char const* nome, tipoGeometria tipo) :
			nome(nome), tipo(tipo) {
		pontos = ListaEnc<BasePoint>();
	}

	Geometria(char* nome, tipoGeometria tipo, ListaEnc<BasePoint> pontos) :
	nome(nome), tipo(tipo), pontos(pontos) {
	}

	char const *nome;
	tipoGeometria tipo;
	ListaEnc<BasePoint> pontos;


public:
	char const* getNome() {
		return nome;
	}

	tipoGeometria getTipo() {
		return tipo;
	}

	int getQuantidadePontos() {
		return pontos.getSize();
	}

	ListaEnc<BasePoint> getPontos() {
		return pontos;
	}

	BasePoint getPonto(int i) {
		return pontos.recuperaDaPosicao(i);
	}
};

#endif
