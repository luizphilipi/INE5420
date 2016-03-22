#ifndef MUNDO_HPP_
#define MUNDO_HPP_

#include "objetografico.hpp"
#include "window.hpp"
#include "ponto.hpp"
#include "linha.hpp"
#include "poligono.hpp"

class Mundo {
private:
	ListaEnc<ObjetoGrafico> displayFile;
	Window window;

public:
	Mundo() :
			window(Coordenada(0, 0), Coordenada(550, 550)) {
		displayFile = ListaEnc<ObjetoGrafico>();
	}

	virtual ~Mundo() {
	}

	void adicionaPonto(const char* nome, Coordenada coord) {
		displayFile.adiciona(Ponto(nome, coord));
	}

	void adicionaLinha(const char* nome, Coordenada p1, Coordenada p2) {
		displayFile.adiciona(Linha(nome, p1, p2));
	}

	void adicionaPoligono(const char* nome, ListaEnc<Coordenada> *coords) {
		displayFile.adiciona(Poligono(nome, coords));
	}

	ListaEnc<ObjetoGrafico> getObjetos() {
		return displayFile;
	}

	Window getWindow() {
		return window;
	}

	void moverCima(int passo) {
		window.move(Coordenada(0, passo));
	}

	void moverBaixo(int passo) {
		window.move(Coordenada(0, -passo));
	}

	void moverEsquerda(int passo) {
		window.move(Coordenada(-passo, 0));
	}

	void moverDireita(int passo) {
		window.move(Coordenada(passo, 0));
	}

	void zoomIn(int passo) {
		window.zoom(passo);
	}

	void zoomOut(int passo) {
		window.zoom(-passo);
	}
};

#endif
