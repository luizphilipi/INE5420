#ifndef MUNDO_HPP_
#define MUNDO_HPP_

#include "canvas.hpp"
#include "objetografico.hpp"
#include "ponto.hpp"
#include "linha.hpp"
#include "poligono.hpp"

class Mundo {
private:
	ListaEnc<ObjetoGrafico> *displayFile;
	Canvas canvas;

public:
	Mundo() :
			canvas(Coordenada(0, 0), Coordenada(550, 550)) {
		displayFile = new ListaEnc<ObjetoGrafico>();
	}

	virtual ~Mundo() {
	}

	void adicionaPonto(const char* nome, Coordenada coord) {
		displayFile->adiciona(Ponto(nome, coord));
	}

	void adicionaLinha(const char* nome, Coordenada p1, Coordenada p2) {
		displayFile->adiciona(Linha(nome, p1, p2));
	}

	void adicionaPoligono(const char* nome, ListaEnc<Coordenada> *coords) {
		displayFile->adiciona(Poligono(nome, coords));
	}

	ListaEnc<ObjetoGrafico> *getObjetos() {
		return displayFile;
	}

	Canvas getCanvas() {
		return canvas;
	}

	void moverCima(int passo) {
		canvas.move(Coordenada(0, passo));
	}

	void moverBaixo(int passo) {
		canvas.move(Coordenada(0, -passo));
	}

	void moverEsquerda(int passo) {
		canvas.move(Coordenada(-passo, 0));
	}

	void moverDireita(int passo) {
		canvas.move(Coordenada(passo, 0));
	}

	void zoomIn(double passo) {
		canvas.zoom(passo);
	}

	void zoomOut(double passo) {
		canvas.zoom(-passo);
	}
};

#endif
