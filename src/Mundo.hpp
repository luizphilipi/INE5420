#ifndef MUNDO_HPP_
#define MUNDO_HPP_

#include <cstring>
#include <iostream>
#include <vector>

#include "Canvas.hpp"
#include "Linha.hpp"
#include "ObjetoGrafico.hpp"
#include "Poligono.hpp"
#include "Ponto.hpp"

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

	void adicionaPonto(string nome, Coordenada coord) {
		displayFile->adiciona(Ponto(nome, coord));
	}

	void adicionaLinha(string nome, Coordenada p1, Coordenada p2) {
		displayFile->adiciona(Linha(nome, p1, p2));
	}

	void adicionaPoligono(string nome, ListaEnc<Coordenada> *coords) {
		displayFile->adiciona(Poligono(nome, coords));
	}

	ListaEnc<ObjetoGrafico>* getObjetos() {
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

	void transladar(string nome, Coordenada coord) {
		for (int i = 0; i < displayFile->getSize(); i++) {
			if (nome == displayFile->recuperaDaPosicao(i).getNome()) {
				displayFile->recuperaDaPosicao(i).transladar(coord);
				break;
			}
		}
	}

	void escalonar(string nome, Coordenada coord) {
		for (int i = 0; i < displayFile->getSize(); i++) {
			if (nome == displayFile->recuperaDaPosicao(i).getNome()) {
				displayFile->recuperaDaPosicao(i).escalonar(coord);
				break;
			}
		}
	}

	void rotacionar(string nome, double angulo) {
		for (int i = 0; i < displayFile->getSize(); i++) {
			std::cout << nome << " == " << displayFile->recuperaDaPosicao(i).getNome() << std::endl;
			if (nome == displayFile->recuperaDaPosicao(i).getNome()) {
				displayFile->recuperaDaPosicao(i).rotacionar(angulo);
				break;
			}
		}
	}

	void rotacionar(string nome, double angulo, Coordenada coord) {
		for (int i = 0; i < displayFile->getSize(); i++) {
			if (nome == displayFile->recuperaDaPosicao(i).getNome()) {
				displayFile->recuperaDaPosicao(i).rotacionar(coord, angulo);
				break;
			}
		}
	}
};

#endif
