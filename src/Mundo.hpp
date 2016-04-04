#ifndef MUNDO_HPP_
#define MUNDO_HPP_

#include "Canvas.hpp"
#include "Linha.hpp"
#include "ObjetoGrafico.hpp"
#include "Poligono.hpp"
#include "Ponto.hpp"
#include <cstring>

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

	void transladar(char* nome, Coordenada coord) {
		for (int i = 0; i < this->displayFile->getSize(); ++i) {
			ObjetoGrafico obj = this->displayFile->recuperaDaPosicao(i);
			if (strcmp(nome, obj.getNome()) == 0) {
				obj.transladar(coord);
				break;
			}
		}
	}

	void escalonar(char* nome, Coordenada coord) {
		for (int i = 0; i < this->displayFile->getSize(); ++i) {
			ObjetoGrafico obj = this->displayFile->recuperaDaPosicao(i);
			if (strcmp(nome, obj.getNome()) == 0) {
				obj.escalonar(coord);
				break;
			}
		}
	}

	void rotacionar(char* nome, double angulo) {
		for (int i = 0; i < this->displayFile->getSize(); ++i) {
			ObjetoGrafico obj = this->displayFile->recuperaDaPosicao(i);
			if (strcmp(nome, obj.getNome()) == 0) {
				obj.rotacionar(angulo);
				break;
			}
		}
	}

	void rotacionar(char* nome, double angulo, Coordenada coord) {
		for (int i = 0; i < this->displayFile->getSize(); ++i) {
			ObjetoGrafico obj = this->displayFile->recuperaDaPosicao(i);
			if (strcmp(nome, obj.getNome()) == 0) {
				obj.rotacionar(coord, angulo);
				break;
			}
		}
	}
};

#endif
