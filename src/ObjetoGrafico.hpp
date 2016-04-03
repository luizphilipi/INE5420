#ifndef GEOMETRIA
#define GEOMETRIA

#include "ListaEnc.hpp"
#include "Coordenada.hpp"
#include "MatrizUtil.hpp"

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

	const Coordenada centro() const {
		int x = 0;
		int y = 0;
		int tamanho = listaCoords->getSize();
		for (int i = 0; i < tamanho; ++i) {
			x += listaCoords->recuperaDaPosicao(i).getX();
			y += listaCoords->recuperaDaPosicao(i).getY();
		}

		x = x / tamanho;
		y = y / tamanho;

		return Coordenada(x, y);
	}

	const void transladar(Coordenada vetorDeslocamento) const {
		Matriz matrizTransformacao = MatrizUtil::matrizTranslacao(3, 3,
				vetorDeslocamento);
		aplicarTransformacao(matrizTransformacao);
	}

	const void escalonar(Coordenada fator) const {
		Matriz matrizEscalonamento = MatrizUtil::matrizEscalonamento(3, 3,
				fator);
		aplicarTransformacao(matrizEscalonamento, this->centro());
	}

	const void rotacionar(double anguloEmGraus) const {
		Matriz matrizRotacao = MatrizUtil::matrizRotacao(3, 3, anguloEmGraus);
		aplicarTransformacao(matrizRotacao, this->centro());
	}

	const void rotacionar(Coordenada emTornoDe, double anguloEmGraus) const {
		Matriz matrizRotacao = MatrizUtil::matrizRotacao(3, 3, anguloEmGraus);
		aplicarTransformacao(matrizRotacao, emTornoDe);
	}

private:
	const void aplicarTransformacao(Matriz matrizTransformacao) const {
		for (int i = 0; i < listaCoords->getSize(); ++i) {
			Coordenada coord = listaCoords->eliminaDaPosicao(i);
			Matriz resultado = Matriz(coord) * matrizTransformacao;
			coord._x = resultado(0, 0);
			coord._y = resultado(0, 1);
			coord._z = resultado(0, 2);
			listaCoords->adicionaNaPosicao(coord, i);
		}
	}

	const void aplicarTransformacao(Matriz matrizTransformacao,
			Coordenada posicao) const {
		Matriz resultado = MatrizUtil::matrizTranslacao(3, 3,
				posicao.negativa()) * matrizTransformacao
				* MatrizUtil::matrizTranslacao(3, 3, posicao);

		aplicarTransformacao(resultado);
	}
};

#endif
