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
			canvas(550, 550) {
		displayFile = new ListaEnc<ObjetoGrafico>();
	}

	virtual ~Mundo() {
	}

	void adicionaPonto(string nome, Coordenada coord) {
		Ponto ponto = Ponto(nome, coord);
		normalizar(ponto);
		displayFile->adiciona(ponto);
	}

	void adicionaLinha(string nome, Coordenada p1, Coordenada p2) {
		Linha linha = Linha(nome, p1, p2);
		normalizar(linha);
		displayFile->adiciona(linha);
	}

	void adicionaPoligono(string nome, ListaEnc<Coordenada> *coords) {
		Poligono poligono = Poligono(nome, coords);
		normalizar(poligono);
		displayFile->adiciona(poligono);
	}

	ListaEnc<ObjetoGrafico>* getObjetos() {
		return displayFile;
	}

	Canvas getCanvas() {
		return canvas;
	}

	void moverCima(int passo) {
		canvas.move(Coordenada(0, passo));
		normalizarTudo();
	}

	void moverBaixo(int passo) {
		canvas.move(Coordenada(0, -passo));
		normalizarTudo();
	}

	void moverEsquerda(int passo) {
		canvas.move(Coordenada(-passo, 0));
		normalizarTudo();
	}

	void moverDireita(int passo) {
		canvas.move(Coordenada(passo, 0));
		normalizarTudo();
	}

	void zoomIn(double passo) {
		canvas.zoom(passo);
		normalizarTudo();
	}

	void zoomOut(double passo) {
		canvas.zoom(-passo);
		normalizarTudo();
	}

	void rotacionar(double angulo) {
		canvas.rotacionar(angulo);
		normalizarTudo();
	}

	void transladar(string nome, Coordenada coord) {
		for (int i = 0; i < displayFile->getSize(); i++) {
			if (nome == displayFile->recuperaDaPosicao(i).getNome()) {
				ObjetoGrafico obj = displayFile->recuperaDaPosicao(i);
				obj.transladar(coord);
				normalizar(obj);
				break;
			}
		}
	}

	void escalonar(string nome, Coordenada coord) {
		for (int i = 0; i < displayFile->getSize(); i++) {
			if (nome == displayFile->recuperaDaPosicao(i).getNome()) {
				ObjetoGrafico obj = displayFile->recuperaDaPosicao(i);
				obj.escalonar(coord);
				normalizar(obj);
				break;
			}
		}
	}

	void rotacionar(string nome, double angulo) {
		for (int i = 0; i < displayFile->getSize(); i++) {
			if (nome == displayFile->recuperaDaPosicao(i).getNome()) {
				ObjetoGrafico obj = displayFile->recuperaDaPosicao(i);
				obj.rotacionar(angulo);
				normalizar(obj);
				break;
			}
		}
	}

	void rotacionar(string nome, double angulo, Coordenada coord) {
		for (int i = 0; i < displayFile->getSize(); i++) {
			if (nome == displayFile->recuperaDaPosicao(i).getNome()) {
				ObjetoGrafico obj = displayFile->recuperaDaPosicao(i);
				obj.rotacionar(coord, angulo);
				normalizar(obj);
				break;
			}
		}
	}

	void normalizarTudo() {
		for (int i = 0; i < displayFile->getSize(); ++i) {
			normalizar(displayFile->recuperaDaPosicao(i));
		}
	}

	void normalizar(ObjetoGrafico obj) {
		Matriz matrizNormalizacao = canvas.matrizTransformacaoCanvas();
//		std::cout << "Matriz de normalização: " << std::endl;
//		std::cout << matrizNormalizacao << std::endl << std::endl;
		obj.normalizar(canvas.centro(), canvas.xOffset(), canvas.yOffset(),
				canvas.zOffset(), matrizNormalizacao);
	}
};

#endif
