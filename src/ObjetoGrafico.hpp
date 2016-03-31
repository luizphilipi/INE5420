#ifndef GEOMETRIA
#define GEOMETRIA

#include "ListaEnc.hpp"
#include "Coordenada.hpp"

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

	Coordenada centro() {
		int x = 0;
		int y = 0;
		int tamanho = listaCoords->getSize();
		for (int i = 0; i < tamanho; ++i) {
			x += listaCoords->recuperaDaPosicao(i).getX();
			y += listaCoords->recuperaDaPosicao(i).getY();
		}

		x = x / tamanho;
		y = y / tamanho;

		return Coordenada(x,y);
	}
};

#endif
