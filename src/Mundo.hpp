#ifndef MUNDO_HPP_
#define MUNDO_HPP_

#include <cstring>
#include <iostream>
#include <vector>

#include "Bezier.hpp"
#include "BSpline.hpp"
#include "Canvas.hpp"
#include "Linha.hpp"
#include "ObjetoGrafico.hpp"
#include "Poligono.hpp"
#include "Ponto.hpp"

class Mundo {
private:
	ListaEnc<ObjetoGrafico*> *displayFile;
	Canvas canvas;

public:
	Mundo() :
			canvas(550, 550) {
		displayFile = new ListaEnc<ObjetoGrafico*>();
	}

	virtual ~Mundo() {
	}

	void adicionaPonto(std::string nome, Coordenada coord) {
		Ponto *ponto = new Ponto(nome, coord);
		normalizar(ponto);
		displayFile->adiciona(ponto);
	}

	void adicionaObj(ObjetoGrafico * obj) {
		normalizar(obj);
		displayFile->adiciona(obj);
	}

	void adicionaLinha(std::string nome, Coordenada p1, Coordenada p2) {
		Linha *linha = new Linha(nome, p1, p2);
		normalizar(linha);
		displayFile->adiciona(linha);
	}

	void adicionaPoligono(std::string nome, std::vector<Coordenada> coords,
			bool preenchimento, GdkRGBA cor) {
		Poligono *poligono = new Poligono(nome, coords, preenchimento, cor);
		normalizar(poligono);
		displayFile->adiciona(poligono);
	}

	void adicionaCurva2D(std::string nome, std::vector<Coordenada> coords) {
			Bezier *curva2D = new Bezier(nome, coords);
			normalizar(curva2D);
			displayFile->adiciona(curva2D);
		}

	ListaEnc<ObjetoGrafico*>* getObjetos() {
		return displayFile;
	}

	Canvas getCanvas() {
		return canvas;
	}

	void moverCima(int passo) {
		canvas.move(Coordenada(0, -passo));
		normalizarTudo();
	}

	void moverBaixo(int passo) {
		canvas.move(Coordenada(0, passo));
		normalizarTudo();
	}

	void moverEsquerda(int passo) {
		canvas.move(Coordenada(passo, 0));
		normalizarTudo();
	}

	void moverDireita(int passo) {
		canvas.move(Coordenada(-passo, 0));
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

	void transladar(std::string nome, Coordenada coord) {
		for (int i = 0; i < displayFile->getSize(); i++) {
			if (nome == displayFile->recuperaDaPosicao(i)->getNome()) {
				ObjetoGrafico *obj = displayFile->recuperaDaPosicao(i);
				obj->transladar(coord);
				normalizar(obj);
				break;
			}
		}
	}

	void escalonar(std::string nome, Coordenada coord) {
		for (int i = 0; i < displayFile->getSize(); i++) {
			if (nome == displayFile->recuperaDaPosicao(i)->getNome()) {
				ObjetoGrafico *obj = displayFile->recuperaDaPosicao(i);
				obj->escalonar(coord);
				normalizar(obj);
				break;
			}
		}
	}

	void rotacionar(std::string nome, double angulo) {
		for (int i = 0; i < displayFile->getSize(); i++) {
			if (nome == displayFile->recuperaDaPosicao(i)->getNome()) {
				ObjetoGrafico *obj = displayFile->recuperaDaPosicao(i);
				obj->rotacionar(angulo);
				normalizar(obj);
				break;
			}
		}
	}

	void rotacionar(std::string nome, double angulo, Coordenada coord) {
		for (int i = 0; i < displayFile->getSize(); i++) {
			if (nome == displayFile->recuperaDaPosicao(i)->getNome()) {
				ObjetoGrafico *obj = displayFile->recuperaDaPosicao(i);
				obj->rotacionar(coord, angulo);
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

	void normalizar(ObjetoGrafico* obj) {
		clock_t begin = clock();

		Matriz matrizNormalizacao = canvas.matrizTransformacaoCanvas();
		obj->normalizar(canvas.centro(), canvas.xOffset(), canvas.yOffset(),
				canvas.zOffset(), matrizNormalizacao);

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		//std::cout << "Objeto " << obj->getNome() << " com " << obj->getListaCoordTela().size() << " pontos normalizado em: "
		//		<< elapsed_secs << std::endl;
	}
};

#endif
