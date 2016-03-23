#ifndef GEOMETRIA
#define GEOMETRIA

#include "listaEnc.hpp"

const int MAX_OBJECTS = 100;

struct Coordenada {

	Coordenada(double x, double y) :
			x(x), y(y) {
	}

	double getX() {
		return x;
	}

	double getY() {
		return y;
	}

	void add(double x, double y) {
		this->x += x;
		this->y += y;
	}

	void sub(double x, double y) {
		this->x -= x;
		this->y -= y;
	}

private:
	double x;
	double y;
};

enum tipoGeometria {
	PONTO, LINHA, POLIGONO
};

class ObjetoGrafico {
protected:
	ObjetoGrafico(char const* nome, tipoGeometria tipo) :
			nome(nome), tipo(tipo) {
		listaCoords = new ListaEnc<Coordenada>();
	}

	ObjetoGrafico(char const* nome, tipoGeometria tipo,
			ListaEnc<Coordenada> *coords) :
			nome(nome), tipo(tipo), listaCoords(coords) {
	}

	char const *nome;
	tipoGeometria tipo;
	ListaEnc<Coordenada> *listaCoords;

public:
	char const* getNome() {
		return nome;
	}

	tipoGeometria getTipo() {
		return tipo;
	}

	int getQuantidadeCoords() {
		return listaCoords->getSize();
	}

	ListaEnc<Coordenada> * getListaCoord() {
		return listaCoords;
	}

	Coordenada getCoord(int i) {
		return listaCoords->recuperaDaPosicao(i);
	}
};

#endif
