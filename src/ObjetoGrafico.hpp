#ifndef GEOMETRIA
#define GEOMETRIA

#include "ListaEnc.hpp"
#include "Coordenada.hpp"
#include "MatrizUtil.hpp"
#include <string>

enum tipoGeometria {
	PONTO, LINHA, POLIGONO
};

class ObjetoGrafico {
protected:
	ObjetoGrafico(string nome, tipoGeometria tipo) :
			nome(nome), tipo(tipo) {
		listaCoords = new ListaEnc<Coordenada>();
	}

	ObjetoGrafico(string nome, tipoGeometria tipo,
			ListaEnc<Coordenada> *coords) :
			nome(nome), tipo(tipo), listaCoords(coords) {
	}

	string nome;
	tipoGeometria tipo;
	ListaEnc<Coordenada> *listaCoords;

public:
	string getNome() {
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

	/* Centro do objeto = (Cx, Cy)
	 * Cx = [ SOMA(xi) i=1 até n ] / n
	 * Cy = [ SOMA(yi) i=1 até n ] / n
	 */
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

	/* Aplica o deslocamento (Dx, Dy) a todas as coordenadas [x y 1]
	 * 						 |1  0	0|
	 * [x' y' 1] = [x y 1] * |0	 1	0|
	 * 						 |Dx Dy	1|
	 */
	const void transladar(Coordenada vetorDeslocamento) const {
		Matriz matrizTransformacao = MatrizUtil::matrizTranslacao(3, 3,
				vetorDeslocamento);
		aplicarTransformacao(matrizTransformacao);
	}

	/* Escalonamento natural
	 * Aplica o fator [Sx, Sy] a todas as coordenadas [x y 1] usando o centro [Cx, Cy]
	 * 						 	|1   0	 0|	  |Sx	0	0|   |1		0	0|
	 * [x'' y'' 1] = [x y 1] *	|0	 1	 0| * |0	Sy	0| * |0		1	0|
	 * 							|-Cx -Cy 1|	  |0	0	1|   |Cx	Cy	1|
	 */
	const void escalonar(Coordenada fator) const {
		Matriz matrizEscalonamento = MatrizUtil::matrizEscalonamento(3, 3,
				fator);
		aplicarTransformacao(matrizEscalonamento, this->centro());
	}

	/* Rotaciona em torno do centro [Dx, Dy] com o angulo Θ
	 * 						 	|1   0	 0|		|cos(Θ) -sin(Θ) 0|	|1	0	0|
	 * [x'' y'' 1] = [x y 1] *	|0	 1	 0| *	|sin(Θ)	 cos(Θ)	0| *|0	1	0|
	 * 							|-Dx -Dy 1|		|0		0		1|	|Dx	Dy	1|
	 */
	const void rotacionar(double anguloEmGraus) const {
		Matriz matrizRotacao = MatrizUtil::matrizRotacao(3, 3, anguloEmGraus);
		aplicarTransformacao(matrizRotacao, this->centro());
	}

	const void rotacionar(Coordenada emTornoDe, double anguloEmGraus) const {
		Matriz matrizRotacao = MatrizUtil::matrizRotacao(3, 3, anguloEmGraus);
		aplicarTransformacao(matrizRotacao, emTornoDe);
	}

	/*
	 * Transcreve um objeto gráfico para o formato .obj
	 * nome, tipo, vértices e arestas
	 * Ex: To describe a polygon, the file first describes each point
	 * with the "v"keyword, then describes the face with the "f" keyword.
	 *       # Simple Wavefront file
	 *       v 0.0 0.0 0.0
	 *       v 0.0 1.0 0.0
	 *       v 1.0 0.0 0.0
	 *       f 1 2 3
	 */
	string transcreveObj(){
		string vertices = "# " + nome + "\n";
		string f = "f ";

		for(int i = 0; i<listaCoords->getSize(); i++){
			Coordenada atual = getCoord(i);
			vertices += "v " +
					std::to_string(atual.getX()) + " " +
					std::to_string(atual.getY()) + " " +
					std::to_string(atual.getZ()) + "\n";
			f += std::to_string(i+1) + " ";
		}
		f += "\n\n";
		return vertices + f;
	}


private:

	// [x' y' z' ... ] = [x y z ...] * matriz transformação
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


	const void aplicarTransformacao(Matriz matrizTransformacao, Coordenada posicao) const {
		Matriz resultado = MatrizUtil::matrizTranslacao(3, 3, posicao.negativa()) *
							matrizTransformacao * MatrizUtil::matrizTranslacao(3, 3, posicao);

		aplicarTransformacao(resultado);
	}

};

#endif
