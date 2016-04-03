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
		Matriz matrizTransformacao = MatrizUtil::matrizTransformacao(3, 3,
				vetorDeslocamento);
		aplicarTransformacao(matrizTransformacao);
	}

	const void escalonar(Coordenada fator) const {
		Matriz matrizEscalonamento = MatrizUtil::matrizEscalonamento(3, 3,
				fator);
		aplicarTransformacaoCentro(matrizEscalonamento);
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

	const void aplicarTransformacaoCentro(Matriz matrizTransformacao) const {
		Coordenada coordCentro = this->centro();

		std::cout
				<< MatrizUtil::matrizTransformacao(3, 3, coordCentro.negativa())
				<< std::endl << std::endl;
		std::cout << matrizTransformacao << std::endl << std::endl;
		std::cout << MatrizUtil::matrizTransformacao(3, 3, coordCentro)
				<< std::endl << std::endl;

		Matriz resultado = MatrizUtil::matrizTransformacao(3, 3,
				coordCentro.negativa()) * matrizTransformacao
				* MatrizUtil::matrizTransformacao(3, 3, coordCentro);

		aplicarTransformacao(resultado);
	}
};

#endif
